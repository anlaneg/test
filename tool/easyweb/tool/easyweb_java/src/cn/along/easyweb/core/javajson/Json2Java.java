package cn.along.easyweb.core.javajson;

import java.util.ArrayList;

import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

public class Json2Java implements Ijson2java
{
	public Object json2java(String json, Class java_class)
	{
		JSONObject jsonObject = JSONObject.fromObject(json);
		return JSONObject.toBean(jsonObject, java_class);
	}

	public EasywebJson json2java(String json) throws ClassNotFoundException
	{
		JSONObject jsonObject = JSONObject.fromObject(json);

		JSONObject header = jsonObject.getJSONObject("head");
		JSONObject extend = jsonObject.getJSONObject("extend");
		JSONArray content = jsonObject.getJSONArray("content");// .getJSONObject("content");

		if (header == null)
		{
			return null;
		}

		EasywebJson easyweb = new EasywebJson();
		easyweb.setHead((EasywebJsonHeader) JSONObject.toBean(header,
				EasywebJsonHeader.class));
		if (extend != null)
		{
			easyweb.setExtend((EasywebJsonExtend) JSONObject.toBean(extend,
					EasywebJsonExtend.class));
		}

		String[] names = easyweb.getHead().getName();
		ArrayList<Object> objlist = new ArrayList<Object>();
		for(int i = 0 ; i < names.length;++i)
		{
			JSONObject elem = content.getJSONObject(i);
			Class<?> bean = Class.forName(names[i]);
			Object obj = JSONObject.toBean(elem,bean);
			objlist.add(obj);
		}
		easyweb.setContent(objlist);

		return easyweb;
	}
}
