#include <stdio.h>

#define SPEED_CAL_LOG(fmt,...)  fprintf(stderr,fmt,##__VA_ARGS__)
#define SPEED_CAL_ERR(fmt,...)  fprintf(stderr,fmt,##__VA_ARGS__)
