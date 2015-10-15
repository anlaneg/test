#!/usr/bin/env python
import socket
host="172.17.42.2"
port=10000

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((host,port))
s.listen(5)
while 1:
    sock,addr=s.accept()
    print "got connection form ",sock.getpeername()
    while True:
	data=sock.recv(1024)
	if data:
		print data
		sock.sendall("hello")
	else:
		sock.close()
		break
    
