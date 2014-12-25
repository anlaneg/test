
#define MAX_SIZE 32
struct type
{
	int test[MAX_SIZE];
};

/** 测试数组常量越界*/
int main(int argc,char**argv)
{
	struct type test_type;
	//越界
	test_type.test[MAX_SIZE] = 0;
	return 0;
}
	
	
