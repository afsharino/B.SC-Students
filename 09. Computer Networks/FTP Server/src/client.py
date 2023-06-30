# Import Libraries
import os
import socket
import threading

class Client():
    def __init__(self) -> None:
        self.SERVER_HOST = '127.0.1.1'
        self.SERVER_PORT = 9092
        self.BUFFER_SIZE = 4096


    def connect_to_server(self):
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect((self.SERVER_HOST, self.SERVER_PORT))

        while True:
            server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
            status, message = server_response.split('@')
            
            if status == 'AUTHENTICATE':
                print(f'{message}')
                user_name = input('> User Name: ')
                password = input('> Password: ')

                client.send(f'{user_name} {password}'.encode('utf-8'))

                server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                status, message = server_response.split('@')

                if status == 'OK':
                    print(f'{message}')
                    break
                else:
                    print(f'{message}')

        while True:
            try:
                user_input = input('> ')
                command, *args = user_input.split(' ')
                print(command, args)
                if command == "HELP":
                    client.send(user_input.encode('utf-8'))
                    server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                    status, message = server_response.split('@')
                    if status == 'OK':
                        print(f'{message}')  

                    elif status == "ERROR":
                        print(f'<ERROR> {message}')
                
                elif command == "LIST":
                    client.send(user_input.encode('utf-8'))
                    server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                    status, message = server_response.split('@')
                    if status == 'OK':
                        print(f'{message}')  

                    elif status == "ERROR":
                        print(f'<ERROR> {message}')
                elif command == "UPLOAD":
                    if args:
                        try:
                            file_path = args[0]
                            file_name = file_path.split('/')[-1]
                            file_size = os.path.getsize(file_path)

                            send_data = f'{command} {file_name} {file_size}'
                            client.send(send_data.encode('utf-8'))

                            with open(file_path, 'rb') as f:
                                data = f.read()
                                client.sendall(data)
                            
                            server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                            status, message = server_response.split('@')
                            if status == 'OK':
                                print(f'{message}')  

                            elif status == "ERROR":
                                print(f'<ERROR> {message}')
                            
                        except Exception as e:
                            client.send("INVALID_ARGS_UPLOAD".encode('utf-8'))

                    else:
                        client.send("INVALID_ARGS_UPLOAD".encode('utf-8'))

                elif command == "DOWNLOAD":
                    if args:
                        try:
                            file_name = args[0]
                            file_path = args[1]

                            send_data = f'{command} {file_name}'
                            client.send(send_data.encode('utf-8'))
                            
                            response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                            status, message = response.split('@')
                            print(f"Trying to download...")
                            print(response)
                            if file_name in os.listdir(file_path):
                                file_name = file_name.split('.')
                                file_name = file_name[0] + 'copy.' + file_name[1]
                                file_path = os.path.join(file_path, file_name)

                            else:
                                file_path = os.path.join(file_path, file_name)
                            file_size = int(message)
                            if status == "ACCEPTED":
                                client.send("START".encode('utf-8'))
                                print("Download Started")
                                with open(file_path, 'wb') as f:
                                    bytes_received = 0
                                    while bytes_received < file_size:
                                        data = client.recv(self.BUFFER_SIZE)
                                        if not data:
                                            break
                                        f.write(data)
                                        bytes_received += len(data)
                                    # while True:
                                    #     data = client.recv(self.BUFFER_SIZE)
                                    #     if b'<END>' in data:
                                    #         data = data.replace(b'<END>', b'')
                                    #         f.write(data)
                                    #         break
                                    #     f.write(data)
                            print(f'{file_name} downloaded successfully!')
                            
                        except Exception as e:
                            print(e)
                            client.send("INVALID_ARGS_DOWNLOAD".encode('utf-8'))
                    
                    else:
                        client.send("INVALID_ARGS_DOWNLOAD".encode('utf-8'))

                elif command == "DELETE" :
                    if args:
                        file_name = args[0]
                        send_data = f'{command} {file_name}'
                        client.send(send_data.encode('utf'))
                        server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                        status, message = server_response.split('@')
                        if status == 'OK':
                            print(f'{message}')  

                        elif status == "ERROR":
                            print(f'<ERROR> {message}')
                    else:
                        client.send("INVALID_ARGS_DELETE".encode('utf-8'))

                    

                elif command == "LOGOUT":
                    client.send(user_input.encode('utf-8'))
                    break

                else:
                    client.send("OTHER".encode('utf-8'))
                    server_response = client.recv(self.BUFFER_SIZE).decode('utf-8')
                    status, message = server_response.split('@')
                    if status == 'OK':
                        print(f'{message}')  

                    elif status == "ERROR":
                        print(f'<ERROR> {message}')
            except Exception as e:
                print(f'Error raised: {e}')
                break

        print(f'Disconnected from the server.')
        client.close()


if __name__ == '__main__':
    
    client = Client()
    client.connect_to_server() 