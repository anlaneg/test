package cn.along.condb.inner;

import java.sql.SQLException;

import cn.along.condb.exception.DBException;

public interface IDBPool
{
	public IDBConnect getConnect() throws DBException;

	public void putConnect(IDBConnect ic) throws DBException;

	public void destroy() throws SQLException;
}
