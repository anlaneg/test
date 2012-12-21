#include <stdint.h>

extern int32_t add_fun_before(int32_t a,int32_t b);
extern int32_t c;

int32_t add_fun(int32_t a,int32_t b)
{
    add_fun_before(a,b);
    return a + b;
}


//a = a + b
int32_t add_to_fun(int32_t* a ,int32_t b)
{
	*a = *a + b;
	return *a;
}

//if (c >0 ) a + b  
//else if (c < 0 ) a -b 
//else c==0   a=b
int32_t add_by_sign_fun(int32_t*a ,int32_t b)
{
	if( c > 0)
	{
	   return *a + b;
	}
	else if( c < 0)
	{
	   return *a - b;
	}
	else
	{
	   *a = b;
	   return *a;
        }
}


