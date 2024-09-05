#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define BLOCK_SIZE 8  // DES block size in bytes

// Error handling function
void handle_errors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

// CBC Mode Encryption function using 3DES
void cbc_encrypt(const unsigned char *plaintext, int plaintext_len,
                 const unsigned char *key1, const unsigned char *key2, const unsigned char *key3,
                 const unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialize the context
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        handle_errors();
    }

    // Initialize the encryption operation using 3DES in CBC mode
    if (1 != EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key1, iv)) {
        handle_errors();
    }

    // Provide the message to be encrypted, and obtain the encrypted output
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        handle_errors();
    }
    ciphertext_len = len;

    // Finalize the encryption. Further ciphertext bytes may be written at this stage
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        handle_errors();
    }
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    printf("Ciphertext (hex): ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");
}

int main() {
    // Initialize OpenSSL error strings
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    // Example keys and IV
    unsigned char key1[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    unsigned char key2[8] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    unsigned char key3[8] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    // Example plaintext (must be a multiple of BLOCK_SIZE)
    unsigned char plaintext[] = "Hello12345678World";
    int plaintext_len = sizeof(plaintext) - 1; // Exclude the null terminator

    // Ensure plaintext length is a multiple of the block size
    int padding_len = BLOCK_SIZE - (plaintext_len % BLOCK_SIZE);
    unsigned char padded_plaintext[sizeof(plaintext) + padding_len];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    memset(padded_plaintext + plaintext_len, padding_len, padding_len);
    plaintext_len += padding_len;

    unsigned char ciphertext[sizeof(padded_plaintext)];

    // Perform CBC encryption with 3DES
    cbc_encrypt(padded_plaintext, plaintext_len, key1, key2, key3, iv, ciphertext);

    // Clean up OpenSSL
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}

