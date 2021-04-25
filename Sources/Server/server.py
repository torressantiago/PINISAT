#import the socket module
import socket
import sys

#create the server socket
server_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

Host = sys.argv[1] # local IP address 
print(Host)
Port = 8080          # port
 
#binding the socket with the server address
server_socket.bind((Host,Port))
print("Server listening")

#listen to incoming datagrams
while(True):
    data, addr = server_socket.recvfrom(1024)
    message = data
    address = addr
    clientMsg = "Client msg : {}".format(message)
    clientAddr = "Client addr : {}".format(address)
    print(clientMsg)
    print(clientAddr)

    #send response
    msg = str.encode("Hello Client!")
    server_socket.sendto(msg, address)