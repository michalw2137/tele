class Node:
    def __init__(self, frequency: float, symbol: str, left_child=None, right_child=None):
        self.frequency = frequency
        self.symbol = symbol
        self.left_child = left_child
        self.right_child = right_child
        self.byte = ""
        self.code = ""

    def __str__(self):
        return f"'{self.symbol}' -> {self.code}"

    def __repr__(self):
        return self.__str__()


def assign_codes_to_nodes(node: Node, codes: list, code=''):
    # huffman code for current node
    new_code = code + str(node.byte)

    # if node is not an edge node
    # then traverse inside it
    if node.left_child:
        assign_codes_to_nodes(node.left_child, codes, new_code)
    if node.right_child:
        assign_codes_to_nodes(node.right_child, codes, new_code)

    # if node is edge node then
    # display its huffman code
    if not node.left_child and not node.right_child:
        node.code = new_code
        codes.append(node)


class Char:
    def __init__(self, character: str):
        self.character = character
        self.occurences = 1

    def inc(self):
        self.occurences += 1

    def __str__(self):
        return f"'{self.character}': {self.occurences}"

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        if isinstance(other, Char):
            return self.character == other.character
        else:
            return False


def is_in_list(_list: list[Char], element: str):
    for c in _list:
        if c.character == element:
            return True
    return False


def count_characters(mess: str) -> ():
    chars = []
    for character in mess:
        if is_in_list(chars, character):
            chars[chars.index(Char(character))].inc()
        else:
            chars.append(Char(character))
    return chars


def code_symbol(symbol: str, codes: list[Node]):
    for code in codes:
        if symbol == code.symbol:
            return code.code
    raise IndexError("Symbol not found in codes list!")


def code_message(message: str, codes: list[Node]) -> str:
    coded = []
    for char in message:
        coded.append(code_symbol(char, codes))
    return ''.join(coded)


def split_into_bytes(coded: str):
    index = 0
    bytes = []
    while index < len(coded) - 8:
        byte = coded[index: index + 8]
        bytes.append(chr(int(byte, 2)))
        index += 8
    if index < len(coded):
        byte = coded[index: len(coded)]
        bytes.append(chr(int(byte, 2)))
    return bytes


if __name__ == '__main__':
    message = "Przykładowa wiadomość. Jebać smolińskiego śmiecia."
    print("ORIGINAL MESSAGE:")
    print(message)
    characters = count_characters(message)
    characters = sorted(characters, key=lambda s: s.occurences)
    print("\nNUMBER OF OCCURENCES OF EACH SYMBOL")
    for c in characters:
        print(c)

    chars = []
    freq = []

    for char in characters:
        chars.append(char.character)
        freq.append(char.occurences)

    # list containing unused nodes
    nodes = []

    # converting characters and frequencies
    # into huffman tree nodes
    for i in range(len(chars)):
        nodes.append(Node(freq[i], chars[i]))

    while len(nodes) > 1:
        # sort all the nodes in ascending order
        # based on theri frequency
        nodes = sorted(nodes, key=lambda x: x.frequency)

        # pick 2 smallest nodes
        left = nodes[0]
        right = nodes[1]

        # assign directional value to these nodes
        left.byte = 0
        right.byte = 1

        # combine the 2 smallest nodes to create
        # new node as their parent
        newNode = Node(left.frequency + right.frequency, left.symbol + right.symbol, left, right)

        # remove the 2 nodes and add their
        # parent as new node among others
        nodes.remove(left)
        nodes.remove(right)
        nodes.append(newNode)

    # Huffman Tree is ready!
    codes = []
    assign_codes_to_nodes(nodes[0], codes)
    print("\nCODES FOR SYMBOLS:")
    print(codes)
    coded = code_message(message, codes)
    print("\nCODED MESSAGE IN BINARY:")
    print(coded)
    bytes = split_into_bytes(coded)
    print("\nORIGINAL MESSAGE:")
    print(f"{len(message) * 8} bytes: {message}")
    print("\nCODED MESSAGE:")
    print(f"{len(coded)} bytes: ", end='')
    print(''.join(bytes))
