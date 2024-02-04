import socket
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
host = socket.gethostname()
port = 12345
while True:
    msg = input("Type some text to send =>")
    print("Client sent: ", msg)
    s.sendto(msg.encode(),(host,port))
    rcv_msg, serAddr = s.recvfrom(1024)
    print("Client received: ", rcv_msg.decode())


#Type some text to send =>Hi
#Client sent:  Hi
#Client received:  Hello
#Type some text to send =>Bye
#Client sent:  Bye
#Client received:  !!    