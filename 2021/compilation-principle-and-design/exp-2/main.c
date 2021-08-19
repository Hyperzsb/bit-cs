#ifdef USE_LIBDEMO
#include "demo.h"
#else
#include <stdio.h>
#endif

int main()
{

#ifdef USE_LIBDEMO
    HelloWorld();
#else
    printf("Hello World! (Libdemo not included)\n");
#endif

    return 0;
}