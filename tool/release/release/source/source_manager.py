
import sys
import os
from release.utils import importutils as imp
from release.event import event_base as event
import release.source.plugin
from release.utils import log as LOG

class SourceManager(event.EventBase):
    @staticmethod
    def load_extends():
        path = release.source.plugin.__path__[0]
        plugin={}
        for f in sorted(os.listdir(path)):
            mod_name, file_ext = os.path.splitext(os.path.split(f)[-1])
            if mod_name == "__init__" or file_ext != ".py":
                continue
            imp_str="release.source.plugin.%s.%s" % (mod_name,mod_name.capitalize())
            obj=imp.load_class(imp_str)
            plugin[mod_name] = obj
        return plugin

    def __init__(self,cfg):
        super(SourceManager,self).__init__(cfg)
        self.plugin=self.load_extends()
        self.url=self.get_or_raise(cfg,'url')
        self.username=self.get_or_raise(cfg,'username')
        self.password=self.get_or_raise(cfg,'password')
        self.type=self.get_or_raise(cfg,'type')

    def checkout(self,cwd,version=None,host='127.0.0.1',user=None,password=None):
        self.trigger('source-checkout-before')
        ret=self.plugin[self.type].checkout(self,cwd,version,host,user,password)
        self.trigger('source-checkout-after')
        return ret
    def version(self):
        return self.plugin[self.type].version(self)
    def update(self,cwd,version=None):
        return self.plugin[self.type].update(self,cwd,version)


if __name__ == "__main__":
   
    a = SourceManager({'url':'svn://192.168.150.75','username':'along','password':'along','type':'svn'})
    LOG.log(a.version())
    LOG.log(a.checkout('/home/along/test1/diff'))
    LOG.log(a.update('/home/along/test1/diff'))

    
