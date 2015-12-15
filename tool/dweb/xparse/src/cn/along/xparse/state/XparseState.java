package cn.along.xparse.state;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.DefaultValue;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.input.XparseInput;
import cn.along.xparse.parameter.XparseParameter;
import cn.along.xparse.sql.XparseSql;
import cn.along.xparse.xswitch.XparseSwitch;

/**
 * <state name="Login" packet="cn.along.module.flow" version="1.0"> <input
 * style="single/array"> <struct name="info" type="struct-type"> ... </state>
 * 
 * @author samsung
 *
 */
public class XparseState extends XparseBase
{
	private XparseInput input;
	private XparseSwitch xswitch;
	private String packet;
	private String version;
	private String name;

	private XparseState()
	{

	}

	public static XparseState parse(Element xmlNode)
			throws XparseSyntaxException
	{
		Assert.test(xmlNode.getTagName().equals("state"));
		XparseState state = new XparseState();
		String name = xmlNode.getAttribute("name");
		Assert.test(name != null && !"".equals(name),
				"<state> tag must have 'name' attribute");
		String packet = xmlNode.getAttribute("packet");
		Assert.test(packet != null && !"".equals(packet),
				"<state> tag must have 'packet' attrubute");
		String version = DefaultValue.get(xmlNode.getAttribute("version"),
				"1.0");
		state.setName(name);
		state.setPacket(packet);
		state.setVersion(version);

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				if ("input".equals(((Element) node).getTagName()))
				{
					XparseInput input = XparseInput.parse((Element) node);
					Assert.test(input != null);
					state.setInput(input);
				}
				else if ("switch".equals(((Element) node).getTagName()))
				{
					XparseSwitch xswitch = XparseSwitch.parse((Element) node);
					Assert.test(xswitch != null);
					state.setSwitch(xswitch);
				}
				else
				{
					throw new XparseSyntaxException("Unkown tag in state :'"
							+ ((Element) node).getTagName() + "'");
				}
			}
		}

		return state;
	}

	private void setSwitch(XparseSwitch xswitch2)
	{
		this.xswitch = xswitch2;
	}

	private void setInput(XparseInput input2)
	{
		this.input = input2;
	}

	private void setVersion(String version2)
	{
		this.version = version2;
	}

	private void setPacket(String packet2)
	{
		this.packet = packet2;
	}

	private void setName(String attribute)
	{
		this.name = attribute;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<state version=\"" + this.version + "\" packet=\""
				+ this.packet + "\" name=\"" + this.name + ">");
		builder.append(this.input.createString());
		builder.append(this.xswitch.createString());
		builder.append("</state>");
		return builder.toString();
	}

}
