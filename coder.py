from node import Node


def code_message_to_binary_string(message: str, codes: list[Node]) -> str:
    coded = []
    for char in message:
        coded.append(code_symbol(char, codes))
    while len(''.join(coded)) % 8 != 0:
        print(len(''.join(coded)))
        coded.append(code_symbol(' ', codes))
        print(f"added ' ' -> {code_symbol(' ', codes)}")
    return ''.join(coded)


def code_symbol(symbol: str, codes: list[Node]):
    for code in codes:
        if symbol == code.symbol:
            return code.code
    raise IndexError("Symbol not found in codes list!")


def binary_to_bytes(binary: str) -> str:
    index = 0
    bytes_ = []
    while index < len(binary) - 8:
        byte = binary[index: index + 8]     # 8 characters long string of 1s and 0s
        bytes_.append(chr(int(byte, 2)))    # char corresponding to int written in binary
        index += 8

    if index < len(binary):                 # last, less than 8, bits
        byte = binary[index: len(binary)]
        bytes_.append(chr(int(byte, 2)))

    return ''.join(bytes_)


def decode_message(message: str, codes: list[Node]) -> str:
    return decode_binary(string_to_binary(message), codes)


def string_to_binary(message: str) -> str:
    binary = []
    for char in message:
        binary.append(format(ord(char), '08b'))
    return ''.join(binary)


def decode_binary(binary: str, codes: list[Node]) -> str:
    start, end = 0, 1
    decoded = []
    while end < len(binary):
        symbol = code_exists(binary[start: end], codes)
        if symbol != '':
            start = end
            end += 1
            decoded.append(symbol)
        else:
            end += 1
    return ''.join(decoded)


def code_exists(binary: str, codes: list[Node]):
    for code in codes:
        if binary == code.code:
            return code.symbol
    return ''
