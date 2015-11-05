package cn.along.condb.connect;

import cn.along.common.util.StringUtil;

class SqlColumnEntity
{
	private String column_name;
	private String set_name;
	private String get_name;

	public SqlColumnEntity(String column_name)
	{
		this.column_name = column_name;
		this.set_name = "set" + StringUtil.initialUpper(column_name);
		this.get_name = "get" + StringUtil.initialUpper(column_name);
	}

	public String getColumn_name()
	{
		return column_name;
	}

	public void setColumn_name(String column_name)
	{
		this.column_name = column_name;
	}

	public String getSet_name()
	{
		return set_name;
	}

	public void setSet_name(String set_name)
	{
		this.set_name = set_name;
	}

	public String getGet_name()
	{
		return get_name;
	}

	public void setGet_name(String get_name)
	{
		this.get_name = get_name;
	}
}
