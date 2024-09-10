#include <stdio.h>

int main() {
    // Initialize the string
    char *str = "Hello world";
    
    // Iterate through each character in the string
    for (int i = 0; str[i] != '\0'; i++) {
        // XOR each character with 0
        char result = str[i] ^ 0;
        
        // Display the result
        printf("%c", result);
    }

    // Newline for better output formatting
    printf("\n");

    return 0;
}

