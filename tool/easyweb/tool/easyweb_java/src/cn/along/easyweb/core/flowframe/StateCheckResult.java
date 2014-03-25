package cn.along.easyweb.core.flowframe;

public class StateCheckResult
{
	private int index;
	private Object obj;

	public int getIndex()
	{
		return index;
	}

	public void setIndex(int index)
	{
		this.index = index;
	}

	public Object getObj()
	{
		return obj;
	}

	public void setObj(Object obj)
	{
		this.obj = obj;
	}

	public StateCheckResult(int index, Object obj)
	{
		super();
		this.index = index;
		this.obj = obj;
	}

}
