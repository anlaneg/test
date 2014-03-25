package cn.along.easyweb.core.flowframe.test;

import cn.along.easyweb.core.flowframe.ICheck;
import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IState;

public class LoginCheck implements ICheck
{
	public String check(IState self, IEasywebInputAdapter input)
	{
		// TODO Auto-generated method stub
		LoginState user = (LoginState) self;
		if ("along".equals(((Login)user.getInput()).getName())
				&& "packet".equals(((Login)user.getInput()).getPassword()))
		{
			return "login_success";
		}
		else
		{
			return "login_fail";
		}
	}

}
