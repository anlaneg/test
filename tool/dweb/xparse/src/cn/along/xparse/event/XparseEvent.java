package cn.along.xparse.event;

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
import cn.along.xparse.validator.XparseValidator;

/**
 * <!-- 目前没有定义事件，处理filter模式时有问题 (解决） <event> <event-action class-name="class.xx"
 * triggest="xx"> <param name="" type="">value</param> </event-action> </event>
 * -->
 * 
 * @author samsung
 *
 */
public class XparseEvent extends XparseBase
{
	private Vector<XparseEventAction> actions;

	private XparseEvent()
	{
		this.actions = new Vector<XparseEventAction>();
	}

	public static XparseBase parse(Element xmlNode)
			throws XparseSyntaxException
	{
		XparseEvent event = new XparseEvent();

		NodeList nodes = xmlNode.getChildNodes();
		for (int i = 0; i < nodes.getLength(); ++i)
		{
			Node node = nodes.item(i);
			if (node.getNodeType() == Node.ELEMENT_NODE)
			{
				if ("event-action".equals(((Element) node).getTagName() ))
				{
					XparseEventAction eventAction = XparseEventAction
							.parse((Element) node);
					event.addEventAction(eventAction);
				}
				else
				{
					throw new XparseSyntaxException(
							"Unkown tag name in 'event' : '"
									+ ((Element) node).getTagName() + "'");
				}
			}
		}
		return event;
	}

	private void addEventAction(XparseEventAction eventAction)
	{
		this.actions.add(eventAction);
	}

	public String createString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("<event>");
		for (int i = 0; i < this.actions.size(); ++i)
		{
			XparseEventAction action = this.actions.get(i);
			builder.append(action.createString());
		}
		builder.append("</event>");
		return builder.toString();
	}
}
