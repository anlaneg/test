package cn.along.xparse.parameter;

import org.w3c.dom.Element;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;

/**
 * <param type="string" name="">select * xx </param>
 * 
 * @author samsung
 *
 */
public class XparseParameter extends XparseBase
{
	private String type;
	private String name;
	private String value;

	public static XparseParameter parse(Element xmlNode)
	{
		Assert.test(xmlNode.getTagName().equals("param"));
		XparseParameter param = new XparseParameter();

		String name = xmlNode.getAttribute("name");
		param.setName(name);

		String type = xmlNode.getAttribute("type");
		Assert.test(type != null && !"".equals(type),
				"<param> tag must have 'type' attribute.");
		param.setType(type);

		param.setValue(xmlNode.getTextContent());

		return param;
	}

	private void setValue(String textContent)
	{
		this.value = textContent;
	}

	private void setType(String type2)
	{
		this.type = type2;
	}

	private void setName(String attribute)
	{
		this.name = attribute;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<param type=\"" + this.type + "\" name=\"" + this.name
				+ "\">");
		builder.append(this.value);
		builder.append("</param>");
		return builder.toString();
	}

	public String getName()
	{
		return this.name;
	}

	public String getValue()
	{
		return this.value;
	}

	public String getType()
	{
		return this.type;
	}
}
