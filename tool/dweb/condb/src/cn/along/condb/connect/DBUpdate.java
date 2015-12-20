package cn.along.condb.connect;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.Map;
import java.util.Vector;

import org.apache.commons.beanutils.PropertyUtils;

import cn.along.condb.exception.DBException;

public class DBUpdate
{
	private Connection conn;

	public DBUpdate(Connection conn)
	{
		this.conn = conn;
	}

	private <T> int update(String sql, Vector<String> paramName, T src,
			Map<String, Object> param) throws DBException
	{
		int result = 0;
		System.err.println("execute sql: " + sql);
		try
		{
			PreparedStatement ps;

			ps = this.conn.prepareStatement(sql);

			// set parameter
			if (paramName != null && (param != null || src != null))
			{
				for (int i = 0; i < paramName.size(); ++i)
				{
					String key = paramName.get(i);
					Object value = null;

					// parameter first
					if (param != null && (value = param.get(key)) != null)
					{
						System.err.println("set sql param[" + (i + 1)
								+ "]: (name:" + key + ",value:" + value + ")");
						ps.setObject(i + 1, value);
						continue;
					}

					value = PropertyUtils.getProperty(src, key);
					System.err.println("set sql param[" + (i + 1) + "]: (name:"
							+ key + ",value:" + value + ")");
					ps.setObject(i + 1, value);
				}
			}
			result = ps.executeUpdate();
			ps.close();

			return result;
		}
		catch (Exception e)
		{
			throw new DBException("execute sql: " + sql + " error: "
					+ e.getMessage());
		}

	}

	public <T> int update(String sql, T src, Map<String, Object> param)
			throws DBException
	{
		Vector<String> paramName = new Vector<String>(8);
		sql = DBParameterParse.parseSqlParam(sql, paramName);
		return this.update(sql, paramName, src, param);
	}
	/*
	 * 暂不提 public int update(String sql) throws DBException { return
	 * this.update(sql, null, null); }
	 * 
	 * public <T> int update(String sql, T in) throws DBException { //
	 * 这个方法实现的比较简单，暂如此处理 Vector<String> paramName = new Vector<String>(8); sql =
	 * DBParameterParse.parseSqlParam(sql, paramName); HashMap<String, Object>
	 * param = new HashMap<String, Object>(); try { for (int i = 0; i <
	 * paramName.size(); ++i) { param.put(paramName.get(i),
	 * PropertyUtils.getProperty(in, paramName.get(i))); } }
	 * catch(InvocationTargetException e) { e.printStackTrace(); throw new
	 * DBException(e.getMessage()); } catch (NoSuchMethodException e) {
	 * e.printStackTrace(); throw new DBException(e.getMessage()); } catch
	 * (IllegalAccessException e) { e.printStackTrace(); throw new
	 * DBException(e.getMessage()); }
	 * 
	 * return this.update(sql, paramName, param); }
	 */
}
