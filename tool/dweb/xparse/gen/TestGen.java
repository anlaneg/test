import cn.along.condb.exception.DBException;

public class TestGen
{
	public static void main(String[] args) throws DBException
	{
		Logins input = new Logins();
		input.setUsername( "along");
		TestDemo demon = new TestDemo(input);
		demon.filler();
		System.out.println(input + " username:" + input.getUsername() + " password:" + input.getPassword());
	}
}
