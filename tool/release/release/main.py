
import time
from source import source_manager
from build  import build_manager
from collect import collect_manager
def main():
    old_version=None
    source=source_manager.SourceManager(cfg)
    build=build_manager.BuildManager(cfg)
    collect=collect_manager.CollectManager(cfg)
  
    while True:
        current_version=source.version()
        if current_version != old_version:
            source.checkout(build.cwd,version=current_version)
            build.build()
            collect.package(build.cwd,env={})
        time.sleep(?)

        

