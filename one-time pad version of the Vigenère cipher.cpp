#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to encrypt plaintext using the one-time pad Vigenère cipher
void encrypt(const char *plaintext, const int *key, size_t key_length, char *ciphertext) {
    size_t text_length = strlen(plaintext);
    for (size_t i = 0; i < text_length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int shift = key[i % key_length];
            ciphertext[i] = ((plaintext[i] - 'A' + shift) % ALPHABET_SIZE) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[i % key_length];
            ciphertext[i] = ((plaintext[i] - 'a' + shift) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters are not encrypted
        }
    }
    ciphertext[text_length] = '\0';
}

// Function to decrypt ciphertext using the one-time pad Vigenère cipher
void decrypt(const char *ciphertext, const int *key, size_t key_length, char *plaintext) {
    size_t text_length = strlen(ciphertext);
    for (size_t i = 0; i < text_length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int shift = key[i % key_length];
            plaintext[i] = ((ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            int shift = key[i % key_length];
            plaintext[i] = ((ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters are not decrypted
        }
    }
    plaintext[text_length] = '\0';
}

int main() {
    // Example plaintext and key
    const char *plaintext = "HELLO";
    int key[] = {3, 19, 5}; // Key stream
    size_t key_length = sizeof(key) / sizeof(key[0]);

    size_t text_length = strlen(plaintext);
    char ciphertext[text_length + 1];
    char decryptedtext[text_length + 1];

    // Encrypt the plaintext
    encrypt(plaintext, key, key_length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, key_length, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

