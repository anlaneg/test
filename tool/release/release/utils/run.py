
import signal
import subprocess

def _subprocess_setup():
    # Python installs a SIGPIPE handler by default. This is usually not what
    # non-Python subprocesses expect.
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)

def _create_process(cmd,shell):
    obj = subprocess.Popen(cmd, shell=shell,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            preexec_fn=_subprocess_setup,
            close_fds=True,
            stderr=subprocess.PIPE)
    return obj

def execute(cmd, process_input=None,
            return_stderr=False, 
            log_fail_as_error=True,shell=False):
    obj= _create_process(cmd,shell=shell)
    _stdout, _stderr = obj.communicate(process_input)
    returncode = obj.returncode
    obj.stdin.close()

    if returncode and log_fail_as_error:
        print("Waring execut '%s' return: %s" % (cmd,returncode))
        if return_stderr==False:
            print("execute command %s" % obj)
            print("stderr %s" % _stderr)
    return (_stdout, _stderr) if return_stderr else _stdout

def simple_execute(cmd,return_stderr=False,shell=False):
    return execute(cmd,return_stderr=return_stderr,shell=shell)
