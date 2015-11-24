

class EventBase(object):
    EVENT_LIST=['release-server-setup',
        'release-begin',
        'source-checkout-before',
        'source-checkout-after',
        'source-build-before',
        'source-build-after',
        'result-collect-before',
        'result-collect-after',
        'result-package-before',
        'result-package-after',
        'release-finish',
        'release-server-stop']
    def __init__(self,cfg):
        config={}
        for event in self.EVENT_LIST:
            if event in cfg:
                config.update({event:cfg[event]})
        self.event=config

    def trigger(self,event):
        if event not in self.EVENT_LIST:
            raise Exception("no find event '%s'" % event)
        cfg=self.event.get(event,None)
        if cfg:
            print("******trigger %s******" % cfg)

if __name__ == "__main__":
    event = EventBase({'release-begin':'/usr/bin/ls'})
    event.trigger('release-begin')
    event.trigger('source')
