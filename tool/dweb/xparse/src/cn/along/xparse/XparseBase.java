package cn.along.xparse;

import org.w3c.dom.Element;

import cn.along.xgen.common.IteratorHelper;
import cn.along.xgen.common.XgenException;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.input.XparseInput;

public abstract class XparseBase
{
	public static XparseBase parse(Element xmlNode)
			throws XparseSyntaxException
	{
		throw new XparseSyntaxException("Unkown syntax exception");
	}
	
	public abstract String createString();

	
	//public abstract String genFillFunction(XparseInput input, IteratorHelper helper)throws XgenException;

	//public abstract String genFillCall(XparseInput input, IteratorHelper helper)throws XgenException;
	
	public  String genFillFunction(XparseInput input, IteratorHelper helper)throws XgenException
	{
		return null;
	}

	public  String genFillCall(XparseInput input, IteratorHelper helper)throws XgenException
	{
		return null;
	}
}
