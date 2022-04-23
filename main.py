import huffman
import coder
from node import Node


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


def code(message: str, codes: list[Node]):
    print("\nCODED MESSAGE IN BINARY:")
    binary = coder.code_message_to_binary_string(message, codes)
    print(binary)

    print("\nORIGINAL SIZE:\t\tCODED SIZE:\t\t\tSAVED SPACE:")
    print(f"{len(message)} B\t\t\t\t{int(len(binary) / 8) + 1} B\t\t\t\t{len(message) - (int(len(binary) / 8) + 1)} B")

    with open("files/coded.txt", 'w', encoding="utf-8") as file_coding:
        file_coding.write(binary_to_bytes(binary))


def decode(codes: list[Node]):
    with open("files/coded.txt", 'r', encoding="utf-8") as file_decoding:
        lines_ = file_decoding.readlines()
    coded = ''.join(lines_)

    decoded = coder.decode_message(coded, codes)

    with open("files/decoded.txt", 'w', encoding="utf-8") as file_decoded:
        file_decoded.write(decoded)


if __name__ == '__main__':
    with open("files/message_pl.txt", 'r', encoding="utf-8") as file_message:
        lines = file_message.readlines()
    message = ''.join(lines)

    print("\nCODES FOR SYMBOLS:")
    codes = huffman.get_codes_for_characters_in_message(message)
    print(*codes, sep='\n')

    code(message, codes)
    decode(codes)
