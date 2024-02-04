import socket
serverIP = 'localhost' 
serverPort = 16000
clientSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
clientSock.connect((serverIP, serverPort))
message = input("Input integers with space in between: ") #raw_input change
message2 = input("Enter the length of the set: ")
clientSock.send(message.encode()) #encode change because a bytes like object needs to be passed
clientSock.send(message2.encode())
data = clientSock.recv(1024)
temp = [float(x) for x in data.decode().split()] #decode
print("The total of all numbers is: " + str(temp[0])) 
print("The lowest number is: " + str(temp[1])) 
print("The highest number is: " + str(temp[2]))
print("The mean is: " + str(temp[3]))
clientSock.close()