package cn.along.condb.connect;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;
import java.util.Map;

import cn.along.condb.exception.DBException;
import cn.along.condb.inner.IDBConnect;

public class DBConnect implements IDBConnect
{
	private Connection conn;

	public DBConnect(Connection con)
	{
		this.conn = con;
	}

	@Override
	public Connection getConnection()
	{
		return this.conn;
	}

	@Override
	public void close() throws DBException
	{
		try
		{
			this.conn.close();
		}
		catch (SQLException e)
		{
			e.printStackTrace();
			throw new DBException("close connect fail!\n");
		}

	}

	@Override
	public <T> List<T> query(Class<T> c, String sql, Map<String, Object> param) throws DBException
	{
		return new DBQuery(this.conn).query(c, sql, param);
	}

	@Override
	public <T> List<T> query(Class<T> c, String sql) throws DBException
	{
		return new DBQuery(this.conn).query(c, sql);
	}

	@Override
	public <T> int update(String sql,T src, Map<String, Object> param) throws DBException
	{
		return new DBUpdate(this.conn).update(sql, src,param);
	}

	@Override
	public int update(String sql) throws DBException
	{
		return new DBUpdate(this.conn).update(sql,null,null);
	}

	@Override
	public void transactionBegin() throws DBException
	{
		new DBTransaction(this.conn).transactionBegin();
	}

	@Override
	public void transactionRollback() throws DBException
	{
		new DBTransaction(this.conn).transactionRollback();
	}

	@Override
	public void transactionCommit() throws DBException
	{
		new DBTransaction(this.conn).transactionCommit();
	}

	@Override
	public <T> int update(String sql, T in) throws DBException
	{
		return new DBUpdate(this.conn).update(sql,in,null);
	}

	@Override
	public <T> List<T> query(String sql, T param) throws DBException
	{
		return new DBQuery(this.conn).query(sql,param);
	}

	@Override
	public <T1, T2> void queryOne(String sql, T1 result, T2 src,Map<String,Object> param)
			throws DBException
	{
		new DBQuery(this.conn).queryOne(sql,result,src,param);
	}

}
