from datetime import datetime
from socket import AF_INET, SOCK_DGRAM, socket

import coder
import huffman


s = socket(AF_INET, SOCK_DGRAM)
s.bind(("10.128.153.61", 69)) # ip i port
def recieve():
    received_data = ""


    buffer = bytearray(512)

    begin_time = datetime.now()

    i = 0
    while True:
        print(len(buffer))
        client_address = s.recvfrom_into(buffer)
        client_data = buffer.decode('utf-8')

        if client_data[0:3] == "END":
            print("ENDING")
            break

        if client_data[0:5] == "SIZE=":
            print("GETTING SIZE")
            print(client_data[5:8])
            buffer = bytearray(int(client_data[5:8]))
        else:
            received_data += client_data
        print("START-", client_data, "-END\n", sep='')
    return received_data


    # i += 1
# print(received_data)
# rec_codes = recieve()
# print(rec_codes)
rec_message = recieve()
print(rec_message)

# ===================================================== wczytanie i obliczenie kodów dla wzorcowego tekstu

with open("files/huffman_frequency.txt", 'r', encoding="utf-8") as file:
    codes_dictionary = ''.join(file.readlines())
codes = huffman.get_codes_for_characters_in_message(codes_dictionary)
# ===================================================================================

decoded = coder.decode_binary(rec_message, codes)
print(decoded)
with open("files/new_message.txt", 'w', encoding="utf-8") as f:
    f.write(decoded)

