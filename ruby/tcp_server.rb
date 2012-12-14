#用于实现一个ruby tcp 服务器

require 'socket'

read_len=0;
server = TCPServer.new(8599)

loop {                         # Servers run forever
  client = server.accept       # Wait for a client to connect
  while line = client.gets
  read_len += line.length
  puts "Received! #{read_len} byte , #{read_len/(1024*1024)} M byte #{read_len/(1024*1024*1024)} G byte\n";
  end
}
