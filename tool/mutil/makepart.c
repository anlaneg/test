#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct my_key
{
    double value;
    double per;
}my_key_t;

#define INIT_MY_KEY(v) {.value=v,.per=0.010}
my_key_t key[]={
    INIT_MY_KEY(0.004450),
    INIT_MY_KEY(0.00450),
    INIT_MY_KEY(0.004510),
    INIT_MY_KEY(0.0050),
    INIT_MY_KEY(0.00510),
    INIT_MY_KEY(0.00540),
    INIT_MY_KEY(0.00550),
};

void try_result(int total,double p)
{
    int i = 0 ;
    for(i = 0 ; i < sizeof(key)/sizeof(my_key_t); ++i)
    {
        double value= key[i].value/(p/365);
        double per= key[i].per/(p/365);
        printf("%.6f    |   %.5f    |   %.5f    \n",key[i].value,value,per);
    }
}


int main(int argc,char**argv)
{
    int total=0;
    double p;

    int c=0;
    while(1)
    {
        c=getopt(argc,argv,"t:p:"); 
        if(c==-1)
        {
            break;
        }

        switch(c)
        {
            case 't':
                total=atoi(optarg);
                break;
            case 'p':
                p=atof(optarg);
                break;
            default:
                exit(0);
        }
    }

    printf("total=%d,p=%.5f\n",total,p);
    if(total > 0 && p > 0)
    {
        try_result(total,p);
    }
}
