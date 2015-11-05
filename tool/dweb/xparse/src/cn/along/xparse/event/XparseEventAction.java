package cn.along.xparse.event;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.DefaultValue;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.global.XparseGlobal;
import cn.along.xparse.method.XparseMethod;
import cn.along.xparse.parameter.XparseParameter;
import cn.along.xparse.session.XparseSession;
import cn.along.xparse.sql.XparseSql;
import cn.along.xparse.struct.XparseStruct;
import cn.along.xparse.validator.XparseValidator;

/**
 * <event-action class-name="class.xx" trigger="xx"> <param name=""
 * type="">value</param> </event-action>
 * 
 * @author samsung
 *
 */
public class XparseEventAction extends XparseBase
{
	private String class_name;
	private String trigger;
	private Vector<XparseParameter> parameters;
	
	private XparseEventAction()
	{
		this.parameters = new Vector<XparseParameter>();
	}
	
	public static XparseEventAction parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseEventAction eventAction = new XparseEventAction();
		
		String className = xmlNode.getAttribute("class-name");
		String trigger  = xmlNode.getAttribute("trigger");
		Assert.test(className != null && !"".equals(className));
		Assert.test(trigger != null && !"".equals(trigger));
		
		eventAction.setClassName(className);
		eventAction.setTrigger(trigger);
		
		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				switch (((Element) node).getTagName())
				{
				case "param":
					XparseParameter param = XparseParameter.parse((Element) node);
					eventAction.addParameter(param);
					break;
				default:
					throw new XparseSyntaxException(
							"Unkown tag name in 'event-action' : '"
									+ ((Element) node).getTagName() + "'");

				}
			}
		}
		return eventAction;
	}

	private void addParameter(XparseParameter param)
	{
		this.parameters.add(param);
	}

	private void setTrigger(String trigger2)
	{
		this.trigger = trigger2;
	}

	private void setClassName(String className)
	{
		this.class_name = className;
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<action-event ");
		builder.append("class-name=\""+ this.class_name + "\" trigger=\"" + this.trigger + "\">");
		for(int i = 0 ; i < this.parameters.size() ; ++i)
		{
			XparseParameter param = this.parameters.get(i);
			builder.append(param.createString());
		}
		builder.append("</action-event>");
		return null;
	}

}
