import string

def generate_cipher_alphabet(key):
    """Generate a cipher alphabet based on the provided key."""
    key = ''.join(sorted(set(key), key=key.index))  # Remove duplicates, maintain order
    alphabet = string.ascii_lowercase
    cipher_alphabet = key + ''.join([c for c in alphabet if c not in key])
    return cipher_alphabet

def monoalphabetic_cipher(text, cipher_alphabet, mode='encrypt'):
    alphabet = string.ascii_lowercase
    result = []

    if mode == 'decrypt':
        cipher_alphabet, alphabet = alphabet, cipher_alphabet

    translation_table = str.maketrans(alphabet, cipher_alphabet)

    for char in text.lower():
        if char in alphabet:
            result.append(char.translate(translation_table))
        else:
            result.append(char)  # Non-alphabet characters remain unchanged

    return ''.join(result)

# User input
key = input("Enter a key (unique letters for the cipher): ").lower()
text = input("Enter the text: ").lower()
mode = input("Do you want to 'encrypt' or 'decrypt'?: ").strip().lower()

# Validate mode input
if mode not in ['encrypt', 'decrypt']:
    print("Invalid mode! Please enter 'encrypt' or 'decrypt'.")
else:
    # Generate the cipher alphabet using the provided key
    cipher_alphabet = generate_cipher_alphabet(key)

    # Perform encryption or decryption
    result = monoalphabetic_cipher(text, cipher_alphabet, mode)
    print(f"Result: {result}")