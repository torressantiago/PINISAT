/** @file gps.h
 * 
 * @brief Socket library for easy unicity between codes.
 * As per our needs, only a UDP socket server will be developed. 
 *
 * @author Santiago Torres Borda       
 * 
 * @version 1.0
 *
 */ 
#ifndef GPIO_H
#define GPIO_H

#define SERVER_IPADDR "192.168.0.10"
#define PORT 7000
#define MAXLINE 1024 // 10 bit buffer



/*
----Steps for a UDP server----
    1. Create UDP socket.
    2. Bind the socket to server address.
    3. Wait until datagram packet arrives from client.
    4. Process the datagram packet and send a reply to client.
    5. Go back to Step 3.

----Some useful socket functions----
i. Create a socket file descriptor
    int socket(int domain, int type, int protocol)
    -- Args
    -> domain: Specifies the ip protocol  to be used => AF_INET for IPv4 | AF_INET6 for IPv6  
    -> type: Specifies the type of socket to be created => SOCK_STREAM for TCP | SOCK_DGRAM for UDP 
    -> protocol: Specifies the protocol to be used by socket. 0 for the default address family.

ii. Assign an address to the socket file descriptor
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    -- Args
    -> sockfd: File descriptor of the socket to be binded
    -> *addr: Structure in which address to bind is found
    -> addrlen: Size of addr struct.

iii. Send a message
    ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen)
    -- Args
    -> sockfd: File descriptor of the socket.
    -> *buf: Buffer containing data to be sent.
    -> len: Size of buf.
    -> flags: bitwise flags to modify software behaviour.
    -> dest_addr: Destination address to which data will be sent.
    -> addr_len: Size of destination address struct.

iv. Receive a message
    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
    -- Args
    -> sockfd: File descriptor of socket
    -> buf: Application buffer in which to receive data
    -> len: Size of buf application buffer
    -> flags: Bitwise OR of flags to modify socket behaviour
    -> src_addr: Structure containing source address is returned
    -> addrlen: Variable in which size of src_addr structure is returned

v. Close file descriptor
    int close(int fd)
    -- Args
    -> fd: File descriptor
*/

/*Do it all server socket function*/
void udpserv(String servipaddr, int port);


#endif