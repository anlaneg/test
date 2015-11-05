package cn.along.xparse.common;

public class DefaultValue
{
	public static <T> T get(T value,T default_value)
	{
		if(value == null || ((value instanceof String) && value.equals("")))
		{
			return default_value;
		}
		return value;
	}
}