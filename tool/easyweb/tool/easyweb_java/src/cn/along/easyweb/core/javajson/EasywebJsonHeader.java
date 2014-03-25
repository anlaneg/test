package cn.along.easyweb.core.javajson;

public class EasywebJsonHeader implements Ijava2json
{
	private int version;
	private String encode;
	private String[] name;

	public String getEncode()
	{
		return encode;
	}

	public void setEncode(String encode)
	{
		this.encode = encode;
	}

	public int getVersion()
	{
		return version;
	}

	public void setVersion(int version)
	{
		this.version = version;
	}

	public String java2json()
	{
		return "{ \"version\":" + version + ",\"encode\":" + this.encode
				+ "\",name\":[" + this.getNames() + "] }";
	}

	public String[] getName()
	{
		return name;
	}

	public void setName(String[] name)
	{
		this.name = name;
	}

	private String getNames()
	{
		String str = "";
		for (int i = 0; i < this.name.length; ++i)
		{
			str = str + "\"" + this.name[i] + "\",";
		}
		return str;
	}
}
