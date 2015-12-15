package cn.along.xparse.validator;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;

/**
 * <validators> <field name=""/> <field-validator type="class-name" > <param
 * name="" type="">value</param> <param name="" type="">value</param>
 * <message>xxxxxx</message> </field-validator> </validators>
 * 
 * @author samsung
 *
 */
public class XparseValidator extends XparseBase
{
	private String filed_name;
	private XparseFieldValidator validator;

	private XparseValidator()
	{

	}

	public static XparseValidator parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseValidator validator = new XparseValidator();

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				if ("field".equals(((Element) node).getTagName()))
				{
					String name = ((Element) node).getAttribute("name");
					Assert.test(name != null && !"".equals(name));
					validator.setFieldName(name);
				}
				else if ("field-validator"
						.equals(((Element) node).getTagName()))
				{
					XparseFieldValidator fieldValidator = XparseFieldValidator
							.parse((Element) node);
					validator.setFieldValidator(fieldValidator);
				}
				else
				{
					throw new XparseSyntaxException(
							"Unkown tag name in 'validators' : '"
									+ ((Element) node).getTagName() + "'");

				}
			}
		}
		return validator;
	}

	private void setFieldName(String name)
	{
		this.filed_name = name;
	}

	private void setFieldValidator(XparseFieldValidator fieldValidator)
	{
		this.validator = fieldValidator;
	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<validators><field name=\"" + this.filed_name + "\" />");
		builder.append(this.validator.createString());
		builder.append("</validators>");
		return builder.toString();
	}

}
