import os
from release.event import event_base as event
class Server(event.EventBase):
    def __init__(self,cfg):
        super(BuildManager,self).__init__(cfg)
        self.interval=self.get_or_raise(cfg,'interval')
        self.log=self.get_or_raise(cfg,'log')
        self.result_mails=self.get_or_raise(cfg,'result-mail-to')
        self.smtp_host=self.get_or_raise(cfg,'smtp-addr')
        self.smtp_port=self.get_or_raise(cfg,'smtp-port')
        self.sender=self.get_or_raise(cfg,'sender-mail-name')
        self.sender_password=self.get_or_raise(cfg,'sender-mail-password')
        self.relase_fail=self.get_or_raise(cfg,'release-fail')
    def stop(self):
        pass
    def start(self):
        pass
    def restart(self):
        self.stop()
        self.start()
    def status(self):
        print("rlease (%d) Running" % os.getpid())
    def _service(self):
        pass    
    
