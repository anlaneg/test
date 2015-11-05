package cn.along.xparse.output;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.global.XparseGlobal;
import cn.along.xparse.method.XparseMethod;
import cn.along.xparse.session.XparseSession;
import cn.along.xparse.sql.XparseSql;
import cn.along.xparse.struct.XparseStruct;

public class XparseOutput extends XparseBase
{
	private XparseStruct struct;
	private Vector<XparseBase> orderTags;

	private XparseOutput()
	{
		this.orderTags = new Vector<XparseBase>();
	}

	public static XparseOutput parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseOutput output = new XparseOutput();

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
					output.setStruct(struct);
					break;
				case "sql":
					XparseSql sql = XparseSql.parse((Element) node);
					// input.addSql(sql);
					output.addOrderTag(sql);
					break;
				case "method":
					XparseMethod method = XparseMethod.parse((Element) node);
					output.addOrderTag(method);
					// throw new XparseSyntaxException("unimplements");
					break;
				case "session":
					XparseSession session = XparseSession.parse((Element) node);
					output.addOrderTag(session);
					break;
				case "global":
					XparseGlobal global = XparseGlobal.parse((Element) node);
					output.addOrderTag(global);
					break;
				default:
					throw new XparseSyntaxException(
							"Unkown tag name in 'output' : '"
									+ ((Element) node).getTagName() + "'");

				}
			}
		}
		return output;
	}

	private void setStruct(XparseStruct struct2)
	{
		this.struct = struct2;
	}

	private void addOrderTag(XparseBase base)
	{
		this.orderTags.add(base);
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<output>");
		builder.append(this.struct.createString());
		for(int i = 0 ; i < this.orderTags.size(); ++i)
		{
			XparseBase base = this.orderTags.get(i);
			builder.append(base.createString());
		}
		builder.append("</output>");
		return builder.toString();
	}
}