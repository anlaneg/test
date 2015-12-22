package cn.along.xrt;

public class DefaultValue
{
	public DefaultValue()
	{
	}

	public static int getIntValue(String value)
	{
		return Integer.parseInt(value);
	}

	public static byte getByteValue(String value)
	{
		return Byte.parseByte(value);
	}

	public static char getCharValue(String value)
	{
		return '0';
	}

	public static short getShortValue(String value)
	{
		return Short.parseShort(value);
	}

	public static long getLongValue(String value)
	{
		return Long.parseLong(value);
	}

	public static float getFloatValue(String value)
	{
		return Float.parseFloat(value);
	}

	public static double getDoubleValue(String value)
	{
		return Double.parseDouble(value);
	}

	public static boolean getBooleanValue(String value)
	{
		return Boolean.parseBoolean(value);
	}

	public static String getStringDefaultValue(String value)
	{
		if (value != null)
		{
			return value;
		}
		return "";
	}
}
