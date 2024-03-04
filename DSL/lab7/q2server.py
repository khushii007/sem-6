import socket
import datetime

def initiate_clock_server():
    s = socket.socket()
    print("Socket successfully created")
    port = 8011
    s.bind(('', port))
    s.listen(5)
    print("Clock server is listening...")

    while True:
        connection, address = s.accept()
        print('Server connected to', address)
        current_time = datetime.datetime.now()
        connection.send(str(current_time).encode())
        connection.close()

if __name__ == '__main__':
    initiate_clock_server()
