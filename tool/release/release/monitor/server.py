import os
from release.event import event_base as event
import signal
import time
from release.utils import log as LOG
from release.utils import email_notify as email

class Server(event.EventBase):
    mail_info="""
hello all:
    here log from release 0.9 :
==============================
%s
==============================
    """
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
        while self.state_start:
            current_version=source.version()
            if current_version != old_version:
                #LOG.flush()
                LOG.enable_log_cache()
                LOG.log("current version %s,prev version %s" % (current_version,old_version))
                source.checkout(build.cwd,version=current_version,host=build.host,user=build.username,password=build.password)
                build.build()
                collect.package(build.cwd,env={'version':current_version,'date':time.strftime("%Y%m%d%H%M%S")},host=build.host,user=build.username,password=build.password)
                log_array=LOG.disable_log_cache()
                if self.smtp_host and self.sender:
                    result_email=email.EmailNotify(self.sender,self.result_mails,"release result notify %s" % time.strftime("%Y-%m-%d %X"))
                    result_email.set_body(Server.mail_info % "\n".join(log_array))
                    result_email.send(self.smtp_host,self.smtp_port,self.sender,self.sender_password)
                old_version = current_version
            LOG.log("sleep %s" % self.interval)
            time.sleep(self.interval)
