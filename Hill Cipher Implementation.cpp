#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
#define ALPHABET_SIZE 26

// Function to multiply matrices
void matrix_multiply(int mat1[MATRIX_SIZE][MATRIX_SIZE], int mat2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] %= ALPHABET_SIZE;
        }
    }
}

// Function to compute the modular inverse of a matrix
void matrix_inverse(int mat[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    // Assuming 2x2 matrix for simplicity
    int det = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) % ALPHABET_SIZE;
    if (det < 0) det += ALPHABET_SIZE;
    
    // Compute modular inverse of determinant
    int inv_det = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if ((det * i) % ALPHABET_SIZE == 1) {
            inv_det = i;
            break;
        }
    }

    // Compute the inverse matrix
    result[0][0] = mat[1][1] * inv_det % ALPHABET_SIZE;
    result[1][1] = mat[0][0] * inv_det % ALPHABET_SIZE;
    result[0][1] = -mat[0][1] * inv_det % ALPHABET_SIZE;
    result[1][0] = -mat[1][0] * inv_det % ALPHABET_SIZE;

    if (result[0][1] < 0) result[0][1] += ALPHABET_SIZE;
    if (result[1][0] < 0) result[1][0] += ALPHABET_SIZE;
    if (result[0][0] < 0) result[0][0] += ALPHABET_SIZE;
    if (result[1][1] < 0) result[1][1] += ALPHABET_SIZE;
}

// Function to encrypt a plaintext using Hill cipher
void encrypt_hill(const char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int block[MATRIX_SIZE], encrypted_block[MATRIX_SIZE];
    size_t len = strlen(plaintext);
    
    for (size_t i = 0; i < len; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = plaintext[i + j] - 'A';
        }
        matrix_multiply(key, (int[2][2]){ {block[0], block[1]} }, encrypted_block);
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = encrypted_block[j] + 'A';
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt ciphertext using Hill cipher
void decrypt_hill(const char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inv_key[MATRIX_SIZE][MATRIX_SIZE], block[MATRIX_SIZE], decrypted_block[MATRIX_SIZE];
    matrix_inverse(key, inv_key);
    
    size_t len = strlen(ciphertext);
    
    for (size_t i = 0; i < len; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = ciphertext[i + j] - 'A';
        }
        matrix_multiply(inv_key, (int[2][2]){ {block[0], block[1]} }, decrypted_block);
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i + j] = decrypted_block[j] + 'A';
        }
    }
    plaintext[len] = '\0';
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = { {6, 24}, {1, 17} };
    char plaintext[] = "HELLO";
    char ciphertext[strlen(plaintext) + 1];
    char decryptedtext[strlen(plaintext) + 1];

    // Encrypt the plaintext
    encrypt_hill(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt_hill(ciphertext, key, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

