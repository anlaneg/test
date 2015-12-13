
from release.event import event_base as event
from release.utils import run
from release.utils import sshutil as ssh
from release.utils import log as LOG
class CollectManager(event.EventBase):
    def __init__(self,cfg):
        super(CollectManager,self).__init__(cfg)
        self.target=self.get_or_raise(cfg,'target')
        self.output=self.get_or_raise(cfg,'output-dir')
        self.target_host=cfg.get('target-host',None)
        self.username=""
        self.password=""
        if self.target_host:
            self.username=self.get_or_raise(cfg,'username')
            self.password=self.get_or_raise(cfg,'password')
        self.script=self.get_or_raise(cfg,'collect-script')

    def package(self,cwd,env,host=None,user=None,password=None):
        cmd=['file_name="'+ self.target % env + '"']
        self.trigger('result-package-before')
        if not host or host == "127.0.0.1":
            stdout,stderr=run.execute_helper(self.script,cmd,cwd=cwd)
        else:
            client = ssh.SSHUtil(host,user,password)
            stdout,stderr=client.execute_lines([" ".join([self.script] + cmd)],cwd=cwd)
        self.trigger('result-package-after')
        if stderr:
            LOG.error(stderr)
        if stdout:
            LOG.log(stdout)
        return stdout,stderr
