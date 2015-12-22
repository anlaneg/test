package cn.along.xgen.common;

@SuppressWarnings("serial")
public class XgenUnSupportException extends XGenException
{

	public XgenUnSupportException()
	{
		super("Current version no support this operator!");
	}
	
}
