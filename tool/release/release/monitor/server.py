import os
from release.event import event_base as event
import signal
import time
class Server(event.EventBase):
    @staticmethod
    def term_signal_process(signum, stack):
        print("wait process die")
        self.state_start=False

    def __init__(self,cfg):
        self.state_start=False
        signal.signal(signal.SIGTERM,Server.term_signal_process) 
        super(Server,self).__init__(cfg)
        self.interval=self.get_or_raise(cfg,'interval')
        self.log=self.get_or_raise(cfg,'log')
        self.result_mails=self.get_or_raise(cfg,'result-mail-to')
        self.smtp_host=self.get_or_raise(cfg,'smtp-addr')
        self.smtp_port=self.get_or_raise(cfg,'smtp-port')
        self.sender=self.get_or_raise(cfg,'sender-mail-name')
        self.sender_password=self.get_or_raise(cfg,'sender-mail-password')
        self.relase_fail=self.get_or_raise(cfg,'release-fail')
    def stop(self):
        signal.kill(0,signal.SIGTERM)
    def start(self,source,build,collect):
        self.state_start=True
        self._do_service(source,build,collect)
    def restart(self):
        self.stop()
        self.start()
    def status(self):
        print("rlease (%d) Running" % os.getpid())
    def _do_service(self,source,build,collect):
        old_version=None
        while self.state_start:
            current_version=source.version()
            print("version=",current_version,"front_version=",old_version)
            if current_version != old_version:
                source.checkout(build.cwd,version=current_version)
                build.build()
                collect.package(build.cwd,env={})
            print("sleep %s" % self.interval)
            time.sleep(self.interval)
