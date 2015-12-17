package cn.along.xparse.struct;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xgen.common.IStructMemberIterator;
import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;

/**
 * 
 * <code><struct name="info" type="struct-type"> <!-- 目前数组类型未定义　 byte[]
 * length="用逗号分隔各维度“ dynamic-size="true/false" (解决) -->
 * 
 * <member name="user_name"
 * type="bytion/short/int/long/float/double/boolean/class/byte[]" length="2,3"
 * dynamic-size="true/flase" pass-type="in/out/inout" comment="用户名" default=""
 * /> </struct>
 * </code>
 * 
 * @author samsung
 *
 */
public class XparseStruct extends XparseBase
{
	private String name;
	private String type;
	private Vector<XparseStructMember> members;

	private XparseStruct()
	{
		this.members = new Vector<XparseStructMember>();
	}

	public static XparseStruct parse(Element xmlNode)
			throws XparseSyntaxException
	{
		Assert.test(xmlNode.getTagName().equals("struct"));
		XparseStruct struct = new XparseStruct();
		struct.setName(xmlNode.getAttribute("name"));
		struct.setType(xmlNode.getAttribute("type"));

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				Assert.test(((Element) node).getTagName().equals("member"));
				XparseStructMember member = XparseStructMember.parse(
						(Element) node, struct);
				struct.addMember(member);
			}
		}

		return struct;
	}

	private void addMember(XparseStructMember member)
	{
		this.members.add(member);
	}

	private void setType(String attribute)
	{
		this.type = attribute;
	}

	private void setName(String attribute)
	{
		this.name = attribute;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<struct name=\"" + this.name + "\" type=\"" + this.type
				+ "\">");
		for (int i = 0; i < this.members.size(); ++i)
		{
			XparseStructMember member = this.members.get(i);
			builder.append(member.createString());
		}
		builder.append("</struct>");
		return builder.toString();
	}

	public String getName()
	{
		return this.name;
	}

	public String getType()
	{
		return this.type;
	}

	public void structMemberForEach(Object obj, IStructMemberIterator iterator)
	{
		for (int i = 0; i < this.members.size(); ++i)
		{
			XparseStructMember member = this.members.get(i);
			iterator.iterator(this, member, obj);
		}
	}
}