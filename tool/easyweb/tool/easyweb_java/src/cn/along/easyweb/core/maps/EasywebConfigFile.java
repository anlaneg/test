package cn.along.easyweb.core.maps;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;

import cn.along.easyweb.core.environment.Environment;
import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IState;
import cn.along.easyweb.core.javajson.Ijson2java;
import cn.along.easyweb.core.javajson.Json2Java;

public class EasywebConfigFile extends EasywebMaps
{
	private int version;
	private EasywebMapConfig[] config;

	public int getVersion()
	{
		return version;
	}

	public void setVersion(int version)
	{
		this.version = version;
	}

	public EasywebMapConfig[] getConfig()
	{
		return config;
	}

	public void setConfig(EasywebMapConfig[] config)
	{
		this.config = config;
	}

	public void buildEasywebConfig(File file,
			HashMap<String, EasywebConfig> hashmap)
	{
		try
		{
			int length = (int) file.length();
			if (length < 0)
			{
				Environment.log.error("file " + file.getPath()
						+ "length to bigger");
				return;
			}
			char[] buffer = new char[length];
			FileReader reader = new FileReader(file);
			reader.read(buffer, 0, length);
			reader.close();

			Ijson2java json = new Json2Java();
			EasywebConfigFile config = (EasywebConfigFile) json.json2java(
					new String(buffer), EasywebConfigFile.class);
			this.buildEasywebConfig(config, hashmap);

		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	private void buildEasywebConfig(EasywebConfigFile fileConfig,
			HashMap<String, EasywebConfig> hashmap)
	{
		assert (fileConfig.getVersion() == 1);
		EasywebMapConfig[] mapConfig = fileConfig.getConfig();
		for (int i = 0; i < mapConfig.length; ++i)
		{
			String packageName = mapConfig[i].getPackageName();
			if (!(packageName == null || packageName.equals("")))
			{
				packageName = packageName + ".";
			}
			else
			{
				packageName = "";
			}
			EasywebConfig[] config = mapConfig[i].getMaps();
			for (int j = 0; j < config.length; ++j)
			{
				config[i].setName(packageName + config[i].getName());
				hashmap.put(config[i].getName(), config[i]);
			}
		}
	}

	@Override
	public String lookfor(String name, HashMap<String, EasywebConfig> hashmap,
			IState self, IEasywebInputAdapter input)
	{
		String value = null;
		EasywebConfig config = hashmap.get(name);
		input.getRequestEnvironment().getLogger().debug(name);
		input.getRequestEnvironment().getLogger().debug(hashmap.toString());
		try
		{
			Class<?> c = Class.forName(config.getClassName());
			Constructor<?> constr = c.getConstructor();
			Object obj = constr.newInstance();
			Method method = c.getMethod(config.getMethod(), IState.class,
					IEasywebInputAdapter.class);
			value = (String) method.invoke(obj, self, input);
		}
		catch (ClassNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (NoSuchMethodException e)
		{
			e.printStackTrace();
		}
		catch (SecurityException e)
		{
			e.printStackTrace();
		}
		catch (InstantiationException e)
		{
			e.printStackTrace();
		}
		catch (IllegalAccessException e)
		{
			e.printStackTrace();
		}
		catch (IllegalArgumentException e)
		{
			e.printStackTrace();
		}
		catch (InvocationTargetException e)
		{
			e.printStackTrace();
		}

		return value;
	}

}
