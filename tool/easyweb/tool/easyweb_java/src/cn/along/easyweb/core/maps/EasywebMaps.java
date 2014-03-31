package cn.along.easyweb.core.maps;

import java.io.File;
import java.lang.reflect.Method;
import java.util.HashMap;

import cn.along.easyweb.core.environment.Environment;
import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IState;

public abstract class EasywebMaps
{
	private HashMap<String, EasywebConfig> hashmap;

	public EasywebMaps()
	{
		super();
		this.hashmap = new HashMap<String, EasywebConfig>();
	}

	public void buildEasywebConfig(String[] filePaths)
	{
		for (int i = 0; i < filePaths.length; ++i)
		{
			File file = new File(filePaths[i]);
			if (!file.exists())
			{
				Environment.log.warn("file:" + filePaths[i]
						+ " is not exsit,ingore!");
			}
			this.buildEasywebConfig(file, this.hashmap);
		}
	}

	public String lookfor(String name, IState self, IEasywebInputAdapter input)
	{
		return this.lookfor(name, hashmap, self, input);
	}

	public abstract void buildEasywebConfig(File file,
			HashMap<String, EasywebConfig> hashmap);

	public abstract String lookfor(String name,
			HashMap<String, EasywebConfig> hashmap, IState self,
			IEasywebInputAdapter input);
}
