#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8  // DES processes 64-bit (8-byte) blocks

// Helper function to print 64-bit blocks in hexadecimal
void print_block(uint8_t *block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}

// Placeholder function for DES encryption (For simplicity)
void des_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key) {
    // For demo purposes, we will XOR the key with the plaintext as a simple operation
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

// Placeholder function for DES decryption (XORing with the key again)
void des_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t *key) {
    // XOR again to decrypt (simple operation for demo purposes)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i];
    }
}

int main() {
    // The message to be encrypted and decrypted
    char message[] = "Meet me very urgently";
    int message_len = strlen(message);
    
    // Key (64-bit, 8-byte key for DES)
    uint8_t key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1}; 

    // Prepare for encryption (Split into blocks)
    uint8_t plaintext_block[BLOCK_SIZE], ciphertext_block[BLOCK_SIZE], decrypted_block[BLOCK_SIZE];
    
    printf("Original message: %s\n", message);
    printf("Encrypting the message using DES...\n");

    // Encrypt each block
    int num_blocks = (message_len + BLOCK_SIZE - 1) / BLOCK_SIZE;  // Calculate number of 8-byte blocks needed

    uint8_t encrypted_message[num_blocks * BLOCK_SIZE];  // To store the encrypted message
    memset(encrypted_message, 0, num_blocks * BLOCK_SIZE);  // Initialize to zero (padding)

    for (int i = 0; i < num_blocks; i++) {
        memset(plaintext_block, 0, BLOCK_SIZE);  // Zero out the block for padding
        strncpy((char *)plaintext_block, &message[i * BLOCK_SIZE], BLOCK_SIZE);  // Copy part of the message

        // Encrypt the current block
        des_encrypt(plaintext_block, ciphertext_block, key);
        
        // Print the encrypted block
        printf("Encrypted block %d: ", i + 1);
        print_block(ciphertext_block);

        // Store the ciphertext
        memcpy(&encrypted_message[i * BLOCK_SIZE], ciphertext_block, BLOCK_SIZE);
    }

    // Simulate sending encrypted_message to receiver

    // Receiver Side (Decryption)
    printf("\nDecrypting the message using DES...\n");

    char decrypted_message[num_blocks * BLOCK_SIZE + 1];  // Extra byte for null-terminator
    memset(decrypted_message, 0, num_blocks * BLOCK_SIZE + 1);  // Initialize to zero

    for (int i = 0; i < num_blocks; i++) {
        // Decrypt the current block
        des_decrypt(&encrypted_message[i * BLOCK_SIZE], decrypted_block, key);

        // Print the decrypted block
        printf("Decrypted block %d: ", i + 1);
        print_block(decrypted_block);

        // Store the decrypted block in the decrypted message
        strncpy(&decrypted_message[i * BLOCK_SIZE], (char *)decrypted_block, BLOCK_SIZE);
    }

    // Output the decrypted message
    printf("\nDecrypted message: %s\n", decrypted_message);

    return 0;
}

