package cn.along.easyweb.core.config.test;

import cn.along.easyweb.core.config.ConfigPath;

public class ConfigPathTest
{
  public static void main(String[] args)
  {
	  ConfigPath config = new ConfigPath();
	  String path = config.getConfigPath("lg4j.properties");
	  System.out.println(path);
  }
}
