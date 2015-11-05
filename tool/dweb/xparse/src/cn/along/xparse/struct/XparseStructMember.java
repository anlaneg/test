package cn.along.xparse.struct;

import org.w3c.dom.Element;

import cn.along.xgen.common.StringUtil;
import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.DefaultValue;
import cn.along.xparse.common.XparseSyntaxException;

/**
 * 
 * <code>
 *  <member name="user_name" type="bytion/short/int/long/float/double/boolean/class/byte[]" 
 *  length="2,3" dynamic-size="true/flase" pass-type="in/out/inout" 
 *  comment="用户名" default="" />
 *  </code>
 * 
 * @author samsung
 *
 */
public class XparseStructMember extends XparseBase
{
	private String name;

	private String type;
	private boolean is_class;
	private boolean is_array;
	private boolean is_dynamic_size;
	private int[] length;

	private String passType;
	private String comment;
	private String def;
	private XparseStruct struct;

	private XparseStructMember()
	{
		this.passType = "in";
	}

	public static XparseStructMember parse(Element xmlNode, XparseStruct struct)
			throws XparseSyntaxException
	{
		XparseStructMember member = new XparseStructMember();

		if (!xmlNode.getTagName().equals("member"))
		{
			throw new XparseSyntaxException("Expect Tag 'member' but '"
					+ xmlNode.getTagName() + "'");
		}

		member.setName(xmlNode.getAttribute("name"));
		member.setType(xmlNode.getAttribute("type"),
				DefaultValue.get(xmlNode.getAttribute("length"), "1"),
				DefaultValue.get(xmlNode.getAttribute("dynamic-size"), "false"));
		member.setPassType(DefaultValue.get(xmlNode.getAttribute("pass-type"),
				"in"));
		member.setComment(DefaultValue.get(xmlNode.getAttribute("comment"), ""));
		member.setDefault(DefaultValue.get(xmlNode.getAttribute("default"), ""));

		member.setStruct(struct);
		return member;
	}

	private void setStruct(XparseStruct struct2)
	{
		Assert.test(struct2 != null, "struct must not null");
		this.struct = struct2;

	}

	private void setDefault(String attribute)
	{
		this.def = attribute;
	}

	private void setComment(String attribute)
	{
		this.comment = attribute;
	}

	private void setPassType(String attribute) throws XparseSyntaxException
	{
		switch (attribute)
		{
		case "in":
		case "out":
		case "inout":
			this.passType = attribute;
			break;
		default:
			throw new XparseSyntaxException("Unkown Pass Type:'" + type + "'");
		}
	}

	private void setType(String type, String length, String dynamic_size)
			throws XparseSyntaxException
	{
		this.setMemberType(type);
		this.setMemberLength(length);
		this.setMemberIsDynamicSize(dynamic_size);
	}

	private void setMemberType(String type2) throws XparseSyntaxException
	{
		Assert.test(type2 != null);
		type2 = type2.trim();
		if (type2.endsWith("[]"))
		{
			this.is_array = true;
			type2 = type2.substring(0, type2.length() - 2).trim();
		}

		switch (type2)
		{
		case "byte":
		case "char":
		case "short":
		case "int":
		case "long":
		case "float":
		case "double":
		case "boolean":
		case "String":
			break;
		default:
			if (type2.startsWith("class:"))
			{
				type2 = type2.substring("class:".length()).trim();
				this.is_class = true;
				break;
			}
			throw new XparseSyntaxException("Unkown Type :'" + type2 + "'");
		}

		this.type = type2;
	}

	private void setMemberLength(String length2) throws XparseSyntaxException
	{
		String[] lens = length2.split(",");
		this.length = new int[lens.length];
		for (int i = 0; i < lens.length; ++i)
		{
			try
			{
				length[i] = Integer.parseInt(lens[i]);
			}
			catch (NumberFormatException e)
			{
				throw new XparseSyntaxException("Unkown Array Size : '"
						+ lens[i] + "' (idx=" + i + ",text='" + length2 + "')");
			}
		}
	}

	private void setMemberIsDynamicSize(String dynamic_size)
			throws XparseSyntaxException
	{
		switch (dynamic_size)
		{
		case "true":
			this.is_dynamic_size = true;
			break;
		case "false":
			this.is_dynamic_size = false;
			break;
		default:
			throw new XparseSyntaxException("Unkown Dynamic Size : '"
					+ dynamic_size + "'");
		}
	}

	private void setName(String attribute)
	{
		Assert.test(attribute != null);
		this.name = attribute;
	}

	public String typeString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("type=\"" + this.type + (this.is_array ? "[]" : "")
				+ "\" length=\"");
		for (int i = 0; i < this.length.length; ++i)
		{
			builder.append(this.length[i]);
			if (i + 1 < this.length.length)
			{
				builder.append(",");
			}
		}
		builder.append("\" dynamic-size=\"" + this.is_dynamic_size + "\"");
		return builder.toString();
	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<member name=\"" + this.name + "\" "
				+ this.typeString() + " pass-type=\"" + this.passType
				+ "\" comment=\"" + this.comment + "\" default=\"" + this.def
				+ "\" />");
		return builder.toString();
	}

	public String getType()
	{
		String type = this.type;
		if (this.is_array)
		{
			int[] size = this.length;// .type.getArraySize();
			for (int i = 0; i < size.length; ++i)
			{
				type += "[]";
			}
		}
		return type;
	}

	public String getVariableName()
	{
		return this.name;
	}

	public String getComment()
	{
		return this.comment;
	}

	public String getContructor()
	{
		String fun_name = "get" + StringUtil.initialUpper(this.type);
		if (this.is_array)
		{
			fun_name += "Array";
		}
		fun_name += "()";

		StringBuilder builder = new StringBuilder();
		builder.append("new int[]{");
		for (int i = 0; i < this.length.length; ++i)
		{
			builder.append(this.length[i]);
			if (i + 1 != this.length.length)
			{
				builder.append(",");
			}
		}
		builder.append("}");

		switch (this.type)
		{
		case "byte":
		case "char":
		case "short":
		case "int":
		case "long":
		case "float":
		case "double":
		case "boolean":
		case "String":
			return "new XRuntimeDefaultValue(" + builder.toString()
					+ ", new String[]{" + this.def + "})." + fun_name;
		default:
			return "new " + this.type + "()";
		}
	}
}
