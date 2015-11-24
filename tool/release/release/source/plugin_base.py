class PluginBase(object):
    def checkout(self,cfg,cwd,version):
        raise NotImplementedError()
    def version(self,cfg):
        raise NotImplementedError()
    def update(self,cfg,cwd,version):
        raise NotImplementedError()
