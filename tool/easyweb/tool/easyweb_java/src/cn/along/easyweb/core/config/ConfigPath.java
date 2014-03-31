package cn.along.easyweb.core.config;

/**
 * 获取Easyweb系统配置文件位置
 * @author along
 *
 */
public class ConfigPath
{
	/**
	 * 获取指定配置文件位置
	 * @param config_file_name 配置文件名称
	 * @return 配置文件位置
	 */
	public String getConfigPath(String configFileName)
	{
		String path ;
		path = ConfigPath.class.getResource("").getPath();
		System.out.println("path=" + path + configFileName);
		return path + configFileName;
	}
}
