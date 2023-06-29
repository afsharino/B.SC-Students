# Import Libraries
import os
import socket
import threading

class Client():
    def __init__(self) -> None:
        self.SERVER_HOST = '127.0.1.1'
        self.SERVER_PORT = 9090
        self.BUFFER_SIZE = 4096

        

    
    def connect_to_server(self):
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f'Trying to connect to the server...')
        client.connect((self.SERVER_HOST, self.SERVER_PORT))

        while True:
            server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
            status, message = server_response.split('@')

            if status == 'OK':
                print(message)
            
            elif status == "ERROR":
                print(message)


if __name__ == '__main__':
    
    client = Client()
    client.connect_to_server()