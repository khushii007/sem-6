import socket
import time
serverSock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  #to create socket for udp
udp_host = socket.gethostname() #to get local host ip
udp_port = 12345    #specifying the port to which to connect
serverSock.bind((udp_host, udp_port))   #binding host to the port
while True:
    #In a UDP server, after binding the socket, you typically listen for incoming data and then send a response.
    data, recv_addr = serverSock.recvfrom(1024) #receiving from client and client address
    print("Received message: ", data.decode())
    currTime = time.ctime(time.time()) + "\r\n"
    serverSock.sendto(currTime.encode('ascii'), recv_addr)


# python3 q1server.py
#Received message:  time
