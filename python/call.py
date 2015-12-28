
class base(object):
    singel=None
    def __new__(cls,*args,**kwargs):
        print(cls,args,kwargs)
        print("do __new__")
        if base.singel==None:
            #base.singel=super(base,cls).__new__(cls,*args,**kwargs)
            base.singel=super(base,cls).__new__(cls)
        return base.singel
    def __init__(self,help):
        print("do base __init__ %s" % help)
    def __call__(self,value):
        print("do base __call__")

class CallTest(object):
    def __init__(self,help):
        print("do CallTest __init__")
        #super(CallTest,self).__init__(help)
        self.base = base(help)
    def __call__(self,value):
        print("do CallTest __call__")
        #super(CallTest,self).__call__(value)
        return base


a = CallTest("hello")
print(id(a))
c=a("hello")
c('abc')
#b = CallTest("help")
#print(id(b))
#b("help")
