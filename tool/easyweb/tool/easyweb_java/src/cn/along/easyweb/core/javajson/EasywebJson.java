package cn.along.easyweb.core.javajson;

import java.util.ArrayList;

public class EasywebJson implements Ijava2json
{
	private EasywebJsonHeader head;
	private EasywebJsonExtend extend;
	private ArrayList<Object> content;

	public ArrayList<Object> getContent()
	{
		return content;
	}

	public void setContent(ArrayList<Object> content)
	{
		this.content = content;
	}

	public EasywebJsonHeader getHead()
	{
		return head;
	}

	public void setHead(EasywebJsonHeader head)
	{
		this.head = head;
	}

	public EasywebJsonExtend getExtend()
	{
		return extend;
	}

	public void setExtend(EasywebJsonExtend extend)
	{
		this.extend = extend;
	}

	public String java2json()
	{
		String ret = "{ \"head\":";
		if (this.head != null)
		{
			ret += this.head.java2json();
		}
		else
		{
			ret += "null";
		}
		ret +=",\"content\":";
		if(this.content != null)
		{
			ret+="[";
			for(int i = 0 ; i < this.content.size();++i)
			{
				Ijava2json obj = (Ijava2json)this.content.get(i);
				ret += obj.java2json() ;
				ret += "," ;
			}
			ret+="]";
		}
		else
		{
			ret += "null";
		}

		ret += ",\"extend\":";
		if (this.extend != null)
		{
			ret += this.extend.java2json();
		}
		else
		{
			ret += "null";
		}

		ret += "}";
		return ret;
	}

}
