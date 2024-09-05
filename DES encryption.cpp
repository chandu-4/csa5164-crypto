#include <stdio.h>
#include <stdint.h>

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint8_t uint8;

// Initial Permutation (IP)
int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7};

// Final Permutation (FP)
int FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
            39, 7, 47, 15, 55, 23, 63, 31,
            38, 6, 46, 14, 54, 22, 62, 30,
            37, 5, 45, 13, 53, 21, 61, 29,
            36, 4, 44, 12, 52, 20, 60, 28,
            35, 3, 43, 11, 51, 19, 59, 27,
            34, 2, 42, 10, 50, 18, 58, 26,
            33, 1, 41, 9, 49, 17, 57, 25};

// Permuted Choice 1 (PC-1)
int PC1[] = {57, 49, 41, 33, 25, 17, 9,
             1, 58, 50, 42, 34, 26, 18,
             10, 2, 59, 51, 43, 35, 27,
             19, 11, 3, 60, 52, 44, 36,
             63, 55, 47, 39, 31, 23, 15,
             7, 62, 54, 46, 38, 30, 22,
             14, 6, 61, 53, 45, 37, 29,
             21, 13, 5, 28, 20, 12, 4};

// Permuted Choice 2 (PC-2)
int PC2[] = {14, 17, 11, 24, 1, 5,
             3, 28, 15, 6, 21, 10,
             23, 19, 12, 4, 26, 8,
             16, 7, 27, 20, 13, 2,
             41, 52, 31, 37, 47, 55,
             30, 40, 51, 45, 33, 48,
             44, 49, 39, 56, 34, 53,
             46, 42, 50, 36, 29, 32};

// Expansion Table (E)
int E[] = {32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1};

// S-boxes (8 of them)
int S[8][4][16] = {
    // S-box 1
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    // ... (other S-boxes should be implemented here similarly)
    // Fill out the remaining S-boxes 2 through 8
};

// Left shifts for key scheduling
int LEFT_SHIFTS[] = {1, 1, 2, 2, 2, 2, 2, 2,
                     1, 2, 2, 2, 2, 2, 2, 1};

// Function to permute bits according to a table
uint64 permute(uint64 block, int* table, int n) {
    uint64 result = 0;
    for (int i = 0; i < n; i++) {
        result <<= 1;
        result |= (block >> (64 - table[i])) & 1;
    }
    return result;
}

// Function to left shift bits (28-bit halves)
uint32 left_shift(uint32 half, int shifts) {
    return ((half << shifts) & 0xFFFFFFF) | (half >> (28 - shifts));
}

// Function to generate 16 subkeys
void generate_keys(uint64 key, uint64 subkeys[16]) {
    key = permute(key, PC1, 56);  // Initial key permutation
    uint32 C = (key >> 28) & 0xFFFFFFF;  // Left half
    uint32 D = key & 0xFFFFFFF;          // Right half

    for (int i = 0; i < 16; i++) {
        C = left_shift(C, LEFT_SHIFTS[i]);
        D = left_shift(D, LEFT_SHIFTS[i]);
        subkeys[i] = permute(((uint64)C << 28) | D, PC2, 48);  // Generate each subkey
    }
}

// Expansion function
uint64 expand(uint32 right) {
    uint64 result = 0;
    for (int i = 0; i < 48; i++) {
        result <<= 1;
        result |= (right >> (32 - E[i])) & 1;
    }
    return result;
}

// S-Box substitution
uint32 sbox_substitute(uint64 block) {
    uint32 result = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((block >> (42 - i * 6)) & 0x20) | ((block >> (42 - i * 6)) & 1);
        int col = (block >> (43 - i * 6)) & 0xF;
        result <<= 4;
        result |= S[i][row][col];
    }
    return result;
}

// Feistel function
uint32 feistel(uint32 right, uint64 subkey) {
    uint64 expanded_right = expand(right);
    uint64 xored = expanded_right ^ subkey;
    return sbox_substitute(xored);
}

// DES decryption function
uint64 des_decrypt(uint64 ciphertext, uint64 subkeys[16]) {
    ciphertext = permute(ciphertext, IP, 64);  // Initial Permutation
    uint32 left = (ciphertext >> 32) & 0xFFFFFFFF;
    uint32 right = ciphertext & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        uint32 temp = right;
        right = left ^ feistel(right, subkeys[15 - i]);  // Apply Feistel with reversed subkeys
        left = temp;
    }

    uint64 combined = ((uint64)right << 32) | left;
    return permute(combined, FP, 64);  // Final Permutation
}

int main() {
    // Example key and ciphertext (in hexadecimal for simplicity)
    uint64 key = 0x133457799BBCDFF1;
    uint64 ciphertext = 0x85E813540F0AB405;

    uint64 subkeys[16];
    generate_keys(key, subkeys);  // Generate subkeys

    uint64 plaintext = des_decrypt(ciphertext, subkeys);
    printf("Plaintext: %llX\n", plaintext);  // Output plaintext in hex
    return 0;
}

