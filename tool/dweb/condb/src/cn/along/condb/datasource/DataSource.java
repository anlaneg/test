package cn.along.condb.datasource;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

import cn.along.condb.inner.IDataSource;

public class DataSource implements IDataSource
{
	private HashMap<String, String> conf;

	public DataSource()
	{
		super();
		this.conf = new HashMap<String, String>();
	}

	private String getHashMapValue(String name)
	{
		return this.conf.get(name);
	}

	private String getHashMapValue(String name, String default_value)
	{
		String value = this.getHashMapValue(name);
		if (value == null)
		{
			return default_value;
		}
		return value;
	}

	private void setHashMapValue(String name, String value)
	{
		this.conf.put(name, value);
	}

	@Override
	public String getDataSourceName()
	{
		return this.getHashMapValue("dataSourceName");
	}

	@Override
	public void setDataSourceName(String dataSourceName)
	{
		this.setHashMapValue("dataSourceName", dataSourceName);
	}

	public String getUserName()
	{
		return this.getHashMapValue("userName", "");
	}

	public void setUserName(String userName)
	{
		this.setHashMapValue("userName", userName);
	}

	public String getPassword()
	{
		return this.getHashMapValue("password", "");
	}

	public void setPassword(String password)
	{
		this.setHashMapValue("password", password);
	}

	public String getDatabase()
	{
		return this.getHashMapValue("database", "");
	}

	public void setDatabase(String database)
	{
		this.setHashMapValue("database", database);
	}

	public String getDriverClass()
	{
		return this.getHashMapValue("driverClass", "");
	}

	public void setDriverClass(String driver_class)
	{
		this.setHashMapValue("driverClass", driver_class);
	}

	public String getHost()
	{
		return this.getHashMapValue("host", "");
	}

	public void setHost(String host)
	{
		this.setHashMapValue("host", host);
	}

	public String getPort()
	{
		return this.getHashMapValue("port", "");
	}

	public void setPort(String port)
	{
		this.setHashMapValue("port", port);
	}

	public String getConnectString()
	{
		String conn_str = this.getHashMapValue("connectString");
		if (conn_str == null)
		{
			conn_str = "jdbc:mysql://@host:@port/@database";
		}

		Set<Entry<String, String>> set = this.conf.entrySet();
		Iterator<Entry<String, String>> iterator = set.iterator();
		while (iterator.hasNext())
		{
			Entry<String, String> e = iterator.next();
			String key = e.getKey();
			String value = e.getValue();

			conn_str = conn_str.replaceAll("@" + key, value);
		}

		return conn_str;
	}

	public void setConnectString(String connect_string)
	{
		this.setHashMapValue("connectString", connect_string);
	}

	public int getPoolSize()
	{
		String pool_size = this.getHashMapValue("poolSize", "1");
		return Integer.parseInt(pool_size);
	}

	public void setPoolSize(String pool_size)
	{
		int size = Integer.parseInt(pool_size);
		this.setHashMapValue("poolSize", new Integer(size).toString());
	}

}
