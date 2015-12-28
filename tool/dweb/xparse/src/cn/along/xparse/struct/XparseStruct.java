package cn.along.xparse.struct;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xgen.XGenConfig;
import cn.along.xgen.common.IStructMemberIterator;
import cn.along.xgen.common.StringUtil;
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

    @Override
    public String gen(XGenConfig config)
    {
        StringBuilder builder = new StringBuilder();
        builder.append(this.genClassHeader());
        builder.append("{\n");
        builder.append(this.genMemberVariable());
        builder.append(this.genClassContructor());
        builder.append(this.genMemberMethod());
        builder.append("}\n");
        
        config.out_file_name = StringUtil.initialUpper(this.getType());
        return builder.toString();
    }

    private String genClassHeader()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("import cn.along.xrt.XrtDefaultValue;\n");
        builder.append("\n");
        builder.append("public class "
                + StringUtil.initialUpper(this.getType()) + "\n");
        return builder.toString();
    }

    private String genClassContructor()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("\tpublic " + StringUtil.initialUpper(this.getType())
                + "()\n");
        builder.append("\t{\n");
        builder.append("\t\t//set member default value\n");
        this.structMemberForEach(builder, new IStructMemberIterator()
        {

            @Override
            public void iterator(XparseStruct struct,
                    XparseStructMember member, Object arg)
            {
                StringBuilder builder = (StringBuilder) arg;
                //builder.append("\t\t//set " + member.getVariableName() + " default value\n");
                builder.append("\t\tthis." + member.getVariableName() + "=" + member.getContructor() + "\n");
            }
        });     
        builder.append("\t}\n\n");
        return builder.toString();
    }

    private String genMemberVariable()
    {
        StringBuilder builder = new StringBuilder();
        this.structMemberForEach(builder, new IStructMemberIterator()
        {

            @Override
            public void iterator(XparseStruct struct,
                    XparseStructMember member, Object arg)
            {
                StringBuilder builder = (StringBuilder) arg;
                builder.append("\t// " + member.getComment().replaceAll("\n", " ") + "\n");
                builder.append("\tprivate " + member.getType() + " "
                        + member.getVariableName() + ";\n\n");
            }
        });

        return builder.toString();
    }

    private String genMemberMethod()
    {
        StringBuilder builder = new StringBuilder();
        this.structMemberForEach(builder, new IStructMemberIterator()
        {

            @Override
            public void iterator(XparseStruct struct,
                    XparseStructMember member, Object arg)
            {
                StringBuilder builder = (StringBuilder) arg;
                builder.append("\t//set " + member.getVariableName() + ":" + member.getComment().replaceAll("\n", " ") + "\n");
                builder.append("\tpublic void set"
                        + StringUtil.initialUpper(member.getVariableName())
                        + "(" + member.getType() + " "
                        + member.getVariableName() + ")\n");
                builder.append("\t{\n");
                builder.append("\t\tthis." + member.getVariableName() + "="
                        + member.getVariableName() + ";\n");
                builder.append("\t}\n\n");

                builder.append("\t//get " + member.getVariableName() + ":" + member.getComment().replaceAll("\n", " ") + "\n");
                builder.append("\tpublic " + member.getType() + " get"
                        + StringUtil.initialUpper(member.getVariableName())
                        + "()\n");
                builder.append("\t{\n");
                builder.append("\t\treturn this." + member.getVariableName()
                        + ";\n");
                builder.append("\t}\n\n");

            }
        });

        return builder.toString();
    }

	
	
}