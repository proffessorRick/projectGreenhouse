#! /usr/bin/python3

# Import A Socket
import socket

# Make A Function That Turns Off Green Led
def turnGreenOff():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipArduino = "192.168.199.123"
    port = 24

    s.connect((ipArduino, port))
    s.sendall("x".encode('utf-8'))

    print("Content-Type: text/plain")
    print("")
    print("Turning Off Green Led")

def changeDatabaseRecords():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipServer = "localhost"
    port = 1234

    s.connect((ipServer, port))

    s.sendall(b"1")
    s.sendall(b"u")

    print("Content-Type: text/plain")
    print("")
    print("Changed Settings Database")

#turnGreenOff()
changeDatabaseRecords()

