#include <stdio.h>
#include <ctype.h>

int mod(int a, int b) {
    int result = a % b;
    return result >= 0 ? result : result + b;
}

char encrypt_affine_caesar(char p, int a, int b) {
    if (isalpha(p)) {
        char base = isupper(p) ? 'A' : 'a';
        return mod((a * (p - base) + b), 26) + base;
    }
    return p;
}

char decrypt_affine_caesar(char c, int a, int b) {
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        int a_inv = -1;
        for (int i = 0; i < 26; i++) {
            if (mod(a * i, 26) == 1) {
                a_inv = i;
                break;
            }
        }
        return mod(a_inv * (c - base - b), 26) + base;
    }
    return c;
}

int main() {
    int a, b;
    char plaintext[1000], ciphertext[1000];

    printf("Enter the key 'a' (an integer between 1 and 25): ");
    scanf("%d", &a);

    printf("Enter the key 'b' (an integer between 0 and 25): ");
    scanf("%d", &b);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encrypt_affine_caesar(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("\nEncrypted Ciphertext: %s\n", ciphertext);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = decrypt_affine_caesar(ciphertext[i], a, b);
    }
    plaintext[strlen(ciphertext)] = '\0';

    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
