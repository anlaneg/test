#include <assert.h>
#include <stdio.h>

#include "al_add.c"

//我们需要提供一个区段用于实现打桩
//打桩区
int32_t add_fun_before(int32_t a , int32_t b)
{
	//在桩函数中我们需要能够检测到输入输出的值
        printf("a=%u,b=%u\n",a,b);	
	return 0;
}

//
int32_t c;
void init_add_by_sign(int32_t set)
{
	c = set;
}
//打桩区结束

int main(int argc,char**argv)
{
   //我们需要生成测试入口函数

   //我们需要解析输出函数及其返回值

   assert(add_fun(2,3) == 5);
   assert(add_fun(2,4) == 6);
   assert(add_fun(3,4) == 7);
   //assert(add_fun(3,3) == 8);

   //我们需要能够检测函数返回及参数返回
   int32_t a = 3;
   assert(add_to_fun(&a,4) == 7);
   assert(a == 7);


   //我们需要能够在执行在每个测试用例是,执行一段初始化函数
   init_add_by_sign(0);
   add_by_sign_fun(&a,19);
   assert(a == 19);
   //我们需要能够在执行每个测试用例是,执行一段稍毁函数
   

   return 0;
}
