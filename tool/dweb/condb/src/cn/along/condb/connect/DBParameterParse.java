package cn.along.condb.connect;

import java.util.Vector;

import cn.along.condb.exception.DBException;

public class DBParameterParse
{
	public static String parseSqlParam(String sql, Vector<String> result)
			throws DBException
	{
		StringBuilder builder = new StringBuilder();

		int sql_len = sql.length();

		for (int i = 0; i < sql_len; ++i)
		{
			int current_letter = sql.charAt(i);
			if (current_letter == '@')
			{
				if (i + 1 < sql_len && sql.charAt(i + 1) != '@')
				{
					int end = DBParameterParse.parseSqlParamName(sql, i + 1);// skip '@'
					result.add(sql.substring(i + 1, end).replace("@@", "@"));
					// System.err.println("hello end:" + end + " result :" +
					// result.toString() + " start:" + i);
					i = end;
					builder.append(" ? ");
					continue;
				}

				// meet @@ or @'\0'
				builder.append("@");
				i = i + 1;
				continue;
			}
			builder.append(sql.charAt(i));
		}
		return builder.toString();
	}

	private static int parseSqlParamName(String sql, int i) throws DBException
	{
		int sql_len = sql.length();
		for (; i < sql_len; ++i)
		{
			int current_letter = sql.charAt(i);
			if (current_letter == '@')
			{
				if ((i + 1 < sql_len && sql.charAt(i + 1) != '@')
						|| (i + 1 == sql_len))
				{
					return i;
				}

				i += 1;// skip '@'
			}
		}

		throw new DBException("sql :" + sql + " not find '@' for "
				+ sql.substring(i));
	}

}
