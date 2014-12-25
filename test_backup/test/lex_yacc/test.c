#include <unistd.h>
#include <stdio.h>
#include <sys/param.h>
void vty_save_cwd ()
{
	char *cwd;

	cwd = getcwd (NULL, MAXPATHLEN);
	printf("%s\n",cwd);
}

int main(int argc,char**argv)
{
	vty_save_cwd();
}


