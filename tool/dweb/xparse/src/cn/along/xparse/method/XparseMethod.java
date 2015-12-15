package cn.along.xparse.method;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.parameter.XparseParameter;

/**
 * <method fun-name="class.bc"> <param type="string" name="">select * xx
 * </param> </method>
 * 
 * @author samsung
 *
 */
public class XparseMethod extends XparseBase
{
	private String class_name;
	private String method_name;

	private Vector<XparseParameter> params;

	private XparseMethod()
	{
		this.params = new Vector<XparseParameter>();
	}

	public static XparseMethod parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseMethod method = new XparseMethod();
		String class_method = xmlNode.getAttribute("fun-name");
		Assert.test(!"".equals(class_method) && class_method != null);
		method.setMethod(class_method);

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				if ("param".equals(((Element) node).getTagName()))
				{
					XparseParameter param = XparseParameter
							.parse((Element) node);
					method.addParameter(param);
				}
				else
				{
					throw new XparseSyntaxException("Unkown tag '"
							+ ((Element) node).getTagName()
							+ "' be fount at tag Method");
				}
			}
		}

		return method;
	}

	private void addParameter(XparseParameter param)
	{
		this.params.add(param);
	}

	private void setMethod(String class_method)
	{
		int method_ioc = class_method.lastIndexOf('.');
		String method = class_method;
		String class_name = "";
		if (method_ioc != -1)
		{
			method = class_method.substring(method_ioc + 1);
			class_name = class_method.substring(0, method_ioc);
		}

		this.method_name = method;
		this.class_name = class_name;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<method fun-name=\"" + this.class_name + "\">");
		for (int i = 0; i < this.params.size(); ++i)
		{
			XparseParameter param = this.params.get(i);
			builder.append(param.createString());
		}
		builder.append("</method>");
		return builder.toString();
	}
}
