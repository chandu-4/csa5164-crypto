#include <stdio.h>
#include <math.h>

// Function to calculate gcd
int gcd(int a, int b) {
    int temp;
    while (1) {
        temp = a % b;
        if (temp == 0)
            return b;
        a = b;
        b = temp;
    }
}

// Function to perform modular exponentiation (m^e mod n)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Two large prime numbers p and q (for simplicity, using small primes here)
    int p = 61;
    int q = 53;
    int n = p * q; // n = p * q
    int phi = (p - 1) * (q - 1); // Euler's totient function

    // Public key exponent 'e' (Choose e such that 1 < e < phi and gcd(e, phi) = 1)
    int e = 17;

    // Private key exponent 'd' (d = e^(-1) (mod f(n)))
    int d = 0;
    int k = 1; // k is any integer
    while (1) {
        if ((k * phi + 1) % e == 0) {
            d = (k * phi + 1) / e;
            break;
        }
        k++;
    }

    printf("Public Key (e, n) = (%d, %d)\n", e, n);
    printf("Private Key (d, n) = (%d, %d)\n", d, n);

    // Input message (a small number representing the message)
    char message[100];
    printf("Enter a message (single character): ");
    scanf("%s", message);
    
    int m = message[0]; // Convert first character to an integer (ASCII value)

    // Encryption: c = (m^e) mod n
    long long encrypted = mod_exp(m, e, n);
    printf("Encrypted message: %lld\n", encrypted);

    // Decryption: m = (c^d) mod n
    long long decrypted = mod_exp(encrypted, d, n);
    printf("Decrypted message: %c\n", (char)decrypted);

    return 0;
}

