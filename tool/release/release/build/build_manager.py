from release.utils import run
from release.event import event_base as event
class BuildManager(event.EventBase):
    def __init__(self,cfg):
        super(BuildManager,self).__init__(cfg)
        self.cwd=self.get_or_raise(cfg,'workspace-dir')
        self.host=self.get_or_raise(cfg,'host')
        self.username=""
        self.password=""
        if self.host != '127.0.0.1' and self.host != 'localhost':
            self.username=self.get_or_raise(cfg,'username')
            self.password=self.get_or_raise(cfg,'password')
        self.script=self.get_or_raise(cfg,'build-script')

    def build(self):
        self.trigger('source-build-before')
        #ret=run.script_execute(self.script,[],self.cwd)
        ret=run.execute_helper(self.script,[],self.cwd)
        self.trigger('source-build-after')
        return ret
