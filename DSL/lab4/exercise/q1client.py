import socket
import time
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
host = socket.gethostname()
port = 12345
#we need to send ANY message to server so that it sends the client address
msg = 'time'
s.sendto(msg.encode(),(host,port))
time, ser_addr = s.recvfrom(1024)
print("Current time: ", time.decode())
s.close