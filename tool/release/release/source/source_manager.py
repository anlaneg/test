
import sys
import os
from release.utils import importutils as imp
from release.event import event_base as event

class SourceManager(event.EventBase):
    @staticmethod
    def load_extends(path="plugin"):
        plugin={}
        for dirpath,dirnames,filenames in os.walk(path):
            for f in filenames:
                idx = f.rfind('.')
                if idx == -1:
                    continue

                postfix=f[idx+1:]
                filename=f[0:idx]
                #print("%s.%s" % (filename,postfix))
                if filename == "__init__" or postfix != "py":
                    continue
                imp_str="%s.%s.%s" % (dirpath.replace('/','.'),filename,filename.capitalize())
                #print(imp_str)
                obj=imp.load_class(imp_str)
                plugin[filename] = obj
        return plugin

    def __init__(self,cfg):
        super(SourceManager,self).__init__(cfg)
        self.plugin=self.load_extends()
        self.url=cfg['url']
        self.username=cfg['username']
        self.password=cfg['password']
        self.type=cfg['type']
    def checkout(self,cwd,version=None):
        return self.plugin[self.type].checkout(self,cwd,version)
    def version(self):
        return self.plugin[self.type].version(self)
    def update(self,cwd,version=None):
        return self.plugin[self.type].update(self,cwd,version)


if __name__ == "__main__":
   
    a = SourceManager({'url':'svn://192.168.150.75','username':'along','password':'along','type':'svn'})
    print(a.version())
    print(a.checkout('/home/along/test1/diff'))
    print(a.update('/home/along/test1/diff'))

    
