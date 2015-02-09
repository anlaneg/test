#include <stdio.h> // for printf() 
#include <stdlib.h> // for exit() 
#if X86_64
#define RUNTIME_LINKER "/lib64/ld-linux-x86-64.so.2"
#else
#define RUNTIME_LINKER "/lib/ld-linux.so.2"
#endif
const char __invoke_dynamic_linker__[] __attribute__ ((section (".interp"))) =  RUNTIME_LINKER ; 
void fun() 
{ 
        printf("This is fun.\n"); 
        exit(0); 
} 
