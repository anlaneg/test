package cn.along.easyweb.core.flowframe;

import org.apache.log4j.Logger;

import cn.along.easyweb.core.flowframe.exception.AutoFillException;
import cn.along.easyweb.core.flowframe.exception.ResultFillException;
import cn.along.easyweb.core.flowframe.exception.StateCheckException;

public class Easyweb
{
	public static boolean entry(IEasywebInputAdapter input,
			IEasywebOutputAdapter output)
	{
		assert (input != null && output != null);
		StateCheckResult check_result = null;
		IState nextState;
		IState currentState = input.getRequestState();
		//ICheck check = input.getRequestCheck(currentState);
		Logger logger = input.getRequestEnvironment().getLogger();

		do
		{
			try
			{
				logger.debug("do state fill");
				currentState.fill(input);// var,session,application,method,database
											// fill
				logger.debug("do state check");
				check_result = currentState.doCheck(input);// do
																	// check,and
																	// get
																	// output,forward
				currentState.resultFill(input, check_result);

				logger.debug("do state get nextstate");
				if ((nextState = currentState.nextState()) == null)
				{
					// 如果自动填充失败，说明有问题，这里不做任何的输出填充
					logger.debug("do state output");
					output.output(check_result);
					return true;
				}
			}
			catch (AutoFillException e)
			{
				output.output(e);
				// 如果自动填充失败，说明有问题，这里不做任何的输出填充
				break;
			}
			catch (StateCheckException e)
			{
				output.output(e);
				// 如果检查结束，则需要进行输出处理。
				break;
			}
			catch (ResultFillException e)
			{
				output.output(e);
				// 如果检查结束，则需要进行输出处理。
				break;
			}

			currentState = nextState;
		} while (true);

		return false;
	}

}
