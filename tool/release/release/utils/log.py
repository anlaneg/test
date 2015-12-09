import time
import sys

class MyLog(object):
    instance=None
    def __init__(self):
        pass
    def display(self,info,file_name,line,msg):
        print("%(date)s %(info)s %(file)s:%(line)s  %(msg)s\n" % { 
                'date':time.strftime("%Y-%m-%d %X"),
                'info':info,
                'file':file_name,
                'line':line,
                'msg':msg
                })
    def flush(self):
        pass

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
def flush():
    MyLog.get_log().flush()
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
