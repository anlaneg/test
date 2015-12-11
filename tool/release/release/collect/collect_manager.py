
from release.event import event_base as event
from release.utils import run
class CollectManager(event.EventBase):
    def __init__(self,cfg):
        super(CollectManager,self).__init__(cfg)
        self.target=self.get_or_raise(cfg,'target')
        self.output=self.get_or_raise(cfg,'output-dir')
        #self.target_host=self.get_or_raise(cfg,'target-host')
        #self.username=self.get_or_raise(cfg,'username')
        #self.password=self.get_or_raise(cfg,'password')
        self.script=self.get_or_raise(cfg,'collect-script')
    def package(self,cwd,env):
        cmd=['file_name="'+ self.target % env + '"']
        self.trigger('result-package-before')
        ret=run.execute_helper(self.script,cmd,cwd=cwd)
        self.trigger('result-package-after')
        return ret
