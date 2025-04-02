import os
import sqlite3
from datetime import datetime

script_dir = os.path.dirname(os.path.abspath(__file__))
db_path = "Hotels.db"
db_path = os.path.join(script_dir, db_path).replace("misc","database")

conn = sqlite3.connect(db_path)
cursor = conn.cursor()

cursor.execute('''
CREATE TABLE IF NOT EXISTS Room (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    hotel_name TEXT,
    number INTEGER,
    location TEXT,
    price REAL,
    availability INTEGER,
    position TEXT,
    facilities TEXT
);
''')

cursor.execute('''
CREATE TABLE IF NOT EXISTS Client (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    email TEXT,
    phone_number TEXT
);
''')

cursor.execute('''
CREATE TABLE IF NOT EXISTS User (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT,
    email TEXT,
    password TEXT,
    role INTEGER
);
''')

cursor.execute('''
INSERT INTO Room (hotel_name, number, location, price, availability, position, facilities)
VALUES
('Hotel A', 101, 'Paris', 120.5, 1, '1st floor', 'TV, AC, WiFi'),
('Hotel B', 102, 'New York', 200.0, 0, '2nd floor', 'TV, WiFi'),
('Hotel A', 103, 'Paris', 150.0, 1, '1st floor', 'AC, WiFi'),
('Hotel C', 104, 'Tokyo', 180.75, 1, '3rd floor', 'WiFi');
''')

cursor.execute('''
INSERT INTO Client (name, email, phone_number)
VALUES
('John Doe', 'john@example.com', '+1234567890'),
('Jane Smith', 'jane@example.com', '+0987654321'),
('Emily White', 'emily@example.com', '+1122334455');
''')

cursor.execute('''
INSERT INTO User (username, email, password, role)
VALUES
('admin', 'admin@example.com', 'password123', 1),
('user1', 'user1@example.com', 'password1', 2),
('user2', 'user2@example.com', 'password2', 2);
''')

conn.commit()

print("Database populated successfully.")

conente_path = "DatabaseContent.txt"
conente_path = os.path.join(script_dir, conente_path)
with open(conente_path, "w") as file:
    print("File Opened")
    file.write("Users (Employees and Administrators):\n")
    file.write("username, email, password, role\n")
    cursor.execute("SELECT * FROM User")
    for row in cursor.fetchall():
        file.write(f"{row}\n")

    file.write("\nClients (No Password):\n")
    file.write("name, email, phone_number\n")
    cursor.execute("SELECT * FROM Client")
    for row in cursor.fetchall():
        file.write(f"{row}\n")
 
    file.write("\nRooms:\n")
    file.write("hotel_name, number, location, price, availability, position, facilities\n")
    cursor.execute("SELECT * FROM Room")
    for row in cursor.fetchall():
        file.write(f"{row}\n")

conn.close()

print("\nDatabase setup complete and data inserted!")
