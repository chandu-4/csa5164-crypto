#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encryptRailFence(char *message, int numRails) {
    int length = strlen(message);
    
    // Create a matrix with numRails rows and length columns
    char **rails = (char **)malloc(numRails * sizeof(char *));
    for (int i = 0; i < numRails; i++) {
        rails[i] = (char *)malloc(length * sizeof(char));
        memset(rails[i], '\0', length * sizeof(char)); // Initialize with '\0'
    }

    int row = 0;
    int direction = 1; // 1 for down, -1 for up
    int current_position = 0;

    // Fill the rail matrix with the message characters
    for (int i = 0; i < length; i++) {
        rails[row][current_position] = message[i];
        current_position++;
        
        // Change direction at the top or bottom rail
        if (direction == 1 && row == numRails - 1) {
            direction = -1;
        } else if (direction == -1 && row == 0) {
            direction = 1;
        }
        row += direction;
    }

    // Print the encrypted message by reading characters row by row
    printf("Encrypted message: ");
    for (int i = 0; i < numRails; i++) {
        for (int j = 0; j < length; j++) {
            if (rails[i][j] != '\0') {
                printf("%c", rails[i][j]);
            }
        }
    }
    printf("\n");

    // Free allocated memory
    for (int i = 0; i < numRails; i++) {
        free(rails[i]);
    }
    free(rails);
}

int main() {
    char message[100];
    int numRails;

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    // Remove newline character from input
    message[strcspn(message, "\n")] = '\0';

    printf("Enter the number of rails: ");
    scanf("%d", &numRails);

    if (numRails < 2) {
        printf("Number of rails must be at least 2.\n");
        return 1;
    }

    encryptRailFence(message, numRails);

    return 0;
}

