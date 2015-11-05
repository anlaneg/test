package cn.along.xparse.common;

public class Assert
{
	public static void test(boolean expr, String msg)
	{
		if (!expr)
		{
			throw new AssertException(msg);
		}
	}

	public static void test(boolean expr)
	{
		test(expr, "Assert fail");
	}

}
