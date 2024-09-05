#include <stdio.h>
#include <stdint.h>

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint8_t uint8;

// Permuted Choice 1 (PC-1) - 56 bits from 64-bit key
int PC1[] = {57, 49, 41, 33, 25, 17, 9,
             1, 58, 50, 42, 34, 26, 18,
             10, 2, 59, 51, 43, 35, 27,
             19, 11, 3, 60, 52, 44, 36,
             63, 55, 47, 39, 31, 23, 15,
             7, 62, 54, 46, 38, 30, 22,
             14, 6, 61, 53, 45, 37, 29,
             21, 13, 5, 28, 20, 12, 4};

// Left shifts for key scheduling
int LEFT_SHIFTS[] = {1, 1, 2, 2, 2, 2, 2, 2,
                     1, 2, 2, 2, 2, 2, 2, 1};

// Permuted Choice 2 (PC-2) - Unused since custom subkey generation
int PC2[] = {14, 17, 11, 24, 1, 5,
             3, 28, 15, 6, 21, 10,
             23, 19, 12, 4, 26, 8,
             16, 7, 27, 20, 13, 2,
             41, 52, 31, 37, 47, 55,
             30, 40, 51, 45, 33, 48,
             44, 49, 39, 56, 34, 53,
             46, 42, 50, 36, 29, 32};

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
void generate_custom_keys(uint64 key, uint64 subkeys[16]) {
    // Apply PC1 to the key
    key = permute(key, PC1, 56);  // Initial key permutation
    uint32 C = (key >> 28) & 0xFFFFFFF;  // Left half (28 bits)
    uint32 D = key & 0xFFFFFFF;          // Right half (28 bits)

    for (int i = 0; i < 16; i++) {
        // Perform left shifts according to the shift schedule
        C = left_shift(C, LEFT_SHIFTS[i]);
        D = left_shift(D, LEFT_SHIFTS[i]);

        // Generate subkey by taking the first 24 bits from C and 24 bits from D
        uint64 subkey = ((C >> 4) & 0xFFFFFF) << 24 | ((D >> 4) & 0xFFFFFF);
        subkeys[i] = subkey;  // Store the 48-bit subkey
    }
}

// Function to print a 48-bit subkey in binary
void print_subkey(uint64 subkey) {
    for (int i = 47; i >= 0; i--) {
        printf("%llu", (subkey >> i) & 1);
    }
    printf("\n");
}

int main() {
    // Example key (64-bit, in hexadecimal for simplicity)
    uint64 key = 0x133457799BBCDFF1;

    uint64 subkeys[16];
    generate_custom_keys(key, subkeys);  // Generate subkeys

    // Print all 16 subkeys in binary format
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: ", i + 1);
        print_subkey(subkeys[i]);
    }

    return 0;
}

