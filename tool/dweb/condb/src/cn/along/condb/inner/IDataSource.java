package cn.along.condb.inner;

public interface IDataSource
{
	public String getDataSourceName();

	public void setDataSourceName(String name);

	public String getDriverClass();

	public String getConnectString();

	public String getUserName();

	public String getPassword();
	
	public int getPoolSize();
}
