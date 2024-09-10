#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to calculate frequency of characters
void calculate_frequency(char *text, int frequency[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        }
    }
}

// Function to print the frequency of characters
void print_frequency(int frequency[]) {
    printf("Character frequencies:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("%c: %d\n", 'a' + i, frequency[i]);
        }
    }
}

int main() {
    char ciphertext[] = "cxknxawxccxkncqjcrbcqnzdnbcrxwfruurjvbqjtnbynjan";
    int frequency[ALPHABET_SIZE] = {0}; // Frequency array initialized to 0

    calculate_frequency(ciphertext, frequency);
    print_frequency(frequency);

    return 0;
}

