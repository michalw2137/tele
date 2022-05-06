from socket import AF_INET, SOCK_DGRAM, socket

s = socket(AF_INET, SOCK_DGRAM)
s.bind(("192.168.100.43", 69)) # ip i port
received_data = ""
while True:
    (client_data, client_address) = s.recvfrom(1024)
    client_data = client_data.decode('utf-8')
    if client_data == "END":
        s.sendto(client_data.encode('utf-8'), client_address)

    received_data += client_data
    print(client_data)