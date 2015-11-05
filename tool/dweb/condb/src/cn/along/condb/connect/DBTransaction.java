package cn.along.condb.connect;

import java.sql.Connection;
import java.sql.SQLException;

import cn.along.condb.exception.DBException;

public class DBTransaction
{
	private Connection conn;

	public DBTransaction(Connection conn)
	{
		this.conn = conn;
	}

	public void transactionBegin() throws DBException
	{
		try
		{
			this.conn.setAutoCommit(false);
		}
		catch (SQLException e)
		{
			throw new DBException(e.getMessage());
		}
	}

	public void transactionRollback() throws DBException
	{
		try
		{
			this.conn.rollback();
		}
		catch (SQLException e)
		{
			throw new DBException(e.getMessage());
		}

	}

	public void transactionCommit() throws DBException
	{
		try
		{
			this.conn.commit();
		}
		catch (SQLException e)
		{
			throw new DBException(e.getMessage());
		}
	}

}
