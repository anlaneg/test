
class BuildManager(event.EventBase):
    def __init__(self,cfg):
        super(BuildManager,self).__init__(cfg)
        #self.host=self.get_or_raise(cfg,'host')
        self.cwd=self.get_or_raise(cfg,'workspace-dir')
        #self.username=self.get_or_raise(cfg,'username')
        #self.password=self.get_or_raise(cfg,'password')
        self.script=self.get_or_raise(cfg,'build-script')

    def build(self):
        self.trigger('source-build-before')
        ret=run.script_execute(self.script,[],self.cwd)
        self.trigger('source-build-after')
        return ret