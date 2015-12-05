#coding:utf-8
class ConfigTypeBase(object):
    def __init__(self,config_param):
        self.param=config_param

    def string_to_value(self,string):
        raise NotImplementedError()
    def value_to_string(self,value):
        raise NotImplementedError()
    
class ConfigStringType(ConfigTypeBase):
    def string_to_value(self,string):
        return string
    def value_to_string(self,value):
        return value

class ConfigStringListType(ConfigTypeBase):
    pass

class ConfigEnumType(ConfigTypeBase):
    def string_to_value(self,string):
        for i in self.param:
            if string == i:
                return string
        raise Exception("Unkown enum value '%s'" % string)
    def value_to_string(self,value):
        return self.string_to_value(value)

class ConfigIntType(ConfigTypeBase):
    def string_to_value(self,string):
        return int(string)
    def value_to_string(self,value):
        return "%s" % value

class Config(object):
    @staticmethod
    def mapping_type(type_name,param):
        BUILDIN_TYPE={
        'string':ConfigStringType,
        'string-list':ConfigStringListType,
        'enum':ConfigEnumType,
        'int':ConfigIntType,
        }
        if type_name not in BUILDIN_TYPE:
            raise Exception("Unknow type '%s'" % type_name)
        return BUILDIN_TYPE[type_name](param)

    def __init__(self,segment,config_name,config_type,default_value,help_text,config_param):
        self.segment=segment
        self.config_name=config_name
        self.type=Config.mapping_type(config_type,config_param)
        self.default_value=self.type.string_to_value(default_value)
        self.help_text=help_text

    def gen_config_template(self):
        return "#%(help_text)s,默认值:'%(default_value)s'\n" \
               "#%(config_name)s = \n" % {'help_text':self.help_text,
        'config_name':self.config_name,
        'default_value':self.type.value_to_string(self.default_value)}

class ConfigManager(object):
    def __init__(self):
        self.cfg={}
    def add_config_item(self,segment,config_name,config_type,default_value,helper,config_param):
        
        config={
                config_name:Config(segment,config_name,config_type,default_value,helper,config_param)
               }
        if segment in self.cfg:
            self.cfg[segment].update(config)
        else:
            self.cfg[segment]=config

    def add_config(self,configs):
        for config in configs:
            self.add_config_item(config['segment'],
            config['config_name'],config['config_type'],
            config['default_value'],config['helper'],config['config_param'])

    def gen_config_template(self):
        result="#此文件自动生成\n#version=1.0\n\n"
        for key in sorted(self.cfg.keys()):
            value=self.cfg[key]
            result+="\n[%s]\n" % key
            for conf_name in sorted(value.keys()):
                config=value[conf_name]
                result+=config.gen_config_template()
        return result

    def _lookfor_cfg(self,segment,cfg_name):
        if segment not in self.cfg:
            return None
        cfg=self.cfg[segment].get(cfg_name,None)
        if cfg:
            return cfg.type
        return None

    def _parse_config(self,segment,config_line):
        equal_char=config_line.find('=')
        if equal_char == -1 or len(config_line) <= equal_char + 1:
            raise Exception("Invalid config line '%s'" % line)
        cfg_name=config_line[0:equal_char].strip()
        cfg_value=config_line[equal_char+1:].strip()
        cfg_type=self._lookfor_cfg(segment,cfg_name)
        if not cfg_type:
            raise Exception("Unkown config: \n[%s]\n%s" % (segment,config_line))
        
        return { cfg_name: cfg_type.string_to_value(cfg_value)}

    def parse_config_file(self,path):
        cfg={}
        try:
            cfg_file = open(path,'r')
            config_line=""
            segment_name=""
            for line in cfg_file.readlines():
                line=line.lstrip()
                if line.startswith('#'):#comment line
                    continue
                if line.endswith('\\'):
                    config_line+=line[:-1]#drop '\'
                    continue
                if config_line:
                    config_line += line
                    cfg[segment_name].update(self._parse_config(segment_name,config_line))
                    config_line=""
                    continue
                if line.startswith('['): #segment begin
                    segment_name=line.rstrip()[1:-1] #drop '[' ']'
                    cfg[segment_name]={}
                    continue
                else: #normal line
                    if "" == line.strip():
                        continue #skip blank line
                    print("adafdfda",segment_name)
                    cfg[segment_name].update(self._parse_config(segment_name,line))

            if "" in cfg:
                raise Exception("Unkown segment")
        except IOError as e:
            raise
        return cfg
