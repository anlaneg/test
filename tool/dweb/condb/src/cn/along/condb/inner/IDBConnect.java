package cn.along.condb.inner;

import java.sql.Connection;
import java.util.List;
import java.util.Map;

import cn.along.condb.exception.DBException;

public interface IDBConnect
{

	public <T> List<T> query(Class<T> c, String sql, Map<String, String> param)
			throws DBException;

	public <T> List<T> query(String sql, T param) throws DBException;
	
	public <T> List<T> query(Class<T> c, String sql) throws DBException;

	public <T1, T2> void queryOne(String sql, T1 result, T2 param)
			throws DBException;
	

	public int update(String sql, Map<String, String> param) throws DBException;

	public <T> int update(String sql, T in) throws DBException;

	public int update(String sql) throws DBException;

	public void transactionBegin() throws DBException;

	public void transactionRollback() throws DBException;

	public void transactionCommit() throws DBException;

	public Connection getConnection();

	public void close() throws DBException;
}
