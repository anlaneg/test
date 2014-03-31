package cn.along.easyweb.core.environment;

import org.apache.log4j.Logger;

import cn.along.easyweb.core.flowframe.IEasywebInputAdapter;
import cn.along.easyweb.core.flowframe.IState;

public interface IEnvironment
{
	/**
	 * 获取logger
	 * 
	 * @return
	 */
	public Logger getLogger();

	/**
	 * 获取session
	 * 
	 * @param name
	 * @return
	 */
	public Object getSession(String name);

	/**
	 * 添加session
	 * 
	 * @param name
	 * @param obj
	 */
	public void putSession(String name, Object obj);

	/**
	 * 获取application
	 * 
	 * @param name
	 * @return
	 */
	public Object getApplication(String name);

	/**
	 * 设置application
	 * 
	 * @param name
	 * @param obj
	 */
	public void putApplication(String name, Object obj);

	/**
	 * 获取check结果
	 * @param name
	 * @param self
	 * @param input
	 * @return
	 */
	public String getCheckResult(String name, IState self,
			IEasywebInputAdapter input);
	// add database
}
