# Import Libraries
import os
import socket
import threading

class Client():
    def __init__(self) -> None:
        self.SERVER_HOST = '127.0.1.1'
        self.SERVER_PORT = 9090
        self.BUFFER_SIZE = 4096
        self.CLIENT_SOCKET = None


    def connect_to_server(self):
        self.CLIENT_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.CLIENT_SOCKET.connect((self.SERVER_HOST, self.SERVER_PORT))

        while True:
            server_response = self.CLIENT_SOCKET.recv(self.BUFFER_SIZE).decode('utf-8')
            status, message = server_response.split('@')
            
            if status == 'AUTHENTICATE':
                print(f'{message}')
                user_name = input('> User Name: ')
                password = input('> Password: ')

                self.CLIENT_SOCKET.send(f'{user_name} {password}'.encode('utf-8'))

                server_response = self.CLIENT_SOCKET.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = server_response.split('@')

                if status == 'OK':
                    print(f'{message}')
                    break
                else:
                    print(f'{message}')

        self.handle_client(self.CLIENT_SOCKET)

    def handle_client(self, client_socket):
        while True:
            try:
                user_input = input('> ')
                command, *args = user_input.split(' ')

                if command == "HELP":
                    self.get_help(client_socket, user_input)
                
                elif command == "LIST":
                    self.list_files(client_socket, user_input)

                elif command == "UPLOAD":
                    self.upload_file(client_socket, command, args)

                elif command == "DOWNLOAD":
                    self.download_file(client_socket, command, args)

                elif command == "DELETE" :
                    self.delete_file(client_socket, command, args)

                elif command == "LOGOUT":
                    client_socket.send(user_input.encode('utf-8'))
                    break

                else:
                    self.other(client_socket)

            except Exception as e:
                print(f'Error raised: {e}')
                break

        print(f'Disconnected from the server.')
        client_socket.close()

    def get_help(self, client_socket, user_input):
        client_socket.send(user_input.encode('utf-8'))

        server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
        status, message = server_response.split('@')

        if status == 'OK':
            print(f'{message}')  

        elif status == "ERROR":
            print(f'<ERROR> {message}')
    
    def list_files(self, client_socket, user_input):
        client_socket.send(user_input.encode('utf-8'))

        server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
        status, message = server_response.split('@')

        if status == 'OK':
            print(f'{message}')  

        elif status == "ERROR":
            print(f'<ERROR> {message}')

    def upload_file(self, client_socket, command, args):
        if args:
            try:
                file_path = args[0]
                file_name = file_path.split('/')[-1]
                file_size = os.path.getsize(file_path)

                send_data = f'{command} {file_name} {file_size}'
                client_socket.send(send_data.encode('utf-8'))

                with open(file_path, 'rb') as f:
                    data = f.read()
                    client_socket.sendall(data)
                
                server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = server_response.split('@')

                if status == 'OK':
                    print(f'{message}')  

                elif status == "ERROR":
                    print(f'<ERROR> {message}')
                
            except Exception as e:
                print(f"Error Raised: {e}")
                client_socket.send("INVALID_ARGS_UPLOAD".encode('utf-8'))
                server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = server_response.split('@')

                if status == 'OK':
                    print(f'{message}')  

                elif status == "ERROR":
                    print(f'<ERROR> {message}')

        else:
            client_socket.send("INVALID_ARGS_UPLOAD".encode('utf-8'))

    def download_file(self, client_socket,command, args):
        if args:
            try:
                file_name = args[0]
                file_path = args[1]

                send_data = f'{command} {file_name}'
                client_socket.send(send_data.encode('utf-8'))
                
                response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = response.split('@')
                print(f"Trying to download...")

                if file_name in os.listdir(file_path):
                    file_name = file_name.split('.')
                    file_name = file_name[0] + 'copy.' + file_name[1]
                    file_path = os.path.join(file_path, file_name)

                else:
                    file_path = os.path.join(file_path, file_name)

                file_size = int(message)

                if status == "ACCEPTED":
                    client_socket.send("START".encode('utf-8'))
                    print("Download Started")

                    with open(file_path, 'wb') as f:
                        bytes_received = 0
                        while bytes_received < file_size:
                            data = client_socket.recv(self.BUFFER_SIZE)
                            if not data:
                                break
                            f.write(data)
                            bytes_received += len(data)

                print(f'{file_name} downloaded successfully!\n')
                
            except Exception as e:
                print(e)
                client_socket.send("INVALID_ARGS_DOWNLOAD".encode('utf-8'))
                server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = server_response.split('@')

                if status == 'OK':
                    print(f'{message}')  

                elif status == "ERROR":
                    print(f'<ERROR> {message}')

        else:
            client_socket.send("INVALID_ARGS_DOWNLOAD".encode('utf-8'))

    def delete_file(self, client_socket, command, args):
        if args:
            file_name = args[0]
            send_data = f'{command} {file_name}'

            client_socket.send(send_data.encode('utf'))

            server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
            status, message = server_response.split('@')

            if status == 'OK':
                print(f'{message}')  

            elif status == "ERROR":
                print(f'<ERROR> {message}')
        else:
            client_socket.send("INVALID_ARGS_DELETE".encode('utf-8'))

    def other(self, client_socket):
        client_socket.send("OTHER".encode('utf-8'))

        server_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
        status, message = server_response.split('@')

        if status == 'OK':
            print(f'{message}')  

        elif status == "ERROR":
            print(f'<ERROR> {message}')

if __name__ == '__main__':
    
    client = Client()
    print(f"Welcome to FTP client app\n")
    client.connect_to_server() 