import time
from socket import AF_INET, SOCK_DGRAM, socket


def send_string(my_string: str):
    s = socket(AF_INET, SOCK_DGRAM)
    s.connect(("192.168.100.42", 69))  # ip i port
    # my_string = my_string.encode('utf-8')

    i = 0
    buffer_size = 512
    while i + buffer_size < len(my_string):
        string_batch = my_string[i: i+buffer_size]
        print(string_batch)

        i += buffer_size

        s.send(string_batch.encode('utf-8'))
        time.sleep(0.1)

    last_size = len(my_string) - i +1
    # i += last_size
    print(last_size)
    size_info = "SIZE=" + str(last_size)
    s.send(size_info.encode('utf-8'))
    print(size_info)

    last_batch = my_string[i: i+buffer_size]

    print(last_batch)
    s.send(last_batch.encode('utf-8'))

    s.send("END".encode('utf-8'))
