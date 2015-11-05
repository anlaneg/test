#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double result366(double m,double p)
{
    return m*(p/366);
}

double result365(double m,double p)
{
    return m*(p/365);
}


int try_result(int start,int end,double p)
{
    int i = start;
    for(; i <=end ; ++i)
    {
        double answer365 = result365(i,p);
        double answer366 = result366(i,p);
        printf("%6d    %.4f  |  %.2f    (%.5f)  |  %.2f    (%.5f)\n",i,p,answer365,answer365,answer366,answer366);
    }
}

int main(int argc,char**argv)
{
    int c;
    int digit_optind = 0;

    int start = 0;
    int end = 0;
    double p = 0;
    while (1) 
    {
        c = getopt(argc, argv, "s:e:p:");
        switch (c) 
        {
            case 's':
                start=atoi(optarg);
                break;
            case 'e':
                end=atoi(optarg);
                break;
            case 'p':
                p = atof(optarg); 
                break;
            case -1:
                break;
            default:
                exit(0);
                break;
        }
        if(c== -1)
        {
            break;
        }
    }
    
    printf("start=%d,end=%d,p=%.5f\n",start,end,p);
    if(start > 0 && end > 0 && start < end && p > 0)
    {
        try_result(start,end,p);
    }
    return 0;
}
