def caesar_cipher(text, shift, mode='encrypt'):
    result = ""

    # Adjust the shift for decryption
    if mode == 'decrypt':
        shift = -shift

    # Loop through each character in the text
    for char in text:
        if char.isalpha():  # Check if the character is a letter
            # Shift within the bounds of uppercase and lowercase letters
            start = ord('A') if char.isupper() else ord('a')
            shifted_char = chr((ord(char) - start + shift) % 26 + start)
            result += shifted_char
        else:
            # If it's not a letter, add it unchanged
            result += char

    return result

# Get user input
text = input("Enter the text: ")
shift = int(input("Enter the shift value: "))
mode = input("Do you want to 'encrypt' or 'decrypt'?: ").strip().lower()

# Validate mode input
if mode not in ['encrypt', 'decrypt']:
    print("Invalid mode! Please enter 'encrypt' or 'decrypt'.")
else:
    # Perform encryption or decryption
    result = caesar_cipher(text, shift, mode)
    print(f"Result: {result}")
