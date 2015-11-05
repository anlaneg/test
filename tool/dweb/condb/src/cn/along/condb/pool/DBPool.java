package cn.along.condb.pool;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import cn.along.condb.connect.DBConnect;
import cn.along.condb.exception.DBException;
import cn.along.condb.inner.IDBConnect;
import cn.along.condb.inner.IDBPool;
import cn.along.condb.inner.IDataSource;

public class DBPool implements IDBPool
{
	private IDataSource ids;

	public DBPool(IDataSource ids)
	{
		this.ids = ids;
	}

	private IDBConnect newConnect() throws DBException
	{
		try
		{
			Class.forName(this.ids.getDriverClass());
			Connection con = DriverManager.getConnection(
					this.ids.getConnectString(), this.ids.getUserName(),
					this.ids.getPassword());
			IDBConnect idc = new DBConnect(con);
			return idc;
		}
		catch (ClassNotFoundException e)
		{
			e.printStackTrace();
			throw new DBException("database driver load fail!\n");

		}
		catch (SQLException e)
		{
			e.printStackTrace();
			throw new DBException("database open connect fail!\n");
		}
	}

	@Override
	public IDBConnect getConnect() throws DBException
	{
		return this.newConnect();
	}
	
	private void deleteConnect(IDBConnect ic) throws DBException
	{
		ic.close();
	}

	@Override
	public void putConnect(IDBConnect ic) throws DBException
	{
		this.deleteConnect(ic);
	}

	

	@Override
	public void destroy() throws SQLException
	{
		System.out.println("nothing to do");
	}
}
