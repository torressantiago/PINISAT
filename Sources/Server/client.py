#import the socket module
import socket

#create the client socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#send to server using the created UDP socket
msgClient = "Hello Server!"
msgToSend = str.encode(msgClient)
addrPort = ("192.168.4.8", 8080)

client_socket.sendto(msgToSend, addrPort)
msgServer = client_socket.recvfrom(1024)

msg = "Server message {}".format(msgServer[0])
print(msg)
