package cn.along.easyweb.core.java2json.test;

import cn.along.easyweb.core.javajson.EasywebJson;
import cn.along.easyweb.core.javajson.Json2Java;

public class Json2javaTest
{
	public static void main(String[] args) throws ClassNotFoundException
	{
		String json = "{ \"head\":{ \"version\":1,\"encode\":\"utf-8\",\"name\":[\"cn.along.easyweb.core.flowframe.test.Login\",] },\"content\":[{\"name\":\"along\",\"password\":\"hello\"},],\"extend\":null}";

		//String json = "{ \"head\":{\"version\":1,\"encode\":\"utf-8\",\"name\":[\"cn.along.easyweb.core.flowframe.test.Login\"]},\"extend\":null,\"content\":[{\"name\":\"along\",\"password\":\"hello\"}] }";
		Json2Java json2java = new Json2Java();
		
		EasywebJson easyweb = (EasywebJson) json2java.json2java(json);
		System.out.println(easyweb.java2json());
		
	}
}
