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
    
    private static String makeIndent(int count)
    {
        if(count == 0)
        {
            return "";
        }
        return StringUtil.times(" ",count-1);
    }

    public static String[] parseArray(String strArray)
    {
        String split_char = StringUtil.split_char;
        if (strArray.startsWith(StringUtil.split_keyword))
        {
            split_char = strArray.charAt(StringUtil.split_keyword.length())
                    + "";
            strArray = strArray
                    .substring(StringUtil.split_keyword.length() + 1);
        }

        return strArray.split(split_char);
    }

    public static String codeFormat(String code)
    {
        String[] lines = code.split("\n");
        StringBuilder builder = new StringBuilder();

        int indent = 0;
        final int indent_size = 4;
        for (int i = 0; i < lines.length; ++i)
        {
            //System.err.println("[" + i + "]=" + lines[i]);
            
      
            if (lines[i].equals("{"))
            {
                builder.append(StringUtil.makeIndent(indent));
                builder.append("{\n");
                indent += indent_size;
                continue;
            }

            if (lines[i].equals("}") || lines[i].equals("};") || lines[i].equals("},"))
            {
                indent -= indent_size;
                builder.append(StringUtil.makeIndent(indent));
                builder.append(lines[i]);
                builder.append("\n");
                continue;
            }
            
            builder.append(StringUtil.makeIndent(indent));
            builder.append(lines[i]);
            builder.append("\n");
        }

        //return builder.toString();
        String ret = builder.toString();
        //System.err.println(ret);
        return ret;
    }
}
