package cn.along.easyweb.core.flowframe;

import cn.along.easyweb.core.environment.IEnvironment;

public interface IEasywebInputAdapter
{
	public IState getRequestState();
	public ICheck getRequestCheck();
	public IEnvironment getRequestEnvironment();
}
