#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// English letter frequency table
const float english_frequency[26] = {8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41,
                                     6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 1.97, 0.07};

// Structure to store letter frequency
typedef struct {
    char letter;
    int count;
} LetterFrequency;

// Function to calculate letter frequency in the given text
void calculate_frequency(const char *text, LetterFrequency *frequency) {
    for (int i = 0; i < strlen(text); i++) {
        char c = tolower(text[i]);
        if (isalpha(c)) {
            frequency[c - 'a'].count++;
        }
    }
}

// Function to compare letter frequency for sorting
int compare_frequency(const void *a, const void *b) {
    const LetterFrequency *freq_a = (const LetterFrequency *)a;
    const LetterFrequency *freq_b = (const LetterFrequency *)b;
    return freq_b->count - freq_a->count;
}

// Function to perform letter frequency attack and generate possible plaintexts
void letter_frequency_attack(const char *ciphertext, char *plaintext, int num_possible_plaintexts) {
    LetterFrequency frequency[26] = {0};

    // Calculate letter frequency in the ciphertext
    calculate_frequency(ciphertext, frequency);

    // Sort the letter frequency in descending order
    qsort(frequency, 26, sizeof(LetterFrequency), compare_frequency);

    // Perform frequency analysis to generate possible plaintexts
    for (int i = 0; i < num_possible_plaintexts; i++) {
        printf("Possible plaintext %d: ", i + 1);
        for (int j = 0; j < strlen(ciphertext); j++) {
            if (isalpha(ciphertext[j])) {
                char c = tolower(ciphertext[j]);
                int index = c - 'a';
                int shift = (c - 'a' - (frequency[i].letter - 'a') + 26) % 26; // Calculate shift for decryption
                if (isupper(ciphertext[j])) {
                    plaintext[j] = (frequency[i].letter + shift - 'a') % 26 + 'A'; // Handle uppercase letters
                } else {
                    plaintext[j] = (frequency[i].letter + shift - 'a') % 26 + 'a'; // Handle lowercase letters
                }
            } else {
                plaintext[j] = ciphertext[j];
            }
        }
        plaintext[strlen(ciphertext)] = '\0';
        printf("%s\n", plaintext);
    }
}

int main() {
    char ciphertext[] = "Lxol, dhuhqbdqwb! Qhawhq grqldidqwb!"; // Example ciphertext
    char plaintext[100]; // Buffer to store possible plaintexts

    int num_possible_plaintexts = 10; // Number of possible plaintexts to generate

    letter_frequency_attack(ciphertext, plaintext, num_possible_plaintexts);

    return 0;
}
