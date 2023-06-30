# Import Libraries
import os
import socket
import threading
import sqlite3
from datetime import datetime


class Server():
    def __init__(self) -> None:
        # Initial configuration
        self.SERVER_HOST = socket.gethostbyname(socket.gethostname())
        self.SERVER_PORT = 9090
        self.BUFFER_SIZE = 4096
        self.SERVER_FILES_DIR = '/home/afsharino/Desktop/server_files/'
        self.SERVER_SOCKET = None

    def start_server(self) -> None:
        try:
            print(f'Server is starting...')
            self.SERVER_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.SERVER_SOCKET.bind((self.SERVER_HOST, self.SERVER_PORT))
            self.SERVER_SOCKET.listen(5)
            print(f'Server listening on {self.SERVER_HOST}:{self.SERVER_PORT}')

            while True:
                client_socket, client_address = self.SERVER_SOCKET.accept()
                client_thread = threading.Thread(target=self.handle_client, args=(client_socket, client_address))
                client_thread.start()

            self.SERVER_SOCKET.close()
        
        except Exception as e:
            print(f'Error raised: {e}')
    
    def handle_client(self, client_socket, client_address):
        try:
            while True:
                if self.authenticate_user(client_socket):
                    print(f'New connection established on  {client_address[0]}:{client_address[1]}')
                    client_socket.send("OK@>> WELCOME TO THE FTP SERVER <<".encode('utf-8'))

                    while True:
                        client_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
                        command, *args = client_response.split(' ')
                        if command:
                            print(f'Client requested to {command}')

                        if command == "HELP":
                            self.get_help(client_socket)

                        elif command == "LIST":
                            self.list_files(client_socket)
                        
                        elif command == "UPLOAD":
                            self.upload_file(client_socket, args)
                        
                        elif command == "DELETE":
                            self.delete_file(client_socket, args)
                                
                        elif command == "LOGOUT":
                            break
                                
                        elif command == 'DOWNLOAD':
                            self.download_file(client_socket, args)

                        elif command == "OTHER":
                            server_response = f'OK@Command not found.\nNOTE: commands are case sensetive\n' +\
                            f'To see available commands enter "HELP" command.\n'
                            client_socket.send(server_response.encode('utf-8'))

                        elif command == "INVALID_ARGS_UPLOAD":
                            server_response = f'ERROR@Enter Valid file path.\n'
                            client_socket.send(server_response.encode('utf-8'))
                        
                        elif command == "INVALID_ARGS_DOWNLOAD":
                            server_response = f'ERROR@Invalid arguments.\n'
                            client_socket.send(server_response.encode('utf-8'))
                        
                        elif command == "INVALID_ARGS_DELETE":
                            server_response = f'ERROR@Enter file name to delete.\n'
                            client_socket.send(server_response.encode('utf-8'))

                        else:

                            break
                    
                    print(f'{client_address[0]}:{client_address[1]} Disconnected from the server.')
                    break
                
                else:
                    print(f'Authentication failed')
                    continue
        
        except Exception as e:
            print(f'Error Raised: {e}')

    def get_help(self, client_socket) -> None:
        server_response = f'OK@' +\
                f'LIST: To list all files in the server\n' +\
                f'UPLOAD <path>: To upload a file to the server\n' +\
                f'DOWNLOAD <file_name> <file_path>: To download file from the server\n' +\
                f'DELETE <file_name>: To delete a file from the server\n' +\
                f'LOGOUT: To disconncet from the server\n' +\
                f'HELP: To list all commands and their functionality\n'

        client_socket.send(server_response.encode('utf-8'))
    
    def list_files(self, client_socket) -> None:
        try:
            files = os.listdir(self.SERVER_FILES_DIR)
            server_response = f'OK@FILE_NAME\t\t\tCREATED_DATE\t\tMODIFIED_DATE\t\tFILE_SIZE\n' 
            
            if files:
                # Get name with longest length
                longest_name = Server.find_longest_name(files)

                for file_name in files:
                    file_path = os.path.join(self.SERVER_FILES_DIR, file_name)
                    file_created = datetime.fromtimestamp(os.path.getctime(file_path)).strftime('%Y-%m-%d %H:%M:%S')
                    file_modefied = datetime.fromtimestamp(os.path.getmtime(file_path)).strftime('%Y-%m-%d %H:%M:%S') 
                    file_size = os.path.getsize(file_path)
                    file_size = Server.human_readable(file_size)
                    file_name += (len(longest_name) - len(file_name)) * ' '
                    server_response += '\t'.join([file_name, file_created, file_modefied, file_size]) + '\n'

            client_socket.send(server_response.encode('utf-8'))
        
        except Exception as e:
            print(f'Error raised: {e}')
            server_response= f'ERROR@Server is not responding.\n'
            client_socket.send(server_response.encode('utf-8'))

    def upload_file(self, client_socket, args) -> None:
        try:
            file_name = args[0]
            file_size = int(args[1])

            if file_name in os.listdir(self.SERVER_FILES_DIR):
                file_name = file_name.split('.')
                file_name = file_name[0] + '-copy.' + file_name[1]
                file_path = os.path.join(self.SERVER_FILES_DIR, file_name)

            else:
                file_path = os.path.join(self.SERVER_FILES_DIR, file_name)

            with open(file_path,'wb' ) as f:
                bytes_received = 0

                while bytes_received < file_size:
                    data = client_socket.recv(self.BUFFER_SIZE)

                    if not data:
                        break
                    f.write(data)
                    bytes_received += len(data)

            server_response = f'OK@{file_name} uploaded to the server successfully!\n'
            print(f'{file_name} uploaded to the server')
            client_socket.send(server_response.encode('utf-8'))
    
        except Exception as e:
            print(f'Error raised: {e}\n')
            server_response= f'ERROR@Server is not responding.\n'
            client_socket.send(server_response.encode('utf-8'))
    
    def download_file(self, client_socket, args) -> None:
        try:
            file_name = args[0]
            file_path = os.path.join(self.SERVER_FILES_DIR, file_name)

            if file_name in os.listdir(self.SERVER_FILES_DIR):
                with open(file_path, 'rb') as f:
                    file_data = f.read()

                file_size = len(file_data)

                send_data = f'ACCEPTED@{file_size}'
                client_socket.send(send_data.encode('utf-8'))
                print(f"Download acccepted")

                response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
    
                client_socket.sendall(file_data)
                print(f"Download finished")

            else:
                server_response = "ERROR@File {file_name} not found\n"
                client_socket.send(server_response.encode('utf-8'))
            
        
        except Exception as e:
            print(f'Error raised: {e}\n')
            server_response= f'ERROR@Server is not responding.\n'
            client_socket.send(server_response.encode('utf-8'))
    
    def delete_file(self, client_socket, args) -> None:
        try:
            files = os.listdir(self.SERVER_FILES_DIR)
            server_response = f'OK@' 

            if files:
                if args[0] in files:
                    os.system(f'rm {self.SERVER_FILES_DIR}/{args[0]}')
                    server_response += f'{args[0]} deleted from server successfully\n'
                    print(f'{args[0]} deleted from server')

                else:
                    server_response += f'{args[0]} not found\n'

            else:
                server_response += "There is no file available on the server.\n"

            client_socket.send(server_response.encode('utf-8'))
        
        except Exception as e:
            print(f'Error raised: {e}')
            server_response= f'ERROR@Server is not responding.\n'
            client_socket.send(server_response.encode('utf-8'))

    def authenticate_user(self, client_socket):
        try:
            client_socket.send('AUTHENTICATE@Login to the server.\n'.encode('utf-8'))
            client_response = client_socket.recv(self.BUFFER_SIZE).decode('utf-8')
            args = client_response.split(' ')

            username, password = args[0], args[1]

            db_connection = sqlite3.connect('database.db')
            cursor = db_connection.cursor()

            # Query the database for the provided username and password
            cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
            user = cursor.fetchone()

            # Close the database connection
            db_connection.close()


            # Check if a user with the provided credentials exists
            if user is not None:
                return True
            else:
                client_socket.send('ERROR@Invalid credential.\n'.encode('utf-8'))
                return False

        except Exception as e:
            print(f"Error Raised: {e}")

    def add_user_to_database(self, username, password):
        # Insert the new user into the database
        try:
            db_connection = sqlite3.connect('database.db')
            cursor = db_connection.cursor()
            cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, password))
            db_connection.commit()

            db_connection.close()

            return True

        except Exception as e:
            print(f"Error Raised: {e}")
            return False   

    def delete_user_from_database(self, username):
        # Insert the new user into the database
        try:
            db_connection = sqlite3.connect('database.db')
            cursor = db_connection.cursor()
            cursor.execute('DELETE FROM users WHERE username=?', (username,))
            db_connection.commit()

            db_connection.close()

            return True

        except Exception as e:
            print(f"Error Raised: {e}")
            return False          

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
    print("Welcome Admin")
  
    while True:
        print("Enter Choise:\n")
        print(f'1) ADD USER\n2) DELETE USER \n3) RUN SERVER')
        user_choice = input('> ')
        if user_choice == '1':
            username = input('> username: ')
            password = input('> password: ')
            server.add_user_to_database(username, password)
            print(f"{username} added to database successfully\n")

        elif user_choice == '2':
            username = input('> username to delete: ')
            server.delete_user_from_database(username)
            print(f"{username} deleted from database successfully\n")

        elif user_choice == '3':
            server.start_server()
            break

        else:
            print("Invalid Input!!!")