
class EmailNotify(object):
    def __init__(self,from=None,to=None,title=None,body=None):
        self.set_from(form)
        self.set_to(to)
        self.set_title(title)
        self.set_body(body)
    def set_to(self,email_addr):
        self.to=email_addr
    def set_from(self,email_addr):
        self.from=email_addr
    def set_titile(self,title):
        self.title=title
    def set_body(self,email_body):
        self.body=body
    def send(self,stmp_host,username,password):
        pass
