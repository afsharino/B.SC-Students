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


if __name__ == '__main__':
    
    server = Server()