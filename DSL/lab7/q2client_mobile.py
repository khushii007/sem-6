import socket
import datetime
from dateutil import parser
from timeit import default_timer as timer

def synchronize_time():
    s = socket.socket()
    port = 8011
    s.connect(('127.0.0.1', port))
    request_time = timer()
    server_time = parser.parse(s.recv(1024).decode())
    print("Time returned by server; " + str(server_time))

    response_time = timer()

    process_delay_latency = response_time - request_time
    print("Process delay latency: " + str(process_delay_latency) + " seconds")


    actual_time = datetime.datetime.now()
    print("Actual clock time at client side: " + str(actual_time))

    
    # Adjust client time using process delay latency

    client_time = server_time + datetime.timedelta(seconds=(process_delay_latency) / 2)
    print("Mobile - Synchronized time:", client_time)

    error = actual_time - client_time
    print("Mobile - Synchronization error:", error.total_seconds(), "seconds")
    s.close()

if __name__ == '__main__':
    synchronize_time()
