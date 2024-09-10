#include <stdio.h>
#include <string.h>

// Function to encrypt the message using Caesar Cipher
void encrypt(char message[], int key) {
    char ch;
    for (int i = 0; message[i] != '\0'; i++) {
        ch = message[i];
        
        // Encrypt lowercase letters
        if (ch >= 'a' && ch <= 'z') {
            ch = ch + key;
            if (ch > 'z') {
                ch = ch - 26; // Wrap around to the beginning of the alphabet
            }
        }
        // Encrypt uppercase letters (if needed)
        else if (ch >= 'A' && ch <= 'Z') {
            ch = ch + key;
            if (ch > 'Z') {
                ch = ch - 26; // Wrap around for uppercase letters
            }
        }
        message[i] = ch; // Replace the original character with the encrypted one
    }
}

// Function to decrypt the message using Caesar Cipher
void decrypt(char message[], int key) {
    char ch;
    for (int i = 0; message[i] != '\0'; i++) {
        ch = message[i];
        
        // Decrypt lowercase letters
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 26; // Wrap around to the end of the alphabet
            }
        }
        // Decrypt uppercase letters (if needed)
        else if (ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if (ch < 'A') {
                ch = ch + 26; // Wrap around for uppercase letters
            }
        }
        message[i] = ch; // Replace the original character with the decrypted one
    }
}

int main() {
    // Message to be encrypted and decrypted
    char message[] = "defend the east wall of the castle";
    int key = 1; // Shift by 1

    printf("Original message: %s\n", message);

    // Encrypt the message
    encrypt(message, key);
    printf("Encrypted message: %s\n", message);

    // Decrypt the message
    decrypt(message, key);
    printf("Decrypted message: %s\n", message);

    return 0;
}

