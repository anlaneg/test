import cn.along.xrt.XrtDefaultValue;

public class Logins
{
	// 
	private String username;

	// 
	private String password;

	// 
	private int dummy;

	// 
	private B[][] dummy2;

	public Logins()
	{
		//set member default value
		this.username=XrtDefaultValue.getStringValue("");
		this.password=XrtDefaultValue.getStringValue("");
		this.dummy=XrtDefaultValue.getIntValue("");
		this.dummy2=new B[][] {
{
new B(),
new B()},{
new B(),
new B()}};

	}

	//set username:
	public void setUsername(String username)
	{
		this.username=username;
	}

	//get username:
	public String getUsername()
	{
		return this.username;
	}

	//set password:
	public void setPassword(String password)
	{
		this.password=password;
	}

	//get password:
	public String getPassword()
	{
		return this.password;
	}

	//set dummy:
	public void setDummy(int dummy)
	{
		this.dummy=dummy;
	}

	//get dummy:
	public int getDummy()
	{
		return this.dummy;
	}

	//set dummy2:
	public void setDummy2(B[][] dummy2)
	{
		this.dummy2=dummy2;
	}

	//get dummy2:
	public B[][] getDummy2()
	{
		return this.dummy2;
	}

}
