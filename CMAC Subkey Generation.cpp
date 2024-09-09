#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16 // AES block size (128 bits)

// XOR a block of bytes with the given Rb constant
void xor_with_rb(uint8_t *block, uint8_t block_size, uint8_t *rb) {
    for (int i = 0; i < block_size; i++) {
        block[i] ^= rb[i];
    }
}

// Left-shift a block of bytes by one bit
void left_shift(uint8_t *input, uint8_t *output, uint8_t block_size) {
    int overflow = 0;
    for (int i = block_size - 1; i >= 0; i--) {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0; // Keep track of overflow from the previous byte
    }
}

// Generate subkeys K1 and K2
void generate_subkeys(const uint8_t *key, uint8_t *K1, uint8_t *K2) {
    uint8_t L[BLOCK_SIZE] = {0};
    uint8_t Z[BLOCK_SIZE] = {0}; // Zero block (16 bytes of 0)
    uint8_t Rb[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87}; // Rb for AES

    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    // Step 1: L = AES_Encrypt(0^128)
    AES_encrypt(Z, L, &aes_key);

    // Step 2: K1 = L << 1
    left_shift(L, K1, BLOCK_SIZE);

    // If MSB(L) is 1, XOR K1 with Rb
    if (L[0] & 0x80) {
        xor_with_rb(K1, BLOCK_SIZE, Rb);
    }

    // Step 3: K2 = K1 << 1
    left_shift(K1, K2, BLOCK_SIZE);

    // If MSB(K1) is 1, XOR K2 with Rb
    if (K1[0] & 0x80) {
        xor_with_rb(K2, BLOCK_SIZE, Rb);
    }
}

void print_block(const uint8_t *block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}

int main() {
    // Example AES key (128-bit key)
    uint8_t key[BLOCK_SIZE] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x09, 0xcf, 0x4f, 0x3c, 0x12, 0x8e
    };

    uint8_t K1[BLOCK_SIZE] = {0};
    uint8_t K2[BLOCK_SIZE] = {0};

    // Generate subkeys
    generate_subkeys(key, K1, K2);

    // Print the subkeys
    printf("Subkey K1: ");
    print_block(K1, BLOCK_SIZE);

    printf("Subkey K2: ");
    print_block(K2, BLOCK_SIZE);

    return 0;
}

