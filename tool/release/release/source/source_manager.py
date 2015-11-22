
import sys
import os
from release.utils import importutils as imp

class SourceManager(object):
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
                imp_str="%s.%s.%s" % (dirpath,filename,filename.capitalize())
                #print(imp_str)
                obj=imp.load_class(imp_str)
                plugin[filename] = obj
        return plugin

    def __init__(self,cfg):
        self.plugin=self.load_extends()
        self.url=cfg['url']
        self.username=cfg['username']
        self.password=cfg['password']
        self.event=event.EventBase.get_instance()
    def checkout(self,cwd):
        
        pass
    def cur_version(self):
        pass


if __name__ == "__main__":
   
    a = SourceManager({})
    a.load_extends()
