package cn.along.condb.inireader;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class IniFileReader
{
	private File ini_file;
	private IiniFileReader custom;
	private Object param;

	private String last_segment;
	private Object last_segment_object;

	public IniFileReader(File f, IiniFileReader custom, Object param)
	{
		this.ini_file = f;
		this.custom = custom;
		this.param = param;
		this.last_segment = null;
		this.last_segment_object = null;
	}

	public void parse() throws IOException, IniFileReaderException
	{
		BufferedReader reader = new BufferedReader(
				new FileReader(this.ini_file));

		String line = null;
		try
		{
			for (line = reader.readLine(); line != null; line = reader
					.readLine())
			{
				line = line.trim();

				if (line.startsWith("["))
				{
					if (!line.endsWith("]"))
					{
						throw new IniFileReaderException("line '" + line
								+ "' not start with '[',and end with ']'");
					}

					if (this.last_segment != null)
					{
						this.custom.segment_leave(this.last_segment,
								this.last_segment_object, this.param);
					}

					this.update_segment(line);
				}
				else
				{
					int idx = 0;
					if (line.length() == 0)
					{
						// 如果是空行，则不进行处理，继续读取下一行。
						continue;
					}

					if (line.startsWith("#"))
					{
						// 如果是注释行，则不进行处理
						continue;
					}

					if ((idx = line.indexOf('=')) == -1)
					{
						throw new IniFileReaderException("line '" + line
								+ "' no contains '='");
					}

					String key = line.substring(0, idx);
					String value = line.substring(idx + 1);
					this.custom.segment_member_set(this.last_segment_object,
							key.trim(), value.trim());
				}
			}
		}
		finally
		{
			if (line == null)
			{
				this.custom.segment_leave(this.last_segment,
						this.last_segment_object, this.param);
			}
			reader.close();
		}
	}

	private void update_segment(String line) throws IniFileReaderException
	{
		String name = line.substring(1, line.length() - 1).trim();// length
																	// -1
																	// and -
																	// "]"

		Object obj = this.custom.segment_entry(name, this.param);
		this.last_segment = name;
		this.last_segment_object = obj;

	}
}
