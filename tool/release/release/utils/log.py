import time
import sys
import os

class MyLog(object):
    instance=None
    def __init__(self):
        self.log_cache=False
        pass
    def enable_log_cache(self):
        self.log_cache=True
        self.log=[]
    def disable_log_cache(self):
        self.log_cache=False
        ret = self.log
        self.log=[]
        return ret
    def display(self,info,file_name,line,msg):
        message="%(date)s %(info)s %(file)s:%(line)s  %(msg)s" % { 
                'date':time.strftime("%Y-%m-%d %X"),
                'info':info,
                'file':os.path.basename(file_name),
                'line':line,
                'msg':msg
                }
        if self.log_cache:
            self.log.append(message)
        print(message)
    #def flush(self):
    #    ret=self.log
    #    self.log=[]
    #    return ret

    @staticmethod
    def get_log():
        if MyLog.instance == None:
            MyLog.instance = MyLog()
        return MyLog.instance

class Log(object):
    DEBUG=1
    LOG=2
    WARNING=3
    ERROR=4
    log_level=2
    @staticmethod
    def _log_inner(info,tag,msg):
        if Log.log_level <= info:
            invoke=sys._getframe().f_back.f_back
            MyLog.get_log().display(tag.center(7),invoke.f_code.co_filename,invoke.f_lineno,msg)

def log(msg):
    Log._log_inner(Log.LOG,"LOG",msg)
def warning(msg):
    Log._log_inner(Log.WARNING,"WARN",msg)
def debug(msg):
    Log._log_inner(Log.DEBUG,"DEBUG",msg)
def error(msg):
    Log._log_inner(Log.ERROR,"ERROR",msg)
#def flush():
#    return MyLog.get_log().flush()
def enable_log_cache():
    MyLog.get_log().enable_log_cache()
def disable_log_cache():
    return MyLog.get_log().disable_log_cache()
def set_log_level(i):
    Log.log_level = i


if __name__ == "__main__":
    def test_log():
        log("hello")
        warning("hello")
        debug("hello")
        error("hello")

    for i in [4,3,2,1]:
        set_log_level(i)
        test_log()
        print("------\n")
