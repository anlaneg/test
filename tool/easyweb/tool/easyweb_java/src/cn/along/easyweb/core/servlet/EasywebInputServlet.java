package cn.along.easyweb.core.servlet;

import javax.servlet.ServletRequest;

import cn.along.easyweb.core.environment.Environment;
import cn.along.easyweb.core.environment.IEnvironment;
import cn.along.easyweb.core.flowframe.ICheck;
import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IInput;
import cn.along.easyweb.core.flowframe.IState;
import cn.along.easyweb.core.flowframe.test.LoginCheck;
import cn.along.easyweb.core.javajson.EasywebJson;
import cn.along.easyweb.core.javajson.Json2Java;

public class EasywebInputServlet implements IEasywebInputAdapter
{
	private ServletRequest req;
	private IEnvironment env;

	public EasywebInputServlet(ServletRequest req, IEnvironment env)
	{
		super();
		this.req = req;
		this.env = env;
	}

	public IState getRequestState()
	{
		String json = req.getParameter("hello");
		Environment.log.debug(json);
		Object obj = null;
		try
		{
			//Ijson2java json2java = new Json2Java();
			//obj = json2java.json2java(json, Login.class);
			Json2Java json2java = new Json2Java();
			
			EasywebJson easyweb = (EasywebJson) json2java.json2java(json);
			obj = easyweb.getContent().get(0);
		}
		catch (Exception e)
		{
			Environment.log.error(e.getMessage());
		}
		
		IState state = ((IInput)obj).getState();//new LoginState();
		state.setInput(0, obj);
		return (IState)state;
	}

	public ICheck getRequestCheck()
	{
		//lookfor table for checkName
		return new LoginCheck();
	}

	public IEnvironment getRequestEnvironment()
	{
		return this.env;
	}

}
