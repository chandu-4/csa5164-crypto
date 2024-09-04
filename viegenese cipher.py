def generate_vigenere_table():
    # Create a Vigenère table (26x26)
    table = []
    for i in range(26):
        row = [(chr(((i + j) % 26) + ord('A'))) for j in range(26)]
        table.append(row)
    return table

def vigenere_cipher(text, key, mode='encrypt'):
    table = generate_vigenere_table()
    text = text.upper().replace(' ', '')
    key = key.upper().replace(' ', '')
    key_repeated = (key * (len(text) // len(key))) + key[:len(text) % len(key)]
    result = []

    for i in range(len(text)):
        text_char = text[i]
        key_char = key_repeated[i]
        if text_char.isalpha():
            if mode == 'encrypt':
                row = ord(key_char) - ord('A')
                col = ord(text_char) - ord('A')
                result.append(table[row][col])
            elif mode == 'decrypt':
                row = ord(key_char) - ord('A')
                col = table[row].index(text_char)
                result.append(chr(col + ord('A')))
        else:
            result.append(text_char)

    return ''.join(result)

# User input
text = input("Enter the text: ").upper()
key = input("Enter the key: ").upper()
mode = input("Do you want to 'encrypt' or 'decrypt'?: ").strip().lower()

# Validate mode input
if mode not in ['encrypt', 'decrypt']:
    print("Invalid mode! Please enter 'encrypt' or 'decrypt'.")
else:
    # Perform encryption or decryption
    result = vigenere_cipher(text, key, mode)
    print(f"Result: {result}")
