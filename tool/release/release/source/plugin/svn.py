import os
import re
from release.source import plugin_base as base
from release.utils  import run
class Svn(base.PluginBase):
    def update(self,cfg,cwd,version):
        cmd=['svn' , 'update',cwd,
             '-r %s ' % version if version else ' ',
             '--username',cfg.username,
             '--password',cfg.password,
             '--non-interactive','--no-auth-cache' ]
        #os.system('svn cleanup')
        stdout=run.simple_execute(cmd)
        return stdout
    def checkout(self,cfg,cwd,version):
        cmd=['svn' , 'checkout',
            cfg.url if not version else "%s@%s" % (cfg.url,version),             cwd,
             '--username',cfg.username,
             '--password',cfg.password,
             '--non-interactive','--no-auth-cache' ]
        stdout=run.simple_execute(cmd)
        return stdout
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
