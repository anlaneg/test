package cn.along.xparse.input;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xgen.common.IInputFillerIterator;
import cn.along.xgen.common.IInputStructIterator;
import cn.along.xgen.common.IteratorHelper;
import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.DefaultValue;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.global.XparseGlobal;
import cn.along.xparse.method.XparseMethod;
import cn.along.xparse.session.XparseSession;
import cn.along.xparse.sql.XparseSql;
import cn.along.xparse.struct.XparseStruct;
import cn.along.xparse.validator.XparseValidator;

/**
 * 
 * <input style="single/array"> <struct name="info" type="struct-type"> <!--
 * 目前数组类型未定义　 byte[] length="用逗号分隔各维度“ dynamic-size="true/false" (解决) -->
 * 
 * <member name="user_name"
 * type="bytion/short/int/long/float/double/boolean/class/byte[]" length="2,3"
 * dynamic-size="true/flase" pass-type="in/out/inout" comment="用户名" default=""
 * /> </struct>
 * 
 * 
 * @author samsung
 * 
 */
public class XparseInput extends XparseBase
{
	private String style;
	private Vector<XparseStruct> structs;
	private Vector<XparseBase> orderTags;

	private XparseInput()
	{
		this.structs = new Vector<XparseStruct>();
		this.orderTags = new Vector<XparseBase>();
	}

	public static XparseInput parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseInput input = new XparseInput();
		input.setStyle(DefaultValue.get(xmlNode.getAttribute("style"), "single"));

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				switch (((Element) node).getTagName())
				{
				case "struct":
					XparseStruct struct = XparseStruct.parse((Element) node);
					input.addStruct(struct);
					break;
				case "sql":
					XparseSql sql = XparseSql.parse((Element) node);
					// input.addSql(sql);
					input.addOrderTag(sql);
					break;
				case "method":
					XparseMethod method = XparseMethod.parse((Element) node);
					input.addOrderTag(method);
					// throw new XparseSyntaxException("unimplements");
					break;
				case "validators":
					XparseValidator validator = XparseValidator
							.parse((Element) node);
					input.addOrderTag(validator);
					break;
				case "session":
					XparseSession session = XparseSession.parse((Element) node);
					input.addOrderTag(session);
					break;
				case "global":
					XparseGlobal global = XparseGlobal.parse((Element) node);
					input.addOrderTag(global);
					break;
				default:
					throw new XparseSyntaxException(
							"Unkown tag name in 'input' : '"
									+ ((Element) node).getTagName() + "'");

				}
			}
		}
		return input;
	}

	private void addOrderTag(XparseBase base)
	{
		this.orderTags.add(base);
	}

	private void addStruct(XparseStruct struct)
	{
		this.structs.add(struct);
	}

	public void setStyle(String style) throws XparseSyntaxException
	{
		Assert.test(style != null, "Input sturct style need {single,array}");
		switch (style)
		{
		case "single":
		case "array":
			this.style = style;
			break;
		default:
			throw new XparseSyntaxException("Unkown input struct style:'"
					+ style + "'");
		}
	}
	
	public String getStyle()
	{
		return this.style;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<input style=\"" + this.style + "\">");
		for (int i = 0; i < this.structs.size(); ++i)
		{
			XparseStruct struct = this.structs.get(i);
			builder.append(struct.createString());
		}
		for (int i = 0; i < this.orderTags.size(); ++i)
		{
			XparseBase base = this.orderTags.get(i);
			builder.append(base.createString());
		}
		builder.append("</input>");
		return builder.toString();
	}

	public void inputStructForEach(Object obj, IInputStructIterator iterator)
	{
		int size = this.structs.size();
		for (int i = 0; i < size; ++i)
		{
			IteratorHelper helper = new IteratorHelper(i == 0, (i + 1) == size,
					i, size);
			iterator.iterator(this, this.structs.elementAt(i), helper, obj);
		}
	}

	public void inputFillerForEach(Object obj, IInputFillerIterator iterator)
	{
		int size = this.orderTags.size();
		for (int i = 0; i < this.orderTags.size(); ++i)
		{
			IteratorHelper helper = new IteratorHelper(i == 0, (i + 1) == size,
					i, size);
			iterator.iterator(this, this.orderTags.elementAt(i),helper, obj);
		}
	}

}
