package cn.along.xparse.validator;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.parameter.XparseParameter;

/**
 * <field-validator type="class-name" > <param name="" type="">value</param>
 * <param name="" type="">value</param> <message>xxxxxx</message>
 * </field-validator>
 * 
 * @author samsung
 *
 */
public class XparseFieldValidator extends XparseBase
{
	private String className;
	private String message;
	private Vector<XparseParameter> parameters;

	private XparseFieldValidator()
	{
		this.parameters = new Vector<XparseParameter>();
	}

	public static XparseFieldValidator parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseFieldValidator field = new XparseFieldValidator();

		String className = xmlNode.getAttribute("type");
		Assert.test(!"".equals(className));
		field.setClassName(className);
		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				switch (((Element) node).getTagName())
				{
				case "param":
					XparseParameter param = XparseParameter
							.parse((Element) node);
					field.addParameter(param);
					break;
				case "message":
					String message = ((Element) node).getTextContent();
					Assert.test(!"".equals(message));
					field.setMessage(message);
					break;
				default:
					throw new XparseSyntaxException(
							"Unkown tag name in 'field-validator' : '"
									+ ((Element) node).getTagName() + "'");

				}
			}
		}
		return field;
	}

	private void setMessage(String message2)
	{
		this.message = message2;
	}

	private void addParameter(XparseParameter param)
	{
		this.parameters.add(param);
	}

	private void setClassName(String className2)
	{
		this.className = className2;
	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<field-validator type=\"" + this.className + "\" >");
		for (int i = 0; i < this.parameters.size(); ++i)
		{
			XparseParameter param = this.parameters.elementAt(i);
			builder.append(param.createString());
		}
		builder.append("<message>" + this.message + "</message>");
		builder.append("</field-validator>");

		return builder.toString();
	}
}
