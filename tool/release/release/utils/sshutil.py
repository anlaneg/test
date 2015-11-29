import os
import paramiko

def _default_response_process_fun(stdin,stdout,stderr):
    lines=stderr.readlines()
    if len(lines):
        raise Exception(lines)
    else:
        for l in stdout.readlines():
            print(l)

class SSHUtil(object):
    def __init__(self,host,username,password,port=22):
        self.name=username
        self.password=password
        #maybe ,we need dns
        self.host=host
        self.port=port
    def open(self):
        try:
            ssh_client=paramiko.SSHClient()
            ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            ssh_client.connect(hostname=self.host,port=self.port,username=self.name,password=self.password)
            return ssh_client
        except Exception as e:
            print(e)
            raise

    def close(self,ssh_client):
        if ssh_client:
            ssh_client.close()

    def execute(self,cmd,response_fun=_default_response_process_fun,ssh_client=None):
        is_need_close=False
        try:
            if not ssh_client:
                ssh_client=paramiko.SSHClient()
                ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
                ssh_client.connect(hostname=self.host,port=self.port,username=self.name,password=self.password)
                is_need_close=True

            stdin,stdout,stderr=ssh_client.exec_command(cmd)
            if response_fun:
                response_fun(stdin,stdout,stderr)

            #if open ssh client myself,close it
            if is_need_close:
                ssh_client.close()

        except Exception as e:
            print(e)
            raise

    def _updown_file(self,src,dst,is_up):
        try:
            transport = paramiko.Transport(self.host,self.port)
            transport.connect(username=self.name,password=self.password)
            sftp=paramiko.SFTPClient.from_transport(transport)
            if is_up:
                sftp.put(src,dst)
            else:
                sftp.get(src,dst)
            transport.close()
        except Exception as e:
            print(e)
            raise

    def upload_file(self,local_file,remote_file):
        self._updown_file(local_file,remote_file,True)
    def download_file(self,remote_file,local_file):
        self._updown_file(remote_file,local_file,False)


if __name__ == "__main__":
    def display(stdin,stdout,stderr):
        lines=stderr.readlines()
        if len(lines):
            print("fail:")
            for l in lines:
                print(l)
        else:
            for l in stdout.readlines():
                print(l)

    username=""
    password=""
    ssh=SSHUtil('127.0.0.1',username,password)
    ssh.execute("pwd",display)
