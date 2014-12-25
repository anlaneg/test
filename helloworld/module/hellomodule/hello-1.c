#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

int add(int a,int b);
//加入参数
static char* mystring="along";

MODULE_LICENSE("GPL");
module_param(mystring,charp,0000);
MODULE_PARM_DESC(mystring,"my name");
static int __init initmodule(void)
{
	printk(KERN_INFO "hello world 1.\n");
	//返回非0表示初始化失败
	printk(KERN_INFO "my name is %s\n",mystring);
	return 0;
}

static void __exit cleanupmodule(void)
{
	printk(KERN_INFO "3 + 4 = %d\n",add(3,4));
	printk(KERN_INFO "goodbye world 1.\n");
	
}

module_init(initmodule);
module_exit(cleanupmodule);
