from socket import AF_INET, SOCK_DGRAM, socket

s = socket(AF_INET, SOCK_DGRAM)
s.connect(("192.168.100.43", 69)) # ip i port
my_string = "test"
s.send(my_string.encode('utf-8'))
