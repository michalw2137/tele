from node import Node


def code_message_to_binary_string(message: str, codes: list[Node]) -> str:
    coded = []
    for char in message:
        coded.append(code_symbol(char, codes))
    return ''.join(coded)


def code_symbol(symbol: str, codes: list[Node]):
    for code in codes:
        if symbol == code.symbol:
            return code.code
    raise IndexError("Symbol not found in codes list!")


def decode_message(message: str, codes: list[Node]) -> str:
    return decode_binary(string_to_binary(message), codes)


def string_to_binary(message: str) -> str:
    binary = []
    for char in message:
        binary.append(format(ord(char), '08b'))
    return ''.join(binary)


def decode_binary(binary: str, codes: list[Node]) -> str:
    start, end = 1, 0
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
