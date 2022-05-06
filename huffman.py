from node import Node


def get_codes_for_characters_in_message(message: str):
    nodes = get_nodes(message)  # node: distinct symbol and its # of occurences
    print(nodes)
    while len(nodes) > 1:
        nodes = sorted(nodes, key=lambda n: n.freq)  # sort all the nodes based on frequency

        left, right = nodes[0], nodes[1]    # pick 2 smallest nodes
        left.bit, right.bit = 0, 1        # assign directional value to these nodes

        # combine the 2 smallest nodes to create new node as their parent
        newNode = Node(left.symbol + right.symbol, left.freq + right.freq, left, right)

        nodes.remove(left)
        nodes.remove(right)
        nodes.append(newNode)
    # Huffman Tree is ready!
    codes = []
    assign_codes_to_nodes(nodes[0], codes)
    return sorted(codes, key=lambda node: node.freq, reverse=True)


def get_nodes(message: str) -> ():
    nodes = []
    for symbol in message:
        if symbol_is_in_node(symbol, nodes):
            nodes[nodes.index(Node(symbol))].inc()  # symbol is in node - increment frequency
        else:
            nodes.append(Node(symbol))          # create new node for new symbol
    return nodes


def symbol_is_in_node(symbol: str, nodes: list[Node]):
    for node in nodes:
        if node.symbol == symbol:
            return True
    return False


def assign_codes_to_nodes(node: Node, codes: list, code=''):
    new_code = code + str(node.bit)  # huffman code for current node

    if node.left_child:     # node has left child - traverse into it
        assign_codes_to_nodes(node.left_child, codes, new_code)
    if node.right_child:    # node has right child - traverse into it
        assign_codes_to_nodes(node.right_child, codes, new_code)
    else:                   # node is edge node - assign its huffman code and add to codes list
        node.code = new_code
        codes.append(node)
