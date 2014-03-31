package cn.along.easyweb.core.flowframe.test.demon1;

import cn.along.easyweb.core.flowframe.IInput;
import cn.along.easyweb.core.flowframe.IState;

public class Login implements IInput
{
	private String name;
	private String password;

	public String getName()
	{
		return name;
	}

	public void setName(String name)
	{
		this.name = name;
	}

	public String getPassword()
	{
		return password;
	}

	public void setPassword(String password)
	{
		this.password = password;
	}

	public String java2json()
	{
		return "{\"name\":\"along\",\"password\":\"hello\"}";
	}

	public IState getState()
	{
		return new LoginState();
	}
	
}
