#coding:utf-8

import time
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import log as LOG

class SMTP_SSL(smtplib.SMTP):
     def __init__(self, host='',port=465 , local_hostname=None, key=None, cert=None):
         self.cert = cert
         self.key = key
         smtplib.SMTP.__init__(self, host, port, local_hostname)

     def connect(self, host, port=465):
         self.sock = None
         for res in socket.getaddrinfo(host, port, 0, socket.SOCK_STREAM):
             af, socktype, proto, canonname, sa = res
             try :
                 self.sock = socket.socket(af, socktype, proto)
                 if self.debuglevel > 0:
                    LOG.log(' connect: host:%s port:%s' % (host, port))

                 self.sock.connect(sa)

                 sslobj = socket.ssl(self.sock, self.key, self.cert)
             except socket.error, msg:
                 if self.debuglevel > 0:
                    LOG.error(' connect fail: host:%s port:%s' % (host, port))

                 if self.sock:
                    self.sock.close()

                 self.sock = None
                 continue
             break

         if not self.sock:
             raise socket.error, msg

         self.sock = smtplib.SSLFakeSocket(self.sock,sslobj)
         self.file = smtplib.SSLFakeFile(sslobj);

         (code, msg) = self.getreply()
         if self.debuglevel > 0:
            LOG.log(" connect: %s" % msg)
         return (code, msg)

class EmailNotify(object):
    def __init__(self,me=None,to=None,title=None,body=None):
        self.set_me(me)
        self.set_to(to)
        self.set_title(title)
        self.set_body(body)
        self.attach = []

    def set_to(self,email_addr):
        self.to=email_addr

    def set_me(self,email_addr):
        self.me=email_addr

    def set_title(self,title):
        self.title=title

    def set_body(self,email_body):
        self.body=email_body

    def attach_file(self,file_path,display_name):
        assert(file_path)
        assert(display_name)
        self.attach.append({'path':file_path,'name':display_name})

    def _build_mail(self):
        if not self.attach:
            msg = MIMEText(self.body,_subtype="plain", _charset='utf-8')
        else:
            msg = MIMEMultipart()
            body = MIMEText(self.body,_subtype="plain", _charset='utf-8')
            msg.attach(body)
            for f in self.attach:
                att = MIMEText(open(f['path'], 'rb').read(), 'base64', 'utf-8')
                att["Content-Type"] = 'application/octet-stream'
                att["Content-Disposition"] = 'attachment; filename="%s"' % f['name']
                msg.attach(att)
        msg['Subject'] = self.title
        msg['From']=self.me
        msg['To']=self.to
        return msg

    def send(self,stmp_host,stmp_port,username,password):
        if not self.title or not self.me or not self.to or not self.body:
            raise Exception("mail <title>,<me>,<to>,<body> must be set")
        try:
            server = smtplib.SMTP_SSL()
            #server.set_debuglevel(1)
            server.connect(stmp_host,stmp_port)
            server.login(username,password)
            server.sendmail(self.me,self.to,self._build_mail().as_string())
            server.close()
        except Exception as e:
            LOG.error(str(e))
            raise e

if __name__ == "__main__":
    mail_from="abc@126.com"
    mail_to="abc@126.com"
    mail_password="abc"
    
    hello_email = EmailNotify(mail_from,mail_to,"hello-test")
    hello_email.set_body("""
        hello along:
            this is a test mail from python client
            中文测试
                            %s
                          thank you!
    """ % time.asctime())
    hello_email.attach_file('/home/samsung/Desktop/mxf004.jpg','test-pict.jpg')
    hello_email.send("smtp.126.com",465,mail_from,mail_password)
