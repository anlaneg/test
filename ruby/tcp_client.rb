#用于实现一个tcp客户端
require 'socket'

hostname = 'localhost'
port = 8599

client = TCPSocket.open(hostname, port)

loop do
 client.print("in this example you have a permanent loop, and when server.accept responds, a new thread is created and started immediately to handle the connection that has just been accepted, using the connection object passed into the thread. However, the main program immediately loops back and awaits new connections.\n"); 
end
client.close               # Close the socket when done

