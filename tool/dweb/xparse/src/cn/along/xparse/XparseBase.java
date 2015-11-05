package cn.along.xparse;

import org.w3c.dom.Element;

import cn.along.xparse.common.XparseSyntaxException;

public abstract class XparseBase
{
	public static XparseBase parse(Element xmlNode)
			throws XparseSyntaxException
	{
		throw new XparseSyntaxException("Unkown syntax exception");
	}
	
	public abstract String createString();
}
