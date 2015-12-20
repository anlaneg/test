package cn.along.condb.connect;

import java.lang.reflect.InvocationTargetException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.apache.commons.beanutils.DynaBean;
import org.apache.commons.beanutils.PropertyUtils;
import org.apache.commons.beanutils.ResultSetDynaClass;

import cn.along.condb.exception.DBException;

interface IFillEntity
{
	void fill(ResultSet rs, SqlColumnEntity[] columns);
}

public class DBQuery
{
	private Connection conn;

	public DBQuery(Connection conn)
	{
		this.conn = conn;
	}

	private SqlColumnEntity[] create_sql_column_entity(ResultSetMetaData rsmd)
			throws SQLException
	{
		SqlColumnEntity[] entitys = new SqlColumnEntity[rsmd.getColumnCount()];
		for (int i = 0; i < entitys.length; ++i)
		{
			entitys[i] = new SqlColumnEntity(rsmd.getColumnName(i + 1));
		}

		return entitys;
	}

	private <T> ArrayList<T> resultSet2Object(ResultSet rs, Class<T> c,
			SqlColumnEntity[] columns, boolean onlyOne, T queryResult)
			throws SQLException, InstantiationException,
			IllegalAccessException, InvocationTargetException,
			NoSuchMethodException, DBException
	{
		ArrayList<T> result = null;
		Iterator<DynaBean> rows;

		rs.beforeFirst();

		rows = new ResultSetDynaClass(rs).iterator();
		if (onlyOne)
		{
			if (!rows.hasNext())
			{
				throw new DBException("No data found");
			}
			DynaBean row = rows.next();
			for (int i = 0; i < columns.length; ++i)
			{
				Object column = row.get(columns[i].getColumn_name());
				PropertyUtils.setProperty(queryResult,
						columns[i].getColumn_name(), column);
			}
		}
		else
		{
			result = new ArrayList<T>();
			while (rows.hasNext())
			{
				DynaBean row = rows.next();
				T o = c.newInstance();
				for (int i = 0; i < columns.length; ++i)
				{
					Object column = row.get(columns[i].getColumn_name());
					PropertyUtils.setProperty(o, columns[i].getColumn_name(),
							column);
				}

				result.add(o);
			}
		}
		return result;
	}

	private <T> List<T> query(Class<T> c, PreparedStatement ps,
			boolean onlyOne, T queryResult) throws DBException
	{
		ArrayList<T> result = null;
		ResultSet rs = null;
		try
		{
			try
			{
				rs = ps.executeQuery();
				result = this.resultSet2Object(rs, c,
						this.create_sql_column_entity(rs.getMetaData()),
						onlyOne, queryResult);

				return result;
			}
			finally
			{
				if (rs != null)
				{
					rs.close();
				}

				if (ps != null)
				{
					ps.close();
				}
			}
		}
		catch (Exception e)
		{
			throw new DBException("execute sql fail: " + e.getMessage());
		}
	}

	private <T> PreparedStatement createPreparedStatement(String sql,
			Map<String, Object> param, T src) throws DBException
	{
		try
		{
			PreparedStatement ps;
			Vector<String> paramName = new Vector<String>(8);
			sql = DBParameterParse.parseSqlParam(sql, paramName);
			System.err.println("execute sql: " + sql);
			ps = this.conn.prepareStatement(sql);

			// set parameter
			if (paramName != null && (param != null || src != null))
			{
				for (int i = 0; i < paramName.size(); ++i)
				{
					String key = paramName.get(i);
					Object value = null;
					
					//parameter first
					if (param != null && (value = param.get(key)) != null)
					{
						System.err.println("set paramater sql param[" + (i + 1)
								+ "]: (name:" + key + ",value:" + value + ")");
						ps.setObject(i + 1, param.get(paramName.get(i)));
						continue;
					}

					value = PropertyUtils.getProperty(src, key);
					System.err.println("set property sql param[" + (i + 1) + "]: (name:"
							+ key + ",value:" + value + ")");
					ps.setObject(i + 1, value);

				}
			}

			return ps;
		}
		catch (Exception e)
		{
			throw new DBException(e.getMessage());
		}
	}

	public <T> List<T> query(Class<T> c, String sql) throws DBException
	{
		PreparedStatement ps = this.createPreparedStatement(sql, null, null);
		return this.query(c, ps, false, null);
	}

	public <T> List<T> query(Class<T> c, String sql, Map<String, Object> param)
			throws DBException
	{
		PreparedStatement ps = this.createPreparedStatement(sql, param, null);
		return this.query(c, ps, false, null);
	}

	public <T> List<T> query(String sql, T param) throws DBException
	{

		PreparedStatement ps = this.createPreparedStatement(sql, null, param);
		@SuppressWarnings("unchecked")
		Class<T> c = (Class<T>) param.getClass();
		return this.query(c, ps, false, null);
	}

	public <T1, T2> void queryOne(String sql, T1 result, T2 src,
			Map<String, Object> param) throws DBException
	{
		PreparedStatement ps = this.createPreparedStatement(sql, param, src);
		@SuppressWarnings("unchecked")
		Class<T1> c = (Class<T1>) result.getClass();
		this.query(c, ps, true, result);
	}
}
