package cn.along.easyweb.core.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServlet;

import cn.along.easyweb.core.environment.Environment;
import cn.along.easyweb.core.environment.IEnvironment;
import cn.along.easyweb.core.flowframe.Easyweb;
import cn.along.easyweb.core.flowframe.IEasywebOutputAdapter;

@SuppressWarnings("serial")
public class WebServerListeren extends HttpServlet
{

	public void service(ServletRequest req, ServletResponse res)
			throws ServletException, IOException
	{
		IEnvironment env = Environment.getInstance();
		EasywebInputServlet input = new EasywebInputServlet(req, env);
		EasywebOutputServlet output = new EasywebOutputServlet(res, env);
		Easyweb.entry(input,output);
	}
}
