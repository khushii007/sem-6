from timeit import default_timer as timer
from dateutil import parser
import socket
import threading
import datetime
import time

def start_sending_time(slave_client):
    while True:
        current_time = datetime.datetime.now()
        slave_client.send(str(current_time).encode())
        print("Recent time sent successfully")
        time.sleep(5)

def start_receiving_time(slave_client):
    while True:
        synchronized_time = parser.parse( slave_client.recv(1024).decode())
        print("Synchronized time at the client is: " + str(synchronized_time), end="\n\n")

def initiate_slave_client(server_ip, server_port):
    slave_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
    slave_client.connect((server_ip, server_port))
    print("Connected to server")

    print("Starting to receive time from server\n")
    send_time_thread = threading.Thread(target=start_sending_time, args=(slave_client,))
    send_time_thread.start()

    print("Starting to receiving synchronized time from server\n")
    receive_time_thread = threading.Thread(target=start_receiving_time, args=(slave_client,))
    receive_time_thread.start()

if __name__ == '__main__':
    server_ip = '127.0.0.1'  # Replace with the IP address of the master clock server
    server_port = 8080  # Replace with the port number the master clock server is listening on

    initiate_slave_client(server_ip, server_port)
