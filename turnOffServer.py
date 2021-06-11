#! /usr/bin/python3

import socket

# Make A Function That Sends A Specific Value To Turn Off Server
def turnOffServer():
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    ipServer = "localhost"
    port = 1234

    s.connect((ipServer, port))
    s.sendall(b"8")

    print("Content-Type: text/plain")
    print("")
    print("Server wordt gestopt")

turnOffServer()
