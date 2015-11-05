package cn.along.xgen.common;

public class StringUtil
{
	public static String initialUpper(String s)
	{
		return Character.toUpperCase(s.charAt(0)) + s.substring(1);
	}
}
