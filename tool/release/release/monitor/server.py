import os
from release.event import event_base as event
import signal
import time
from release.utils import log as LOG

class Server(event.EventBase):
    @staticmethod
    def term_signal_process(signum, stack):
        LOG.log("wait process die")
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
        LOG.log("release (%d) Running" % os.getpid())
    def _do_service(self,source,build,collect):
        old_version=None
        LOG.flush()
        while self.state_start:
            current_version=source.version()
            LOG.log("current version %s,prev version %s" % (current_version,old_version))
            if current_version != old_version:
                source.checkout(build.cwd,version=current_version,host=build.host,user=build.username,password=build.password)
                build.build()
                collect.package(build.cwd,env={'version':current_version,'date':time.strftime("%Y%m%d%H%M%S")},host=build.host,user=build.username,password=build.password)
                LOG.flush()#next version mail log information
            LOG.log("sleep %s" % self.interval)
            time.sleep(self.interval)
