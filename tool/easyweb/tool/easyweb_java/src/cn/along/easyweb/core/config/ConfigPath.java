package cn.along.easyweb.core.config;


public class ConfigPath
{
	public String getConfigPath(String config_file_name)
	{
		String path ;
		path = ConfigPath.class.getResource("").getPath();
		System.out.println("path=" + path + config_file_name);
		return path + config_file_name;
	}
}
