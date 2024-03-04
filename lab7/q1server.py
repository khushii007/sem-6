from functools import reduce
from dateutil import parser
import socket
import threading
import datetime
import time

clock_data = {}

def start_receiving_clock_time(connector, address):
    while True:
        clock_time_string = connector.recv(1024).decode()
        clock_time = parser.parse(clock_time_string)
        clock_time_diff = datetime.datetime.now() - clock_time

        clock_data[address] = {
            "clock_time" : clock_time,
            "time_difference" : clock_time_diff,
            "connector" : connector
        }

        print("Client data updated with: " + str(address), end="\n\n")
        time.sleep(5)

def start_connecting(master_server):
    while True:
        master_slave_connector, addr = master_server.accept()
        institute_address = str(addr[0]) + ":" + str(addr[1])

        print(institute_address + " got connected successfully")

        current_thread = threading.Thread(
            target=start_receiving_clock_time,
            args=(master_slave_connector, institute_address,)
        )
        current_thread.start()

def get_average_clock_diff():
    current_clock_data = clock_data.copy()
    time_difference_list = [client['time_difference'] for client_addr, client in current_clock_data.items()]

    sum_of_clock_difference = sum(time_difference_list, datetime.timedelta(0, 0))
    average_clock_difference = sum_of_clock_difference / len(current_clock_data)

    return average_clock_difference

def synchronize_all_clocks():
    while True:
        print("New synchronization cycle started.")
        print("Number of clients to be synchronized: " + str(len(clock_data)))

        if len(clock_data) > 0:
            average_clock_difference = get_average_clock_diff()

            for client_addr, client in clock_data.items():
                try:
                    synchronized_time = datetime.datetime.now() + average_clock_difference
                    client['connector'].send(str(synchronized_time).encode())
                except Exception as e:
                    print("Something went wrong while sending synchronized time through" + str(client_addr))
        else:
            print("No client data. \nSynchronization not applicable.")

        print("\n\n")


        time.sleep(5)

def initiate_clock_server(port=8080):
    master_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    master_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    print("Socket at master node created successfully")
    master_server.bind(('', port))
    master_server.listen(10)
    print("Clock server started...")

    print("Starting to make connections...")
    master_thread = threading.Thread(target=start_connecting, args=(master_server,))
    master_thread.start()

    print("Starting synchronization parallely...")
    sync_thread = threading.Thread(target=synchronize_all_clocks, args=())
    sync_thread.start()

if __name__ == '__main__':
    initiate_clock_server(port=8080)
