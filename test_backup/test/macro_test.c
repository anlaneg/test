
#include <stdio.h>
#include <string.h>

#define test_print(msg, len) do { \
   int i; \
   int ulen = len; /*len可能引用i*/\
   for (i = 0; i < ulen; i++) \
   { \
   } \
   /*此时ulen可以为错*/\
 } while(0)

int main()
{
	char str[3][20] = {{"a"}, {"b"}, {"c"}};
	int i = 0;
	for (; i < 3; i++)
	{
		printf("i=%d, str_len = %d\n", i, strlen(str[i]));
		test_print(str[i], strlen(str[i]));
	}
	return 0;
}



