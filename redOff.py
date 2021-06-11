#! /usr/bin/python3

# Import A Socket
import socket

# Make A Function That Turns Off Red Led
def turnRedOff():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipArduino = "192.168.199.123"
    port = 24

    s.connect((ipArduino, port))
    s.sendall("m".encode('utf-8'))

    print("Content-Type: text/plain")
    print("")
    print("Turning Off Red Led")


#turnRedOff()

def changeDatabaseRecords():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipServer = "localhost"
    port = 1234

    s.connect((ipServer, port))

    s.sendall(b"2")
    s.sendall(b"u")

    print("Content-Type: text/plain")
    print("")
    print("Changed Settings Database")

changeDatabaseRecords()
