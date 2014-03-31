package cn.along.easyweb.core.maps.test;

import cn.along.easyweb.core.config.ConfigPath;
import cn.along.easyweb.core.flowframe.IState;
import cn.along.easyweb.core.flowframe.test.demon1.Login;
import cn.along.easyweb.core.flowframe.test.demon1.LoginState;
import cn.along.easyweb.core.maps.EasywebConfigFile;
import cn.along.easyweb.core.maps.EasywebMaps;

public class EasywebMapsTest
{
	public static void main(String[] args)
	{
		EasywebMaps maps = new EasywebConfigFile();
		maps.buildEasywebConfig(new String[]{new ConfigPath().getConfigPath("easyweb.maps")});
		IState state = new LoginState();
		Login login = new Login();
		login.setName("along");
		login.setPassword("packet");
		state.setInput(0, login);
		String value = maps.lookfor("cn.along.easyweb.core.flowframe.test.demon1.Login",state,null);
		System.out.println(value);
	}
}
