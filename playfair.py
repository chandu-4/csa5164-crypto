def generate_playfair_matrix(key):
    # Remove duplicates from key and create a 5x5 matrix
    key = ''.join(sorted(set(key), key=key.index)).replace('j', 'i')
    alphabet = "abcdefghiklmnopqrstuvwxyz"
    matrix = []

    for char in key:
        if char not in matrix:
            matrix.append(char)

    for char in alphabet:
        if char not in matrix:
            matrix.append(char)

    return [matrix[i:i+5] for i in range(0, len(matrix), 5)]

def find_position(matrix, char):
    for i, row in enumerate(matrix):
        if char in row:
            return i, row.index(char)
    return None

def playfair_cipher(text, key, mode='encrypt'):
    matrix = generate_playfair_matrix(key)
    text = text.replace('j', 'i').replace(' ', '').lower()
    processed_text = []

    # Prepare the text: break into digraphs, insert 'x' between repeating letters
    i = 0
    while i < len(text):
        digraph = text[i]
        if i + 1 < len(text) and text[i] == text[i + 1]:
            digraph += 'x'
        elif i + 1 < len(text):
            digraph += text[i + 1]
            i += 1
        else:
            digraph += 'x'
        processed_text.append(digraph)
        i += 1

    # Encrypt or decrypt the text
    result = []
    for digraph in processed_text:
        row1, col1 = find_position(matrix, digraph[0])
        row2, col2 = find_position(matrix, digraph[1])

        if row1 == row2:
            # Same row, shift columns right (encrypt) or left (decrypt)
            if mode == 'encrypt':
                result.append(matrix[row1][(col1 + 1) % 5] + matrix[row2][(col2 + 1) % 5])
            else:
                result.append(matrix[row1][(col1 - 1) % 5] + matrix[row2][(col2 - 1) % 5])
        elif col1 == col2:
            # Same column, shift rows down (encrypt) or up (decrypt)
            if mode == 'encrypt':
                result.append(matrix[(row1 + 1) % 5][col1] + matrix[(row2 + 1) % 5][col2])
            else:
                result.append(matrix[(row1 - 1) % 5][col1] + matrix[(row2 - 1) % 5][col2])
        else:
            # Rectangle swap
            result.append(matrix[row1][col2] + matrix[row2][col1])

    return ''.join(result)

# User input
key = input("Enter the key: ").lower().replace(' ', '')
text = input("Enter the text: ").lower()
mode = input("Do you want to 'encrypt' or 'decrypt'?: ").strip().lower()

# Validate mode input
if mode not in ['encrypt', 'decrypt']:
    print("Invalid mode! Please enter 'encrypt' or 'decrypt'.")
else:
    # Perform encryption or decryption
    result = playfair_cipher(text, key, mode)
    print(f"Result: {result}")
