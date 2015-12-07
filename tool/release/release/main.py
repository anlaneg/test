import time
from source import source_manager
from build  import build_manager
from collect import collect_manager
from cfg import cfg as config
def main():
    old_version=None
    cfg_manager=config.get_cfg_manager()
    cfg=cfg_manager.parse_config_file('./release.conf')
    print(cfg)
    source=source_manager.SourceManager(cfg['source'])
    build=build_manager.BuildManager(cfg['build'])
    collect=collect_manager.CollectManager(cfg['collect'])
  
    while True:
        current_version=source.version()
        print("version=",current_version)
        if current_version != old_version:
            source.checkout(build.cwd,version=current_version)
            build.build()
            collect.package(build.cwd,env={})
        time.sleep(10)

def write_config_template():
    cfg_manager=config.get_cfg_manager()
    cfg_file_content=cfg_manager.gen_config_template()
    f = open("./release.conf.template","w")
    f.writelines(cfg_file_content)
    f.close()

if __name__ == "__main__":
    #write_config_template()
    main()
