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
        client.connect((self.SERVER_HOST, self.SERVER_PORT))

        while True:
            try:
                server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = server_response.split('@')

                if status == 'OK':
                    print(message)
                
                elif status == "DISCONNECT":
                    print(message)
                    break

                elif status == "ERROR":
                    print(message)

                user_input = input('> ')
                command, *args = user_input.split(' ')

                if command == "HELP":
                    client.send(user_input.encode('utf-8'))

                elif command == "LIST":
                    client.send(user_input.encode('utf-8'))

                elif command == "UPLOAD":
                    if args:
                        try:
                            file_path = args[0]
                            file_name = file_path.split('/')[-1]
                        
                            with open(file_path, 'rb') as f:
                                data = f.read()

                            send_data = f'{command} {file_name} {data}'
                            client.send(user_input.encode('utf-8'))
                            
                        except Exception as e:
                            client.send("INVALID_ARGS_UPLOAD".encode('utf'))

                    else:
                        client.send("INVALID_ARGS_UPLOAD".encode('utf'))

                elif command == "DOWNLOAD":
                    pass

                elif command == "DELETE" :
                    if args:
                        file_name = args[0]
                        send_data = f'{command} {file_name}'
                        client.send(send_data.encode('utf'))

                    else:
                        client.send("INVALID_ARGS_DELETE".encode('utf'))

                    

                elif command == "LOGOUT":
                    client.send(user_input.encode('utf-8'))
                    break

                else:
                    client.send("OTHER".encode('utf'))
            
            except Exception as e:
                print(f'Error raised: {e}')
                break

        print(f'Disconnected from the server.')
        client.close()


if __name__ == '__main__':
    
    client = Client()
    client.connect_to_server() 