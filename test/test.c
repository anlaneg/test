#include <stdio.h>

int p()
{
  printf("hello world\n");
  return 0;
}
int main(int argc ,char**argv)
{
	int k = 2000;
	int i ;
	for(i = 0 ; i < k; ++i)
	{
		p();
	}
	return 0;
}
       
