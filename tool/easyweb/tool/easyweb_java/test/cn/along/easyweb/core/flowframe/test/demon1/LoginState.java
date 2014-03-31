package cn.along.easyweb.core.flowframe.test.demon1;

import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IState;
import cn.along.easyweb.core.flowframe.StateCheckResult;
import cn.along.easyweb.core.flowframe.exception.AutoFillException;
import cn.along.easyweb.core.flowframe.exception.ResultFillException;
import cn.along.easyweb.core.flowframe.exception.StateCheckException;

public class LoginState implements IState
{
	private Login login;

	public void fill(IEasywebInputAdapter input) throws AutoFillException
	{

	}

	public StateCheckResult doCheck(IEasywebInputAdapter input)
			throws StateCheckException
	{
		IState state = input.getRequestState();
		String result = input.getRequestEnvironment().getCheckResult(
				state.getInput().getClass().getName(), state, input);
		if ("login_success".equals(result))
		{
			LoginSuccess obj = new LoginSuccess();
			return new StateCheckResult(1, obj);
		}

		if ("login_fail".equals(result))
		{
			LoginFail obj = new LoginFail();
			return new StateCheckResult(2, obj);
		}

		throw new StateCheckException("no implements!\n");
	}

	public void resultFill(IEasywebInputAdapter input,
			StateCheckResult checkResult) throws ResultFillException
	{

	}

	public IState nextState()
	{
		return null;
	}

	public void setInput(int idx, Object obj)
	{
		this.login = (Login) obj;
	}

	public Object getInput()
	{
		return this.login;
	}
}
