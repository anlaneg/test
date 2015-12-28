package cn.along.xgen.common;

public class StringUtil
{
    public static final String split_keyword = "split";
    public static final String split_char = ",";

    public static String initialUpper(String s)
    {
        return Character.toUpperCase(s.charAt(0)) + s.substring(1);
    }

    public static String times(String s, int count)
    {
        StringBuilder builder = new StringBuilder(s);
        for (int i = 0; i < count; ++i)
        {
            builder.append(s);
        }
        return builder.toString();
    }

    public static String[] parseArray(String strArray)
    {
        String split_char = StringUtil.split_char;
        if (strArray.startsWith(StringUtil.split_keyword))
        {
            split_char = strArray.charAt(StringUtil.split_keyword.length())
                    + "";
            strArray = strArray.substring(StringUtil.split_keyword.length()+1);
        }

        return strArray.split(split_char);
    }
}
