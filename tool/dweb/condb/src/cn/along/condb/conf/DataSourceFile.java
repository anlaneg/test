package cn.along.condb.conf;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import cn.along.condb.datasource.DataSource;
import cn.along.condb.inireader.IiniFileReader;
import cn.along.condb.inireader.IniFileReader;
import cn.along.condb.inireader.IniFileReaderException;
import cn.along.condb.inner.IDataSource;

public class DataSourceFile implements IiniFileReader
{
	private File cfg_file;
	private ArrayList<IDataSource> param = new ArrayList<IDataSource>();

	public DataSourceFile(File f)
	{
		this.cfg_file = f;
	}

	public IDataSource[] load() throws IOException, IniFileReaderException
	{

		IniFileReader reader = new IniFileReader(this.cfg_file, this,
				this.param);
		reader.parse();
		IDataSource[] ids = new IDataSource[this.param.size()];
		return this.param.toArray(ids);
	}

	@Override
	public Object segment_entry(String segment_name, Object o)
			throws IniFileReaderException
	{
		IDataSource ids = new DataSource();
		ids.setDataSourceName(segment_name);
		return ids;
	}

	@Override
	public void segment_leave(String segment_name, Object segment_object,
			Object o) throws IniFileReaderException
	{
		this.param.add((IDataSource) segment_object);
	}

	@Override
	public void segment_member_set(Object segment_object, String key,
			String value) throws IniFileReaderException
	{
		// setAxx
		String method_name = "set" + Character.toUpperCase(key.charAt(0))
				+ key.substring(1);
		try
		{
			Method method = segment_object.getClass().getMethod(method_name,
					String.class);
			method.invoke(segment_object, value);
		}
		catch (Exception e)
		{
			e.printStackTrace();
			throw new IniFileReaderException("We try to invoke method '"
					+ method_name + "' fail");
		}
	}
}
