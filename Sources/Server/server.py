#import the socket module
import socket

#create the socket
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

Host = '192.168.0.1' # local IP address 
Port = 8080          # port
 
#binding the socket (to be able to recieve connections)
server_socket.bind((Host,Port))

#listening for incoming connections
server_socket.listen(5000)

#next steps : accept connection and recieve data