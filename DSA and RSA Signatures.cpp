#include <stdio.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <string.h>

#define MESSAGE "This is a test message."

void print_signature(unsigned char* sig, unsigned int sig_len) {
    for (unsigned int i = 0; i < sig_len; i++) {
        printf("%02x", sig[i]);
    }
    printf("\n");
}

void sign_dsa() {
    DSA* dsa;
    unsigned char signature[DSA_size(dsa)];
    unsigned int sig_len;
    unsigned char message[] = MESSAGE;

    // Generate DSA key pair
    dsa = DSA_new();
    if (!DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL)) {
        ERR_print_errors_fp(stderr);
        return;
    }
    if (!DSA_generate_key(dsa)) {
        ERR_print_errors_fp(stderr);
        return;
    }

    printf("DSA Signing:\n");
    printf("Message: \"%s\"\n\n", message);

    // Sign the message multiple times and show how signatures differ
    for (int i = 0; i < 2; i++) {
        if (DSA_sign(0, message, strlen((char *)message), signature, &sig_len, dsa)) {
            printf("Signature %d: ", i + 1);
            print_signature(signature, sig_len);
        } else {
            ERR_print_errors_fp(stderr);
        }
    }

    DSA_free(dsa);
}

void sign_rsa() {
    RSA* rsa;
    unsigned char signature[256];
    unsigned int sig_len;
    unsigned char message[] = MESSAGE;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Generate RSA key pair
    rsa = RSA_new();
    BIGNUM* bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bn, NULL);

    printf("\nRSA Signing:\n");
    printf("Message: \"%s\"\n\n", message);

    // Hash the message using SHA-256
    SHA256(message, strlen((char *)message), hash);

    // Sign the message multiple times and show that signatures are the same
    for (int i = 0; i < 2; i++) {
        if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &sig_len, rsa)) {
            printf("Signature %d: ", i + 1);
            print_signature(signature, sig_len);
        } else {
            ERR_print_errors_fp(stderr);
        }
    }

    RSA_free(rsa);
    BN_free(bn);
}

int main() {
    sign_dsa();
    sign_rsa();
    return 0;
}

