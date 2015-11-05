package cn.along.xparse.global;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;

/**
 * <global dir="in/out"> <map src="" target="" /> <global>
 * 
 * @author samsung
 *
 */
public class XparseGlobal extends XparseBase
{
	private String direction;
	private Vector<XparseMap> maps;

	private XparseGlobal()
	{
		this.maps = new Vector<XparseMap>();
	}

	public static XparseGlobal parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseGlobal global = new XparseGlobal();
		String dir = xmlNode.getAttribute("dir");
		if ("".equals(dir))
		{
			dir = "in";
		}
		Assert.test("in".equals(dir) || "out".equals(dir));
		global.setDirection(dir);

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				switch (((Element) node).getTagName())
				{
				case "map":
					XparseMap map = XparseMap.parse((Element) node);
					global.addMap(map);
					break;
				default:
					throw new XparseSyntaxException(
							"Unkown tag name in 'global' : '"
									+ ((Element) node).getTagName() + "'");
				}
			}
		}

		return global;
	}

	private void addMap(XparseMap map2)
	{
		this.maps.add(map2);
	}

	private void setDirection(String dir)
	{
		this.direction = dir;

	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<global dir=\"" + this.direction + "\">");
		for(int i = 0 ; i < this.maps.size();++i)
		{
			XparseMap map = this.maps.get(i);
			builder.append(map.createString());
		} 
		builder.append("</global>");
		return builder.toString();
	}
}
