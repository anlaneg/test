package cn.along.condb.inireader;

public interface IiniFileReader
{
	public Object segment_entry(String segment_name, Object param)
			throws IniFileReaderException;

	public void segment_leave(String segment_name, Object segment_object,
			Object param) throws IniFileReaderException;

	public void segment_member_set(Object segment_object, String key,
			String value) throws IniFileReaderException;
}
