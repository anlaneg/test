import time
from source import source_manager
from build  import build_manager
from collect import collect_manager
from cfg import cfg as config
from monitor import server
from utils import log as LOG
def main():
    old_version=None
    cfg_manager=config.get_cfg_manager()
    LOG.log("try to read config file :./release.conf")
    cfg=cfg_manager.parse_config_file('./release.conf')
    LOG.log("config:%s" % cfg)
    source=source_manager.SourceManager(cfg['source'])
    build=build_manager.BuildManager(cfg['build'])
    collect=collect_manager.CollectManager(cfg['collect'])
    monitor=server.Server(cfg['monitor'])
    monitor.status()
    monitor.start(source,build,collect)

def write_config_template():
    cfg_manager=config.get_cfg_manager()
    cfg_file_content=cfg_manager.gen_config_template()
    f = open("./release.conf.template","w")
    f.writelines(cfg_file_content)
    f.close()

if __name__ == "__main__":
    #write_config_template()
    main()
