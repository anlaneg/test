package cn.along.condb.datasource;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;

import cn.along.condb.conf.DataSourceFile;
import cn.along.condb.inireader.IniFileReaderException;
import cn.along.condb.inner.IDataSource;

public class DataSourceManager
{
	private String[] search_path;
	private HashMap<String, IDataSource> datasources;

	public DataSourceManager()
	{
		this.datasources = new HashMap<String, IDataSource>();
	}

	private File findDatasourceFile(String file, String[] search_path)
	{
		for (int i = 0; i < search_path.length; ++i)
		{
			File f;
			if (search_path[i] != null)
			{
				f = new File(search_path[i], file);
			}
			else
			{
				f = new File(file);
			}

			if (f.exists() && f.canRead() && f.isFile())
			{
				return f;
			}
			else
			{/*
			 * System.err.println("find file:" + f.getAbsolutePath() +
			 * " exists:" + f.exists() + " read:" + f.canRead() + " is-file:" +
			 * f.isFile());
			 */
			}
		}

		return null;
	}

	private void appendDataSource(IDataSource[] ds)
	{
		for (int i = 0; i < ds.length; ++i)
		{
			String name = ds[i].getDataSourceName();
			if (!this.datasources.containsKey(name))
			{
				System.out.println("add " + name);
				this.datasources.put(name, ds[i]);
			}
			else
			{
				throw new IllegalArgumentException("datasource '" + name
						+ "' already exsits");
			}
		}

	}

	public String getDataSourcePath()
	{
		StringBuilder message = new StringBuilder();
		for (int i = 0; i < this.search_path.length; ++i)
		{
			message.append(this.search_path[i]);
			message.append(" ,");
		}
		return message.toString();
	}

	public void SetDataSourcePath(String search_path)
	{
		this.search_path = search_path.split(";");
	}

	public void loadDatabaseSource(String file) throws IOException,
			IniFileReaderException
	{
		File f = this.findDatasourceFile(file, this.search_path);

		if (f == null)
		{
			throw new FileNotFoundException("We can't find the file '" + file
					+ "',search paths {" + this.getDataSourcePath() + "}");
		}

		DataSourceFile dsf = new DataSourceFile(f);
		this.appendDataSource(dsf.load());

	}

	public IDataSource findDataSource(String name)
	{
		return this.datasources.get(name);
	}
}
