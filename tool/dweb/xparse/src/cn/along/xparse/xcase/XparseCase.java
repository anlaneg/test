package cn.along.xparse.xcase;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

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
public class XparseCase extends XparseCaseBase
{
	private String value;

	public XparseCase()
	{
		
	}

	public static XparseCase parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseCase xcase = new XparseCase();

		String value = xmlNode.getAttribute("value");
		Assert.test(value != null && !"".equals(value));

		XparseCaseBase.parse(xcase, xmlNode);

		return xcase;
	}

	@Override
	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<case value=\"" + this.value + "\" "
				+ super.createString() + ">");
		builder.append(this.output.createString());
		builder.append("</case>");
		return builder.toString();
	}

}
