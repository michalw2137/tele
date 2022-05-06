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
        file_coding.write(binary)


def decode(codes: list[Node]):
    with open("files/coded.txt", 'r', encoding="utf-8") as file_decoding:
        lines_ = file_decoding.readlines()
    coded = ''.join(lines_)

    with open("files/read.txt", 'w', encoding="utf-8") as file_decoded:
        file_decoded.write(coded)

    print("\nBINARY READ FROM FILE:")
    binary = coded
    print(binary)

    decoded = coder.decode_message(coded, codes)

    with open("files/decoded.txt", 'w', encoding="utf-8") as file_decoded:
        file_decoded.write(decoded)


if __name__ == '__main__':
    with open("files/pasta.txt", 'r', encoding="utf-8") as file_message:
        lines = file_message.readlines()
    message = ''.join(lines)

    with open("files/huffman_frequency.txt", 'r', encoding="utf-8") as file_message:
        lines_ = file_message.readlines()
    huffman_frequency = ''.join(lines_)

    print("\nCODES FOR SYMBOLS:")
    codes = huffman.get_codes_for_characters_in_message(huffman_frequency)
    print(*codes, sep='\n')

    code(message, codes)
    decode(codes)
