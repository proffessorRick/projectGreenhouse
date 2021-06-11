#!/usr/bin/python3

# Import A Socket
import socket

# Make Function To Turn On Fan
def turnOnFan():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipArduino = "192.168.199.123"
    port = 24

    s.connect((ipArduino, port))
    s.sendall("k".encode('utf-8'))

    print("Content-Type: text/plain")
    print("")
    print("De Fan Staat Aan")

turnOnFan()
