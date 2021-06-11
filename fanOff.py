#! /usr/bin/python3

# Import A Socket
import socket

# Make A Function That Turns Off Fan
def turnFanOff():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipArduino = "192.168.199.123"
    port = 24

    s.connect((ipArduino, port))
    s.sendall("j".encode('utf-8'))

    print("Content-Type: text/plain")
    print("")
    print("Turning Fan Off")

turnFanOff()
