from release.utils import run
from release.event import event_base as event
from release.utils import sshutil as ssh
from release.utils import log as LOG

class BuildManager(event.EventBase):
    def __init__(self,cfg):
        super(BuildManager,self).__init__(cfg)
        self.cwd=self.get_or_raise(cfg,'workspace-dir')
        self.host=cfg.get('host',None)
        if not self.host or self.host == 'localhost':
            self.host = '127.0.0.1'
        self.username=""
        self.password=""
        if self.host != '127.0.0.1':
            self.username=self.get_or_raise(cfg,'username')
            self.password=self.get_or_raise(cfg,'password')
        self.script=self.get_or_raise(cfg,'build-script')

    def build(self):
        self.trigger('source-build-before')
        #ret=run.script_execute(self.script,[],self.cwd)
        if not self.host or self.host == "127.0.0.1":
            stdout,stderr=run.execute_helper(self.script,[],self.cwd)
        else:
            client = ssh.SSHUtil(self.host,self.username,self.password)
            stdout,stderr=client.execute_lines([self.script],cwd=self.cwd)
        self.trigger('source-build-after')
        if stderr:
            LOG.error(stderr)
        if stdout:
            LOG.log(stdout)
        return stdout,stderr 
