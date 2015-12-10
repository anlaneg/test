
import signal
import subprocess
import log as LOG

def _subprocess_setup():
    # Python installs a SIGPIPE handler by default. This is usually not what
    # non-Python subprocesses expect.
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)

def _create_process(cmd,shell,cwd):
    obj = subprocess.Popen(cmd, shell=shell,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            preexec_fn=_subprocess_setup,
            close_fds=True,
            stderr=subprocess.PIPE,cwd=cwd)
    return obj

def execute(cmd, process_input=None,
            return_stderr=False, 
            log_fail_as_error=True,shell=False,cwd=None):
    obj= _create_process(cmd,shell=shell,cwd=cwd)
    _stdout, _stderr = obj.communicate(process_input)
    returncode = obj.returncode
    obj.stdin.close()

    if returncode and log_fail_as_error:
        LOG.warning("execute '%s' return: %s" % (cmd,returncode))
        if return_stderr==False:
            LOG.error("execute command %s" % obj)
            LOG.error("stderr %s" % _stderr)
    return (_stdout, _stderr) if return_stderr else _stdout

def simple_execute(cmd,return_stderr=False,shell=False,cwd=None):
    return execute(cmd,return_stderr=return_stderr,shell=shell,cwd=cwd)

def script_execute(file_path,args,cwd=None):
    idx=file_path.rfind('.')
    if idx != -1:
        post_fix=file_path[idx:]
        if post_fix ==".py":
            return execute(['python',file_path],cwd=cwd)
    return execute(['bash',file_path] + args,cwd)
        
    
    

