public class Logins
{
	// 
	private String username;

	// 
	private String password;

	public Logins()
	{
		//set member default value
		//this.username=new XRuntimeDefaultValue(new int[]{1}, new String[]{}).getString();
		//this.password=new XRuntimeDefaultValue(new int[]{1}, new String[]{}).getString();
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

}