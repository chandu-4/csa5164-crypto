#include <stdio.h>
#include <string.h>

// Define a key for encryption/decryption (just for demonstration, this is not a real AES key)
#define KEY 0x3A

// Function to encrypt the message using XOR operation
void encrypt(char *message, char *encrypted_message) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        encrypted_message[i] = message[i] ^ KEY;  // XOR each character with the key
    }
    encrypted_message[i] = '\0';  // Null-terminate the encrypted message
}

// Function to decrypt the message using XOR operation
void decrypt(char *encrypted_message, char *decrypted_message) {
    int i;
    for (i = 0; i < strlen(encrypted_message); i++) {
        decrypted_message[i] = encrypted_message[i] ^ KEY;  // XOR again to decrypt
    }
    decrypted_message[i] = '\0';  // Null-terminate the decrypted message
}

int main() {
    // Original message to be encrypted
    char message[] = "welcome to CSE";
    
    // Buffers for encrypted and decrypted messages
    char encrypted_message[100];
    char decrypted_message[100];

    printf("Original message: %s\n", message);

    // Encrypt the message
    encrypt(message, encrypted_message);
    printf("Encrypted message (XOR-ed): ");
    for (int i = 0; i < strlen(encrypted_message); i++) {
        printf("%02X", (unsigned char)encrypted_message[i]);  // Print in hexadecimal
    }
    printf("\n");

    // Decrypt the message
    decrypt(encrypted_message, decrypted_message);
    printf("Decrypted message: %s\n", decrypted_message);

    return 0;
}

