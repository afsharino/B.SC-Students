import sqlite3

def create_database():
    # Create a connection to the database (or create a new one if it doesn't exist)
    conn = sqlite3.connect('database.db')

    # Create a cursor object to execute SQL queries
    cursor = conn.cursor()

    # Create a table to store user information
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE,
            password TEXT
        )
    ''')

    # Commit the changes and close the connection
    conn.commit()
    conn.close()


if __name__ == '__main__':
    create_database()