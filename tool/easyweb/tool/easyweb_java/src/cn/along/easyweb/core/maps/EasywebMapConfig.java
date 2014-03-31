package cn.along.easyweb.core.maps;

public class EasywebMapConfig
{
	private String packageName;
	private EasywebConfig[] maps;

	public String getPackageName()
	{
		return packageName;
	}

	public void setPackageName(String packageName)
	{
		this.packageName = packageName;
	}

	public EasywebConfig[] getMaps()
	{
		return maps;
	}

	public void setMaps(EasywebConfig[] maps)
	{
		this.maps = maps;
	}
}
