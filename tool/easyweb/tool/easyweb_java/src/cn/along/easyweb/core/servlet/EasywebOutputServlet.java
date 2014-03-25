package cn.along.easyweb.core.servlet;

import java.io.IOException;

import javax.servlet.ServletResponse;

import cn.along.easyweb.core.environment.IEnvironment;
import cn.along.easyweb.core.flowframe.IEasywebOutputAdapter;
import cn.along.easyweb.core.flowframe.StateCheckResult;
import cn.along.easyweb.core.flowframe.exception.AutoFillException;
import cn.along.easyweb.core.flowframe.exception.ResultFillException;
import cn.along.easyweb.core.flowframe.exception.StateCheckException;
import cn.along.easyweb.core.javajson.Ijava2json;

public class EasywebOutputServlet implements IEasywebOutputAdapter
{
	private ServletResponse res;
	private IEnvironment env;

	public EasywebOutputServlet(ServletResponse res, IEnvironment env)
	{
		super();
		this.res = res;
		this.env = env;
	}

	public void output(StateCheckResult check_result)
	{
		Ijava2json java = (Ijava2json) check_result.getObj();
		try
		{
			this.res.getWriter().write(java.java2json());
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public void output(AutoFillException e)
	{
		e.printStackTrace();
	}

	public void output(StateCheckException e)
	{
		e.printStackTrace();
	}

	public void output(ResultFillException e)
	{
		e.printStackTrace();
	}

}
