#import the socket module
import socket

#create the server socket
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

Host = '192.168.0.1' # local IP address 
Port = 8080          # port
 
#binding the socket with the server address
server_socket.bind((Host,Port))
print("Server listening")

#listen to incoming datagrams
while(True):
    addr = server_socket.recvfrom(1024, MSG_WAITALL)
    message = addr[0]
    address = addr[1]
    clientMsg = "Client msg : {}".format(message)
    clientAddr = "Client addr : {}".format(address)
    print(clientMsg)
    print(clientAddr)

    #send response
    msg = str.encode("Hello Client!")
    s.sendto(msg, address)

