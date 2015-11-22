import sys

"""
support load_class function for dynamic load class
"""
class ImportException(Exception):
    def __init__(self,str,**args):
        if not str:
            msg = "load fail" 
        else:
            msg = str % args
        super(ImportException,self).__init__(msg)

def _load_module(mod):
    __import__(mod)
    return sys.modules[mod]

def _load_class(mod,cls,**args):
    mod=_load_module(mod)
    construct=getattr(mod,cls)
    return construct(**args)

def _split_mod_cls(cls):
    idx=cls.rfind('.')
    if idx == -1:
       raise ImportException("Not module name in string '%(cls)s'" ,cls=cls)
    return cls[0:idx],cls[idx+1:]

def load_class(cls,**args):
    """
       load one module,and get instance of module' class
       @param cls       module.class
       @param **args    class construct parameter
    """
    mod,cls=_split_mod_cls(cls)
    return _load_class(mod,cls,**args)

"""
class A(object):
        def __init__(self,a):
            self.a = a
            print("hello %s" % a)
        def fun(self):
            print("my member is %s" % self.a)

if __name__ == "__main__":
    
    a=load_class("importutils.A",a="world")
    a.fun()
    b=load_class("importutils.test",value="3")
    print(b)
"""
