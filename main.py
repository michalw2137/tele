import huffman
import coder


def binary_to_bytes(binary: str) -> str:
    index = 0
    bytes_ = []
    while index < len(binary) - 8:
        byte = binary[index: index + 8]     # 8 characters long string of 1s and 0s
        bytes_.append(chr(int(byte, 2)))    # char corresponding to int written in binary
        index += 8
    if index < len(binary):
        byte = binary[index: len(binary)]
        bytes_.append(chr(int(byte, 2)))
    return ''.join(bytes_)


if __name__ == '__main__':
    message = "Przykładowa wiadomość. Jebać smolińskiego śmiecia."
    print("ORIGINAL MESSAGE:")
    print(message)

    print("\nCODES FOR SYMBOLS:")
    codes = huffman.get_codes_for_characters_in_message(message)
    print(*codes, sep='\n')

    print("\nCODED MESSAGE IN BINARY:")
    binary = coder.code_message_to_binary_string(message, codes)
    print(binary)

    print("\nORIGINAL MESSAGE:")
    print(f"{len(message)} bytes: {message}")

    print("\nCODED MESSAGE:")
    print(f"{int(len(binary) / 8) + 1} bytes: {binary_to_bytes(binary)}")

