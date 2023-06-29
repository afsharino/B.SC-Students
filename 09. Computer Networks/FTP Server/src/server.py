# Import Libraries
import os
import socket
import threading

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

            if command == "HELP":
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
                            server_response += f'{args[0]} deleted from server successfully'
                        else:
                            server_response += f'{args[0]} not found'

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
                    server_response = f'OK@' 

                    if files:
                        server_response += '\n'.join(file for file in files) + '\n'

                    else:
                        server_response += "There is no file available on the server.\n"

                    client_socket.send(server_response.encode('utf-8'))
                
                except Exception as e:
                    print(f'Error raised: {e}')
                    server_response= f'ERROR@Server is not responding.\n'
                    client_socket.send(server_response.encode('utf-8'))

            elif command == "OTHER":
                server_response = f'OK@Command not found.\nTo see available commands enter "HELP" command.\n'
                client_socket.send(server_response.encode('utf-8'))

            else:
                break
        
        print(f'{client_address[0]}:{client_address[1]} Disconnected from the server.')


                


if __name__ == '__main__':
    
    server = Server()