//#变量必须先定义后使用
//#所有发生异常的函数,必须说明会扔出异常
//#所有调用异常函数处,必须抛出或者解决异常
//#所有事件函数只能保证在被说明函数之前或者之后调用,除此之外不能调用
//#所有事件处理函数均有权利拒绝某个函数的调用.
//#对某一类做出修改后,从修改点开始将会影响所有之后对此类的使用.
packet cn.along.lang.example;

import cn.along.lang.example.B;

//#展示类修改语法(这种语法用起来太复杂了?)
modify class B
{
	public B()
	{
		//此操作将overrid 构造函数
	}

	//此操作将修改c_function函数的实现
	private c_function()
	{
	}
}

modify function {
 public B();
 public C();
}


//继续语法
class A < B
{
	public A() {
		super("along");
		s = new Array();
	}

	private var s;
	private	var f;
	private var t;

	pulbic sayHello()
	{
		system.out.println("hello world");
	}

	public sayHello(exe)throws testException;
	{
		exe.execute();
		exe();
	}

	//事件有哪几种
	//function entry,leave,on_exception,on_return,
        //function onxxx_modify_before,onxxx_modify_after
        //
	public event xx_before()
	{
	}

	public event xx_edit()
	{
	}

	public event xx_edit()
	{
	}

	public event xx_on_entern()
	{
	}

	public event xx_on_leveaf()
	{
	}
}

//动态的添加成员函数
//成员属性
A.functions.add(function);
A.functions.sub(xxxx);
A.members.add(xxx);

//1.代码即为字符串,字符串即为代码
//2.一开始我只写了一个大纲,后来我把这些大纲变成了一本书
//3.
