# Import Libraries
import os
import socket
import threading
from datetime import datetime

class Server():
    def __init__(self) -> None:
        self.SERVER_HOST = socket.gethostbyname(socket.gethostname())
        self.SERVER_PORT = 9090
        self.BUFFER_SIZE = 4096
        self.SERVER_FILES_DIR = '/home/afsharino/Desktop/server_files/'

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

        while True:

            client_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
            command, *args = client_response.split(' ')
            print(f'Client requested to {command}')

            if command == 'AUTH':
                if len(args) != 2:
                    client_socket.send('OK@Invalid credentials.\n'.encode('utf-8'))
                    
                else:
                    username, password = args

                    if self.authenticate_user(username, password):
                        client_socket.send('OK@Authentication successful.\n'.encode('utf-8'))

                    else:
                        client_socket.send('OK@Authentication failed.\n'.encode('utf-8'))

            elif command == "HELP":
                server_response = f'OK@' +\
                f'LIST: To list all files in the server\n' +\
                f'UPLOAD <path>: To upload a file to the server\n' +\
                f'DOWNLOAD <file_name>: To download file from the server\n' +\
                f'DELETE <file_name>: To delete a file from the server\n' +\
                f'LOGOUT: To disconncet from the server\n' +\
                f'HELP: To list all commands and their functionality\n'

                client_socket.send(server_response.encode('utf-8'))

            elif command == "LOGOUT":
                break

            elif command == "DELETE":
                try:
                    files = os.listdir(self.SERVER_FILES_DIR)
                    server_response = f'OK@' 

                    if files:
                        if args[0] in files:
                            os.system(f'rm {self.SERVER_FILES_DIR}/{args[0]}')
                            server_response += f'{args[0]} deleted from server successfully\n'
                        else:
                            server_response += f'{args[0]} not found\n'

                    else:
                        server_response += "There is no file available on the server.\n"

                    client_socket.send(server_response.encode('utf-8'))
                
                except Exception as e:
                    print(f'Error raised: {e}')
                    server_response= f'ERROR@Server is not responding.\n'
                    client_socket.send(server_response.encode('utf-8'))

            elif command == "LIST":
                try:
                    files = os.listdir(self.SERVER_FILES_DIR)
                    server_response = f'OK@FILE_NAME\t\t\t\t\t\tCREATED_DATE\t\tMODIFIED_DATE\t\tFILE_SIZE\n' 
                    
                    if files:
                        longest_name = Server.find_longest_name(files)
                        for file_name in files:
                            filepath = os.path.join(self.SERVER_FILES_DIR, file_name)
                            file_created = datetime.fromtimestamp(os.path.getctime(filepath)).strftime('%Y-%m-%d %H:%M:%S')
                            file_modefied = datetime.fromtimestamp(os.path.getmtime(filepath)).strftime('%Y-%m-%d %H:%M:%S') 
                            file_size = os.path.getsize(filepath)
                            file_size = Server.human_readable(file_size)
                            
                            file_name += (len(longest_name) - len(file_name)) * ' '
                            server_response += '\t'.join([file_name, file_created, file_modefied, file_size]) + '\n'

                    client_socket.send(server_response.encode('utf-8'))
                
                except Exception as e:
                    print(f'Error raised: {e}')
                    server_response= f'ERROR@Server is not responding.\n'
                    client_socket.send(server_response.encode('utf-8'))
            
            elif command == "UPLOAD":
                pass 
            elif command == "OTHER":
                server_response = f'OK@Command not found.\nNOTE: commands are case sensetive\n' +\
                f'To see available commands enter "HELP" command.\n'
                client_socket.send(server_response.encode('utf-8'))

            elif command == "INVALID_ARGS_DELETE":
                server_response = f'OK@Enter file name to delete.\n'
                client_socket.send(server_response.encode('utf-8'))

            elif command == "INVALID_ARGS_UPLOAD":
                server_response = f'OK@Enter Valid file path.\n'
                client_socket.send(server_response.encode('utf-8'))
            
            elif command == "INVALID_ARGS_DELETE":
                server_response = f'OK@Enter file name to delete.\n'
                client_socket.send(server_response.encode('utf-8'))
            

            else:
                break
        
        print(f'{client_address[0]}:{client_address[1]} Disconnected from the server.')

    def authenticate_user(self, usrname, passwd):
        pass            
    
    @classmethod
    def human_readable(cls, num, suffix="B"):
        for unit in ("", "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi"):
            if abs(num) < 1024.0:
                return f"{num:3.1f} {unit}{suffix}"
            num /= 1024.0
        return f"{num:.1f}Yi{suffix}"
    
    @classmethod
    def find_longest_name(cls, names):
        longest = ''

        for name in names:
            if len(name) > len(longest):
                longest = name

        return longest


if __name__ == '__main__':
    
    server = Server()