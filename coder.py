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


