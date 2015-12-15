package cn.along.xparse.xswitch;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.xcase.XparseCase;
import cn.along.xparse.xcase.XparseDefault;

/**
 * <switch fun-name="class.fun-name"> <case value="1" redirect="name"
 * break="true/false"> </case> <default forward="welcome" break="true/false">
 * <output> <struct name="" type=""> </struct> </output> </default>
 * 
 * </switch>
 * 
 * @author samsung
 *
 */
public class XparseSwitch extends XparseBase
{
	private String fun_name;
	private Vector<XparseBase> xcase;
	private XparseDefault xdefault;

	private XparseSwitch()
	{
		this.xcase = new Vector<XparseBase>();
		this.xdefault = null;
	}

	public static XparseSwitch parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseSwitch xswitch = new XparseSwitch();

		String fun_name = xmlNode.getAttribute("fun-name");
		Assert.test(fun_name != null && !"".equals(fun_name));

		xswitch.setFunctionName(fun_name);

		NodeList nodes = xmlNode.getChildNodes();
		boolean is_find_default = false;
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				if ("case".equals(((Element) node).getTagName()))
				{
					XparseCase xcase = XparseCase.parse((Element) node);

					xswitch.addOrderCase(xcase);
				}
				else if ("default".equals(((Element) node).getTagName()))
				{
					if (!is_find_default)
					{
						XparseDefault xdefault = XparseDefault
								.parse((Element) node);
						xswitch.xdefault = xdefault;
						is_find_default = true;
					}
					else
					{
						xswitch.throwException("'default' tag must have and only have one");
					}
				}
				else
				{
					xswitch.throwException("Unkown tag in 'switch' :"
							+ ((Element) node).getTagName());

				}
			}
		}
		if (!is_find_default)
		{
			xswitch.throwException("'default' tag not find in 'switch'");
		}
		return xswitch;
	}

	private void throwException(String string) throws XparseSyntaxException
	{
		throw new XparseSyntaxException(string);
	}

	private void setFunctionName(String fun_name)
	{
		this.fun_name = fun_name;
	}

	private void addOrderCase(XparseBase base)
	{
		this.xcase.add(base);
	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<switch fun-name=\"" + this.fun_name + "\">");
		for (int i = 0; i < this.xcase.size(); ++i)
		{
			XparseBase base = this.xcase.elementAt(i);
			builder.append(base.createString());
		}
		builder.append("</switch>");
		return builder.toString();
	}
}
