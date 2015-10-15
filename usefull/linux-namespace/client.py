#!/usr/bin/env python
import socket
import time

host="172.17.42.2"
port=10000
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((host,port))
while True:
	s.send("hello from client")
	time.sleep(1)	
        data=s.recv(1024)
        if data:
                print data
s.close()
