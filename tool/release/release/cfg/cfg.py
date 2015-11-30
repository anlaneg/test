class ConfigTypeBase(object):
    def __init__(config_param):
        self.param=config_param

    def string_to_value(self,string):
        pass
    def value_to_string(self,value):
        pass
    
class ConfigStringType(ConfigTypeBase):
    def string_to_value(self,string):
        pass
    def value_to_string(self,value):
        pass

class ConfigStringListType(ConfigTypeBase):
    def string_to_value(self,string):
        pass
    def value_to_string(self,value):
        pass

class ConfigEnumType(ConfigTypeBase):
    def string_to_value(self,string):
        pass
    def value_to_string(self,value):
        pass

class ConfigIntType(ConfigTypeBase):
    def string_to_value(self,string):
        pass
    def value_to_string(self,value):
        pass

class ConfigType(object):
    BUILDIN_TYPE={
        'string':ConfigStringType,
        'string-list':ConfigStringListType,
        'enum':ConfigEnumType,
        'int':ConfigIntType,
    }
    @staticmethod
    def mapping_type(type_name,param):
        if type_name not in BUILDIN_TYPE:
            raise Exception("Unknow type '%s'" % type_name)
        return BUILDIN_TYPE[type_name](param)

class Config(object):
    def __init__(self,segment,config_name,config_type,default_value,help_text,config_param):
        self.segment=segment
        self.config_name=segment
        #self.config_param=config_param
        self.type=ConfigType.mapping_type(config_type,config_param)
        self.default_value=self.type.string_to_value(default_value)
        self.help_text=help_text

    def gen_config_template():
        return """
#%(help_text)s
#default value
#%(config_name)s = %(default_value)s
#%(config_name)s = 
""" % {'help_text':self.help_text,
        'config_name':self.config_name,
        'default_value':self.type.value_to_string(self.default_value)}

class ConfigManager(object):
    def __init__(self):
        self.cfg={}
    def addConfig(self,segment,config_name,config_type,default_value,helper,config_param):
        
        config={
                config_name:Config(segment,config_name,config_type,default_value,helper,config_param)
               }
        if segment in self.cfg:
            self.cfg[segment].update(config)
        else:
            self.cfg[segment]=config
    def addConfig(self,*config):
        for i in config:
            self.addConfig(i)
    def gen_config_template(self):
        result=""
        for key,value in self.cfg:
            result+="\n[%s]\n" % key
            for conf_name,confg in value:
                result+=config.gen_config_template()
        return result
    def _parse_config(segment,config_line):
        equal_char=config_line.find('=')
        if equal_char == -1 || len(line) <= equal_char + 1:
            raise Exception("Invalid config line '%s'" % line)
        return { line[0:equal_char].strip():line[equal_char+1:].lstrip() }
    def parse_config_file(self,path):
        cfg={}
        try:
            cfg_file = open(path,'r')
            config_line=""
            segment_name=""
            for line in cfg_file.readlines():
                line=line.lstrip()
                if line.startswith('#'):
                    #comment line
                    continue
                if line.endswith('\\'):
                    #drop '\'
                    config_line+=line[:-1]
                    continue
                if config_line:
                    config_line += line
                    cfg[segment_name].update(self._parse_config(segment_name,config_line))
                    config_line=""
                    continue
                if line.startwith('['):
                    #segment begin
                    segment_name=line.rstrip()[1:-1] #drop '[' ']'
                    continue
                else:
                    #normal line
                    cfg[segment_name].update(self._parse_config(segment_name,line))
            if "" in cfg:
                raise Exception("Unkown segment")
        except IOError as e:
            print(e)
        return cfg
