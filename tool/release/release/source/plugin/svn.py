import os
import re
from release.source import plugin_base as base
from release.utils  import run
from release.utils  import sshutil as ssh
from release.utils  import log as LOG
class Svn(base.PluginBase):
    def update(self,cfg,cwd,version):
        cmd=['svn' , 'update',
             '-r %s ' % version if version else ' ',
             '--username',cfg.username,
             '--password',cfg.password,
             '--non-interactive','--no-auth-cache' ]
        #os.system('svn cleanup')
        stdout=run.simple_execute(cmd,cwd=cwd)
        return stdout
    def checkout(self,cfg,cwd,version,host,user,password):
        cmd=['svn' , 'checkout',
            cfg.url if not version else "%s@%s" % (cfg.url,version),cwd,
             '--username',cfg.username,
             '--password',cfg.password,
             '--non-interactive','--no-auth-cache' ]
        if not host or host == "127.0.0.1":
            stdout,stderr=run.simple_execute(cmd,return_stderr=True)
        else:
            client=ssh.SSHUtil(host,user,password)
            stdout,stderr=client.execute_lines(["echo 'rm -rf %s'" % cwd," ".join(cmd)],cwd=None)
            if stderr:
                LOG.error(stderr)
            if stdout:
                LOG.log(stdout)
        return stdout,stderr
    def version(self,cfg):
        cmd=['svn','log',
            cfg.url,
            '-l','1',
            '--username',cfg.username,
            '--password',cfg.password,
            '--non-interactive','--no-auth-cache' ]
        regex=re.compile('^r[0-9]+')
        stdout=run.simple_execute(cmd)
        for line in stdout.split('\n'):
            ver_match=regex.match(line)
            if ver_match:
                return ver_match.group()[1:]
        raise Exception("We can't find current version")
