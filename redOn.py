#! /usr/bin/python3

# Import A Socket
import socket

# Make A Function That Turns The Red Light On
def redOn():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipArduino = "192.168.199.123"
    port = 24

    s.connect((ipArduino, port))
    s.sendall("n".encode('utf-8'))

    print("Content-Type: text/plain")
    print("")
    print("Turning Red Led On")

def changeDatabaseRecord():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipServer = "localhost"
    port = 1234

    s.connect((ipServer, port))

    s.sendall(b"2")
    s.sendall(b"a")

    print("Content-Type: text/plain")
    print("")
    print("Changed Settings Database")

#redOn()
changeDatabaseRecord()
