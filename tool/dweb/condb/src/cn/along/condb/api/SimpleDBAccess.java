package cn.along.condb.api;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Map;

import cn.along.condb.constant.CondbConstant;
import cn.along.condb.datasource.DataSourceManager;
import cn.along.condb.exception.DBException;
import cn.along.condb.inireader.IniFileReaderException;
import cn.along.condb.inner.IDBConnect;
import cn.along.condb.inner.IDBPool;
import cn.along.condb.inner.IDataSource;
import cn.along.condb.pool.DBPool;

public class SimpleDBAccess
{
	private static SimpleDBAccess database;
	private IDBPool idp;

	private SimpleDBAccess() throws IOException, IniFileReaderException
	{
		DataSourceManager dsm;
		dsm = new DataSourceManager();
		dsm.SetDataSourcePath(CondbConstant.DEFAULT_DATASOURCE_SEARCH_PATH);
		dsm.loadDatabaseSource(CondbConstant.DEFAULT_DATASOURCE_FILE_NAME);
		IDataSource ids = dsm
				.findDataSource(CondbConstant.DEFAULT_DATASOURCE_NAME);
		if (ids == null)
		{
			throw new IniFileReaderException("no find datasource "
					+ CondbConstant.DEFAULT_DATASOURCE_NAME);
		}
		this.idp = new DBPool(ids);
	}

	public static SimpleDBAccess getInstance()
	{
		if (SimpleDBAccess.database != null)
		{
			return SimpleDBAccess.database;
		}

		try
		{
			SimpleDBAccess.database = new SimpleDBAccess();
			return SimpleDBAccess.database;
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (IniFileReaderException e)
		{
			e.printStackTrace();
		}
		return null;
	}

	public IDBConnect getConnect() throws DBException
	{
		return this.idp.getConnect();
	}

	public void putConnect(IDBConnect conn) throws DBException
	{
		this.idp.putConnect(conn);
	}

	public void destory() throws SQLException
	{
		this.idp.destroy();
	}

	public static <T> ArrayList<T> query(Class<T> cl, String sql,
			Map<String, String> param) throws DBException
	{
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();

		ArrayList<T> result = (ArrayList<T>) conn.query(cl, sql, param);
		SimpleDBAccess.getInstance().putConnect(conn);
		return result;
	}

	public static int update(String sql, Map<String, String> param)
			throws DBException
	{
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();

		int ret = conn.update(sql, param);
		SimpleDBAccess.getInstance().putConnect(conn);
		return ret;
	}

	public static <T> ArrayList<T> query(String sql, T param)
			throws DBException
	{
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();
		ArrayList<T> result = (ArrayList<T>) conn.query(sql, param);
		SimpleDBAccess.getInstance().putConnect(conn);
		return result;
	}

	public static <T1, T2> void loadOne(String sql, T1 result, T2 param)
			throws DBException
	{
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();
		conn.queryOne(sql, result, param);
		SimpleDBAccess.getInstance().putConnect(conn);
	}

	public static <T> int save(String sql, T object) throws DBException
	{
		IDBConnect conn = SimpleDBAccess.getInstance().getConnect();
		int ret = conn.update(sql, object);
		SimpleDBAccess.getInstance().putConnect(conn);
		return ret;
	}

}
