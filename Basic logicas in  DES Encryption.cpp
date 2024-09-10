#include <stdio.h>
#include <stdint.h>

// Initial Permutation Table
int IP[] = { 
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
int FP[] = { 
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion table for right half of data
int E[] = { 
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

// S-Boxes
int S[8][4][16] = {
    // S1
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
     
    // S2-S8 ...
    // (Skipping for brevity in this sample)
};

// Permutation P Table
int P[] = { 
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Key Permutation Tables and Key Schedule functions are not shown here for brevity

// Perform the Initial Permutation
uint64_t initial_permutation(uint64_t block) {
    uint64_t permuted_block = 0;
    for (int i = 0; i < 64; i++) {
        permuted_block <<= 1;
        permuted_block |= (block >> (64 - IP[i])) & 1;
    }
    return permuted_block;
}

// Perform the Final Permutation
uint64_t final_permutation(uint64_t block) {
    uint64_t permuted_block = 0;
    for (int i = 0; i < 64; i++) {
        permuted_block <<= 1;
        permuted_block |= (block >> (64 - FP[i])) & 1;
    }
    return permuted_block;
}

// Feistel function (expansion, XOR with subkey, substitution, and permutation)
uint32_t feistel(uint32_t half_block, uint64_t subkey) {
    // Expand 32-bit half block to 48 bits
    uint64_t expanded_half = 0;
    for (int i = 0; i < 48; i++) {
        expanded_half <<= 1;
        expanded_half |= (half_block >> (32 - E[i])) & 1;
    }

    // XOR with the subkey
    expanded_half ^= subkey;

    // Substitute using S-boxes and perform permutation
    uint32_t substituted_half = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((expanded_half >> (42 - 6 * i)) & 0x20) | ((expanded_half >> (47 - 6 * i)) & 0x01);
        int col = (expanded_half >> (43 - 6 * i)) & 0xF;
        substituted_half <<= 4;
        substituted_half |= S[i][row][col];
    }

    // Apply P-box permutation
    uint32_t permuted_half = 0;
    for (int i = 0; i < 32; i++) {
        permuted_half <<= 1;
        permuted_half |= (substituted_half >> (32 - P[i])) & 1;
    }

    return permuted_half;
}

// DES encryption function
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    // Apply the initial permutation
    uint64_t permuted_plaintext = initial_permutation(plaintext);

    // Split the block into two halves
    uint32_t left = (permuted_plaintext >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted_plaintext & 0xFFFFFFFF;

    // Perform 16 rounds of encryption
    for (int i = 0; i < 16; i++) {
        uint32_t temp = right;
        right = left ^ feistel(right, key);  // Feistel function
        left = temp;
    }

    // Combine the two halves and apply the final permutation
    uint64_t pre_output = ((uint64_t)right << 32) | left;
    uint64_t ciphertext = final_permutation(pre_output);

    return ciphertext;
}

int main() {
    // Example plaintext and key
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;

    // Encrypt the plaintext using DES
    uint64_t ciphertext = des_encrypt(plaintext, key);

    // Print the result
    printf("Ciphertext: %016llX\n", ciphertext);

    return 0;
}

