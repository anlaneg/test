package cn.along.easyweb.core.flowframe.test.demon1;

import cn.along.easyweb.core.javajson.Ijava2json;

public class LoginSuccess implements Ijava2json
{
	private final String message = "login success";

	public String getMessage()
	{
		return message;
	}

	public String java2json()
	{
		return "{\"message\":\""+this.message+"\"}";
	}
}
