class PluginBase(object):
    def checkout(self):
        raise NotImplemented
    def cur_version(self):
        raise NotImplemented
