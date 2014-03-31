package cn.along.easyweb.core.flowframe;

import cn.along.easyweb.core.flowframe.exception.AutoFillException;
import cn.along.easyweb.core.flowframe.exception.ResultFillException;
import cn.along.easyweb.core.flowframe.exception.StateCheckException;

public interface IState
{
	public void setInput(int idx, Object obj);

	public Object getInput();

	public void fill(IEasywebInputAdapter input) throws AutoFillException;

	public StateCheckResult doCheck(IEasywebInputAdapter input)
			throws StateCheckException;

	public void resultFill(IEasywebInputAdapter input,
			StateCheckResult checkResult) throws ResultFillException;

	public IState nextState();
}
