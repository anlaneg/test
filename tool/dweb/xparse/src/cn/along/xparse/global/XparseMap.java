package cn.along.xparse.global;

import org.w3c.dom.Element;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;

/**
 * <map src="" target="" />
 * 
 * @author samsung
 *
 */
public class XparseMap extends XparseBase
{
	private String src;
	private String target;

	private XparseMap()
	{

	}

	public static XparseMap parse(Element xmlNode) throws XparseSyntaxException
	{
		XparseMap map = new XparseMap();

		String src = xmlNode.getAttribute("src");
		Assert.test(!"".equals(src));
		String target = xmlNode.getAttribute("target");
		Assert.test(!"".equals(target));

		map.setSrc(src);
		map.setTarget(target);

		return map;
	}

	private void setTarget(String target2)
	{
		this.target = target2;
	}

	private void setSrc(String src2)
	{
		this.src = src2;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<map src=\"" + this.src + "\" target=\"" + this.target + "\" />");
		return builder.toString();
	}
}
