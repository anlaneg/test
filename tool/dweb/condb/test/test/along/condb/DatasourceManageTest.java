package test.along.condb;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import cn.along.condb.api.SimpleDBAccess;
import cn.along.condb.inner.IDBConnect;

public class DatasourceManageTest
{
	public static <T> ArrayList<T> testLoadDataSource(Class<T> cl, String sql,
			Map<String, Object> param) throws Exception
	{
		System.out.println(System.currentTimeMillis());
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();

		ArrayList<T> logins = (ArrayList<T>) conn.query(cl, sql, param);
		SimpleDBAccess.getInstance().putConnect(conn);
		System.out.println(System.currentTimeMillis());
		return logins;
	}

	public static int testUpdateDataSource(String sql, Map<String, ?> param)
			throws Exception
	{
		System.out.println(System.currentTimeMillis());
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();

		int ret = conn.update(sql, param);
		SimpleDBAccess.getInstance().putConnect(conn);
		System.out.println(System.currentTimeMillis());
		return ret;
	}

	private static void printLogin(ArrayList<Login> logins)
	{
		for (int i = 0; i < logins.size(); ++i)
		{
			Login login = logins.get(i);
			System.out.println("username:" + login.getUsername() + " password:"
					+ login.getPassword());
		}
	}

	public static void main(String[] args) throws Exception
	{
		// 0.test load login table
		ArrayList<Login> logins = testLoadDataSource(Login.class,
				"select * from login", null);
		DatasourceManageTest.printLogin(logins);

		// 1.test load login by parameter
		HashMap<String, Object> param = new HashMap<String, Object>();
		param.put("username", "along");
		logins = testLoadDataSource(Login.class,
				"select * from login where username = @username@ ", param);
		DatasourceManageTest.printLogin(logins);

		// 2.test deletpe not exists data
		HashMap<String, Object> insert = new HashMap<String, Object>();
		insert.put("username", genRandomString(12));
		insert.put("password", genRandomString(24));
		int ret = testUpdateDataSource(
				"delete from login where username=@username@", insert);
		System.out.println("delete result " + ret);

		// 3.test insert data
		ret = testUpdateDataSource(
				"insert into login(username,password) values(@username@,@password@)",
				insert);
		System.out.println("delete result " + ret);

		// 4.query insert data
		logins = testLoadDataSource(Login.class,
				"select * from login where username = @username@ ", insert);
		DatasourceManageTest.printLogin(logins);

		// 5.test delete exists date
		ret = SimpleDBAccess.update(
				"delete from login where username=@username@", insert,null);
		System.out.println("delete result " + ret);

		// 6.query delete data
		logins = SimpleDBAccess.query(Login.class,
				"select * from login where username = @username@ ", insert);
		System.out.println("no data " + logins.size());
		DatasourceManageTest.printLogin(logins);
		
		//7.entity lookup
		Login login = new Login();
		login.setUsername("along");
		SimpleDBAccess.loadOne("select * from login where username = @username@ ", login, login,null);
		
		//8. entity queryOne
		login.setUsername("along");
		logins = SimpleDBAccess.query("select * from login where username = @username@ ", login);
		
		//9.entity update
		login.setUsername(genRandomString(12));
		login.setPassword(genRandomString(24));
		ret = SimpleDBAccess.save("insert into login(username,password) values(@username@,@password@)", login);
		System.out.println("save ret = " + ret);
	}

	private static String genRandomString(int length)
	{
		byte[] buffer = new byte[length];
		Random random = new Random();
		random.setSeed(System.currentTimeMillis());
		for (int i = 0; i < buffer.length; ++i)
		{
			buffer[i] = (byte) (random.nextInt(26) + 'A');
		}

		return new String(buffer);
	}
}
