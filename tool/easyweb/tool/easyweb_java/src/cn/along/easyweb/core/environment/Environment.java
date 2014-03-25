package cn.along.easyweb.core.environment;

import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

public class Environment implements IEnvironment
{
	static
	{
		PropertyConfigurator
				.configure("/home/along/project/cworkspace/easyweb_java/src/lg4j.properties");
	}
	public static final Logger log = Logger.getLogger(Environment.class);
	private static IEnvironment env = new Environment();

	private Environment()
	{
		super();
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

	// xxx 添加其它项
}
