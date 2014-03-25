package cn.along.easyweb.core.flowframe;

import cn.along.easyweb.core.flowframe.exception.AutoFillException;
import cn.along.easyweb.core.flowframe.exception.ResultFillException;
import cn.along.easyweb.core.flowframe.exception.StateCheckException;

public interface IEasywebOutputAdapter
{

	public void output(StateCheckResult check_result);

	public void output(AutoFillException e);

	public void output(StateCheckException e);

	public void output(ResultFillException e);

}
