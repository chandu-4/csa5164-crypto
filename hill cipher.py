import numpy as np

def create_key_matrix(key, block_size):
    key = key.replace(" ", "").lower()
    key_matrix = []
    
    for i in range(block_size):
        row = [ord(key[block_size * i + j]) - ord('a') for j in range(block_size)]
        key_matrix.append(row)

    return np.array(key_matrix)

def mod_inverse(matrix, modulus):
    det = int(np.round(np.linalg.det(matrix))) % modulus
    det_inv = pow(det, -1, modulus)
    matrix_modulus_inv = det_inv * np.round(det * np.linalg.inv(matrix)).astype(int) % modulus
    return matrix_modulus_inv

def hill_cipher(text, key_matrix, block_size, mode='encrypt'):
    text = text.replace(" ", "").lower()
    
    # Pad text if necessary
    while len(text) % block_size != 0:
        text += 'x'

    # Convert text into blocks of integers
    text_blocks = [text[i:i+block_size] for i in range(0, len(text), block_size)]
    text_vectors = [np.array([ord(char) - ord('a') for char in block]) for block in text_blocks]
    
    result = []
    for vector in text_vectors:
        if mode == 'encrypt':
            transformed_vector = np.dot(key_matrix, vector) % 26
        elif mode == 'decrypt':
            inv_key_matrix = mod_inverse(key_matrix, 26)
            transformed_vector = np.dot(inv_key_matrix, vector) % 26
        else:
            raise ValueError("Invalid mode. Choose 'encrypt' or 'decrypt'.")
        
        result_block = ''.join([chr(int(num) + ord('a')) for num in transformed_vector])
        result.append(result_block)
    
    return ''.join(result)

# User input
key = input("Enter the key (without spaces, length should be a perfect square): ").lower()
text = input("Enter the text: ").lower()
mode = input("Do you want to 'encrypt' or 'decrypt'?: ").strip().lower()

block_size = int(len(key) ** 0.5)

if len(key) != block_size ** 2:
    print("Invalid key length! The key length must be a perfect square.")
else:
    # Create the key matrix
    key_matrix = create_key_matrix(key, block_size)

    # Perform encryption or decryption
    result = hill_cipher(text, key_matrix, block_size, mode)
    print(f"Result: {result}")
