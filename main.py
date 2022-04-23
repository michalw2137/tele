import huffman
import coder
from node import Node


def code(message: str, codes: list[Node]):
    print("\nCODED MESSAGE IN BINARY:")
    binary = coder.code_message_to_binary_string(message, codes)
    print(binary)

    print("\nORIGINAL SIZE:\t\tCODED SIZE:\t\t\tSAVED SPACE:")
    print(f"{len(message)} B\t\t\t\t{len(binary) / 8} B\t\t\t\t{len(message) - (int(len(binary) / 8) + 1)} B")

    with open("files/coded.txt", 'w', encoding="utf-8") as file_coding:
        file_coding.write(coder.binary_to_bytes(binary))


def decode(message: str, codes: list[Node]):
    with open("files/coded.txt", 'r', encoding="utf-8") as file_decoding:
        lines_ = file_decoding.readlines()
    coded = ''.join(lines_)

    with open("files/read.txt", 'w', encoding="utf-8") as file_decoded:
        file_decoded.write(coded)

    print("\nBINARY READ FROM FILE:")
    binary_decoded = coder.string_to_binary(coded)
    binary_coded = coder.code_message_to_binary_string(message, codes)
    errors_count = 0
    for i, (b1, b2) in enumerate(zip(binary_decoded, binary_coded)):
        if b1 != b2:
            print(f"{i}) dec: {b1}, c: {b2}")
            errors_count += 1
    print(f"errors: {errors_count}")
    print(binary_decoded)
    print(binary_coded)

    bytes_coded = coder.binary_to_bytes(binary_coded)
    bytes_decoded = coder.binary_to_bytes(binary_decoded)
    errors_count = 0
    for i, (b1, b2) in enumerate(zip(bytes_decoded, bytes_coded)):
        if b1 != b2:
            print(f"{i}) dec: '{ord(b1)}', c: '{ord(b2)}'")
            errors_count += 1
    print(f"errors: {errors_count}")
    print(bytes_decoded)
    print(bytes_coded)

    decoded = coder.decode_message(coded, codes)

    with open("files/decoded.txt", 'w', encoding="utf-8") as file_decoded:
        file_decoded.write(decoded)


if __name__ == '__main__':
    with open("files/pasta.txt", 'r', encoding="utf-8") as file_message:
        lines = file_message.readlines()
    message = ''.join(lines)

    print("\nCODES FOR SYMBOLS:")
    codes = huffman.get_codes_for_characters_in_message(message)
    print(*codes, sep='\n')

    code(message, codes)
    decode(message, codes)
