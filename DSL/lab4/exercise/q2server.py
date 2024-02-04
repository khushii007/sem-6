import socket
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
host = socket.gethostname()
port = 12345
s.bind((host,port))
while True:
    print("####### Server is listening #######")
    data, recvAddr = s.recvfrom(1024)
    print("Server received: ", data.decode())
    msg = input("Type some text to send =>")
    print("Server sent: ", msg)
    s.sendto(msg.encode(), recvAddr)

#python3 q2server.py
####### Server is listening #######
#Server received:  Hi
#Type some text to send =>Hello
#Server sent:  Hello
####### Server is listening #######
#Server received:  Bye
#Type some text to send =>!!
#Server sent:  !!
####### Server is listening #######