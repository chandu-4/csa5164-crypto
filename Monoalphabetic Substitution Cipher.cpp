#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequencies
void calculate_frequencies(const char *text, int *freq) {
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = toupper(text[i]) - 'A';
            freq[index]++;
        }
    }
}

// Function to sort letters by frequency
void sort_by_frequency(int *freq, char *letters) {
    int i, j, temp_freq;
    char temp_letter;
    for (i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[i] < freq[j]) {
                temp_freq = freq[i];
                freq[i] = freq[j];
                freq[j] = temp_freq;
                
                temp_letter = letters[i];
                letters[i] = letters[j];
                letters[j] = temp_letter;
            }
        }
    }
}

// Function to generate possible plaintexts
void generate_plaintexts(const char *ciphertext, const char *substitutions, int num_candidates) {
    char plaintext[strlen(ciphertext) + 1];
    for (int i = 0; i < num_candidates; i++) {
        for (size_t j = 0; ciphertext[j] != '\0'; j++) {
            if (isalpha(ciphertext[j])) {
                plaintext[j] = substitutions[ciphertext[j] - 'A'];
            } else {
                plaintext[j] = ciphertext[j];
            }
        }
        plaintext[strlen(ciphertext)] = '\0';
        printf("Possible Plaintext %d: %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[] = "LIPPS ASVPH";
    int freq[ALPHABET_SIZE] = {0};
    char letters[ALPHABET_SIZE];
    char substitutions[ALPHABET_SIZE];
    int num_candidates = 10;

    // Initialize letters array
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i] = 'A' + i;
    }

    // Calculate frequencies
    calculate_frequencies(ciphertext, freq);
    
    // Sort letters by frequency
    sort_by_frequency(freq, letters);
    
    // Generate possible substitutions (simple example, swap based on sorted frequency)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitutions[i] = letters[i];
    }
    
    // Generate and print possible plaintexts
    generate_plaintexts(ciphertext, substitutions, num_candidates);

    return 0;
}

