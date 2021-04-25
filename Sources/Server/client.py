#import the socket module
import socket

#create the client socket
client.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#send to server using the created UDP socket
msgClient = "Hello Server!"
msgToSend = str.encode(msgClient)
addrPort = ("192.168.0.1", 8080)

s.sendto(msgToSend, addrPort)
msgServer = s.recvfrom(1024)

msg = "Server message {}".format(msgServer[0])
print(msg)