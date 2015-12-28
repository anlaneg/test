package cn.along.xrt;

public class XrtDefaultValue
{
    public XrtDefaultValue()
    {
    }

    public static int getIntValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        return Integer.parseInt(value);
    }

    public static byte getByteValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        return Byte.parseByte(value);
    }

    public static char getCharValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        if (value.length() != 1)
        {
            throw new ClassCastException("'" + value + "' length more than one");
        }
        return value.charAt(0);
    }

    public static short getShortValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        return Short.parseShort(value);
    }

    public static long getLongValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        return Long.parseLong(value);
    }

    public static float getFloatValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        return Float.parseFloat(value);
    }

    public static double getDoubleValue(String value)
    {
        if ("".equals(value))
        {
            return 0;
        }
        return Double.parseDouble(value);
    }

    public static boolean getBooleanValue(String value)
    {
        if ("".equals(value))
        {
            return false;
        }
        if (value.equals("true"))
        {
            return true;
        }
        else if (value.equals("false"))
        {
            return false;
        }
        else
        {
            throw new ClassCastException(
                    "boolean type value must is 'true' or 'false' --" + value);
        }
    }

    public static String getStringValue(String value)
    {
        return value;
    }
}
