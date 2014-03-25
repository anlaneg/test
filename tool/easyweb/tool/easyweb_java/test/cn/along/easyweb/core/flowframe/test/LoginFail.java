package cn.along.easyweb.core.flowframe.test;

import cn.along.easyweb.core.javajson.Ijava2json;

public class LoginFail implements Ijava2json
{
	private final String message = "login fail";

	public String getMessage()
	{
		return message;
	}

	public String java2json()
	{
		return "{\"message\":\""+this.message+"\"}";
	}
}
