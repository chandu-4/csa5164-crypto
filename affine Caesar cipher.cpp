#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to find the modular inverse of a under modulo m
int modular_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist if this returns -1
}

// Function to encrypt plaintext using the affine cipher
void encrypt_affine(const char *plaintext, int a, int b, char *ciphertext) {
    int shift, index;
    for (size_t i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            index = toupper(plaintext[i]) - 'A';
            shift = (a * index + b) % 26;
            ciphertext[i] = shift + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters are not encrypted
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Function to decrypt ciphertext using the affine cipher
void decrypt_affine(const char *ciphertext, int a, int b, char *plaintext) {
    int inv_a = modular_inverse(a, 26);
    if (inv_a == -1) {
        printf("Error: Modular inverse does not exist for a = %d\n", a);
        return;
    }
    
    int shift, index;
    for (size_t i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            index = toupper(ciphertext[i]) - 'A';
            shift = (inv_a * (index - b + 26)) % 26;
            plaintext[i] = shift + 'A';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters are not decrypted
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    const char *plaintext = "HELLO WORLD";
    int a = 5; // Must be coprime with 26
    int b = 8;
    
    size_t text_length = strlen(plaintext);
    char ciphertext[text_length + 1];
    char decryptedtext[text_length + 1];

    // Encrypt the plaintext
    encrypt_affine(plaintext, a, b, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt_affine(ciphertext, a, b, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

