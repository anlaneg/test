import java.util.HashMap;

import cn.along.condb.api.SimpleDBAccess;
import cn.along.condb.exception.DBException;

public class TestDemo
{
	private Logins $0;

	public TestDemo(Logins $0)
	{
		this.$0 = $0;
	}

	private void sql_select_select() throws DBException
	{
		String sql = "select * from login where username = @username@ and 1=@dummy@";
		HashMap<String, Object> param = new HashMap<String, Object>();
		param.put("dummy", "1");
		SimpleDBAccess.loadOne(sql, this.$0, this.$0, param);
	}

	private void sql_insert_login_insert() throws DBException
	{
		String sql = "insert login(username,password) values(@username@,@password@)";
		HashMap<String, Object> param = new HashMap<String, Object>();
		param.put("password", "default-password");
		SimpleDBAccess.update(sql, this.$0, param);
	}

	public void filler() throws DBException
	{
		this.sql_select_select();
		this.sql_insert_login_insert();
	}
}