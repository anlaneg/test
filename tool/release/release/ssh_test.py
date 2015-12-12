import paramiko

def process_input(stdin,stdout,stderr):
    for l in stderr.readlines():
        print("STDERR:" + l)
    for l in stdout.readlines():
        print("STDOUT:" + l)

def simple_execute(client,cmd,process_input=process_input):
    stdin,stdout,stderr = client.exec_command(cmd)
    if process_input:
        process_input(stdin,stdout,stderr)

def remote_execute(chan,cmd,bufsize=-1,process_input=process_input):
    chan.exec_command(cmd)
    stdin = chan.makefile('wb', bufsize)
    stdout = chan.makefile('rb', bufsize)
    stderr = chan.makefile_stderr('rb', bufsize)
    if process_input:
        process_input(stdin,stdout,stderr)
    return stdin,stdout,stderr
def command_execute(stdin,stdout,stderr):
    cmd=['pwd','cd /home/along/dvr','pwd','ls -l','exit']
    for i in cmd:
        stdin.write(i + '\n')
    for l in stderr.readlines():
        print("STDERR:" + l)
    for l in stdout.readlines():
        print("STDOUT:" + l)

if __name__ == "__main__":
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.connect('192.168.150.75',username='',password='')
    simple_execute(client,'bash',process_input=command_execute)
    #stdin = chan.makefile('wb', bufsize)
    #stdout = chan.makefile('rb', bufsize)
    #stderr = chan.makefile_stderr('rb', bufsize)
    #return stdin, stdout, stderr
    #simple_execute(client,'pwd')
    #simple_execute(client,'cd /home/along/dvr')
    #simple_execute(client,'pwd')
    #simple_execute(client,'ls -l')
    client.close()


