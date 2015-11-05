package cn.along.xparse.xcase;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.output.XparseOutput;

/**
 * <default forward="welcome" break="true/false"> <output> <struct name=""
 * type=""> </struct> </output> </default>
 * 
 * @author samsung
 *
 */
public class XparseDefault extends XparseCaseBase
{
	private XparseDefault()
	{

	}

	public static XparseDefault parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseDefault xdefault = new XparseDefault();
		XparseCaseBase.parse(xdefault, xmlNode);
		
		return xdefault;
	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<default "
				+ super.createString() + ">");
		builder.append(this.output.createString());
		builder.append("</case>");
		return builder.toString();
	}

}
