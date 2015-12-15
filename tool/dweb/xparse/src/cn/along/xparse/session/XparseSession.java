package cn.along.xparse.session;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.global.XparseMap;

/**
 * <session dir="in/out"> <map src="" target="" /> <session>
 * 
 * @author samsung
 *
 */
public class XparseSession extends XparseBase
{
	private String direction;
	private Vector<XparseMap> maps;

	private XparseSession()
	{
		this.maps = new Vector<XparseMap>();
	}

	public static XparseSession parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseSession session = new XparseSession();
		String dir = xmlNode.getAttribute("dir");
		if ("".equals(dir))
		{
			dir = "in";
		}
		Assert.test("in".equals(dir) || "out".equals(dir));
		session.setDirection(dir);

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				if ("map".equals(((Element) node).getTagName()))
				{
					XparseMap map = XparseMap.parse((Element) node);
					session.addMap(map);
				}
				else
				{
					throw new XparseSyntaxException(
							"Unkown tag name in 'session' : '"
									+ ((Element) node).getTagName() + "'");
				}
			}
		}

		return session;
	}

	private void addMap(XparseMap map2)
	{
		this.maps.add(map2);
	}

	private void setDirection(String dir)
	{
		this.direction = dir;

	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<session dir=\"" + this.direction + "\">");
		for (int i = 0; i < this.maps.size(); ++i)
		{
			XparseMap map = this.maps.get(i);
			builder.append(map.createString());
		}
		builder.append("</session>");
		return builder.toString();
	}
}
