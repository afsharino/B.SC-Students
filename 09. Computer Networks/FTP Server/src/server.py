# Import Libraries
import os
import socket
import threading

class Server():
    def __init__(self) -> None:
        self.SERVER_HOST = socket.gethostbyname(socket.gethostname())
        self.SERVER_PORT = 9090
        self.BUFFER_SIZE = 4096
        self.SERVER_FILES_DIR = 'server_files/'

        self.start_server()

    def start_server(self) -> None:
        print(f'Server is starting...')
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind((self.SERVER_HOST, self.SERVER_PORT))
        server_socket.listen(5)
        print(f'Server listening on {self.SERVER_HOST}:{self.SERVER_PORT}')

        while True:
            client_socket, client_address = server_socket.accept()
            client_thread = threading.Thread(target=self.handle_client, args=(client_socket, client_address))
            client_thread.start()

        server_socket.close()
    
    def handle_client(self, client_socket, client_address):
        print(f'New connection established on  {client_address[0]}:{client_address[1]}')
        client_socket.send("OK@>> WELCOME TO THE FTP SERVER <<".encode('utf-8'))

if __name__ == '__main__':
    
    server = Server()