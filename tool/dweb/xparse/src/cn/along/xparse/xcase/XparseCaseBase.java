package cn.along.xparse.xcase;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.output.XparseOutput;

/**
 * <case value="1" redirect="name" break="true/false"> <output> <struct name=""
 * type=""> </struct>
 * 
 * <sql> <delete>delete from users where user_name = ?<delete> <param
 * type="string" value="$SESSION.xx" /> </sql> <method fun-name="class.abc" >
 * <param type="" value="" /> </method> <session dir=""> <map src="" target=""
 * /> </session> <global dir=""> <map src="" target="" /> </global> </output>
 * </case>
 * 
 * @author samsung
 *
 */
public class XparseCaseBase extends XparseBase
{
	protected boolean isForward;
	protected String target;
	protected boolean has_break;
	protected XparseOutput output;

	public XparseCaseBase()
	{

	}

	public static void parse(XparseCaseBase xcaseBase, Element xmlNode)
			throws XparseSyntaxException
	{
		String redirect_tag = xmlNode.getAttribute("redirect");
		String forward_tag = xmlNode.getAttribute("forward");

		// 1 将两者都不存在的情况排除掉
		if ((redirect_tag == null || !"".equals(redirect_tag))
				&& (forward_tag == null || !"".equals(forward_tag)))
		{
			throw new XparseSyntaxException(
					"redirect/forward no support not exist both");
		}

		// 2 将两者都存在的情况排除掉
		if ((redirect_tag != null && !"".equals(redirect_tag))
				&& (forward_tag != null && !"".equals(forward_tag)))
		{
			throw new XparseSyntaxException(
					"redirect/forward no support exist always");
		}

		if (redirect_tag != null && !"".equals(redirect_tag))
		{
			xcaseBase.setRedirectTarget(redirect_tag);
		}
		else
		{
			xcaseBase.setForwardTarget(forward_tag);
		}

		String has_break = xmlNode.getAttribute("break");
		if (has_break != null && !"".equals(has_break))
		{
			switch ((has_break = (has_break.trim().toLowerCase())))
			{
			case "true":
			case "false":
				xcaseBase.setBreak(has_break);
				break;
			default:
				throw new XparseSyntaxException(
						"break attribute only 'true/false'");
			}
		}

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				switch (((Element) node).getTagName())
				{
				case "output":
					XparseOutput output = XparseOutput.parse((Element) node);
					xcaseBase.setOutput(output);
					break;
				default:
					throw new XparseSyntaxException("Unkown tag in 'case' :"
							+ ((Element) node).getTagName());
				}
			}
		}
	}

	protected void setOutput(XparseOutput output2)
	{
		this.output = output2;
	}

	protected void setBreak(String has_break2)
	{
		this.has_break = Boolean.getBoolean(has_break2);
	}

	protected void setRedirectTarget(String redirect_tag)
	{
		this.isForward = false;
		this.target = redirect_tag;
	}

	protected void setForwardTarget(String forward_tag)
	{
		this.isForward = true;
		this.target = forward_tag;
	}

	@Override
	public String createString()
	{
		String msg = "redirect";
		if (this.isForward)
		{
			msg = "forward";
		}
		return msg + "=\"" + this.target + "\" break=\"" + this.has_break +"\"";
	}
}
