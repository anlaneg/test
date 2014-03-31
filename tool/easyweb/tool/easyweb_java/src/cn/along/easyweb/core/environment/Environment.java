package cn.along.easyweb.core.environment;

import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

import cn.along.easyweb.core.config.ConfigPath;
import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IState;
import cn.along.easyweb.core.maps.EasywebConfigFile;
import cn.along.easyweb.core.maps.EasywebMaps;

public class Environment implements IEnvironment
{
	static
	{
		PropertyConfigurator.configure(new ConfigPath()
				.getConfigPath("lg4j.properties"));
	}
	public static final Logger log = Logger.getLogger(Environment.class);
	private static IEnvironment env = new Environment();
	private EasywebMaps maps;

	private Environment()
	{
		super();
		this.maps = new EasywebConfigFile();
		maps.buildEasywebConfig(new String[]
		{ new ConfigPath().getConfigPath("easyweb.maps") });

	}

	public static IEnvironment getInstance()
	{
		return Environment.env;
	}

	public Logger getLogger()
	{
		return Environment.log;
	}

	public Object getSession(String name)
	{
		// TODO Auto-generated method stub
		return null;
	}

	public void putSession(String name, Object obj)
	{
		// TODO Auto-generated method stub

	}

	public Object getApplication(String name)
	{
		// TODO Auto-generated method stub
		return null;
	}

	public void putApplication(String name, Object obj)
	{
		// TODO Auto-generated method stub

	}
	
	public String getCheckResult(String name, IState self, IEasywebInputAdapter input)
	{
		return this.maps.lookfor(name, self, input);
	}

	// xxx 添加其它项
}
