# Import Libraries
import os
import socket
import threading

class Client():
    def __init__(self) -> None:
        self.SERVER_HOST = '127.0.1.1'
        self.SERVER_PORT = 9090
        self.BUFFER_SIZE = 4096


if __name__ == '__main__':
    
    server = Client()