#include <stdio.h>

int main() {
    // Initialize the string
    char *str = "Hello world";
    
    // Iterate through each character in the string
    for (int i = 0; str[i] != '\0'; i++) {
        // Perform AND operation with 127
        char and_result = str[i] & 127;
        
        // Perform XOR operation with 127
        char xor_result = str[i] ^ 127;
        
        // Display the results
        printf("Original: %c, AND with 127: %c, XOR with 127: %c\n", str[i], and_result, xor_result);
    }

    return 0;
}

