
/*test_main.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "safe_malloc.h"

#define ARR_SIZE 10

void err_exit(const char * info)
{
    fprintf(stderr, "%s\n", info);
    exit(1);
}

void test(void)
{
    void * arr[ARR_SIZE];
    int i;

    for(i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = NULL;
    }

    for(i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = SAFE_MALLOC(sizeof(int));
        if(!arr[i])
        {
            err_exit("SAFE_MALLOC failed!");
        }
    }

    /*there is lack of 2 free() deliberately*/
    for(i = 0; i < ARR_SIZE - 2; ++i)
    {
        SAFE_FREE(arr[i]);
    }       
}

int main(int argc, const char * const argv[])
{
    /*init memery leak check module*/
    if(safe_malloc_init() != 0)
    {
        return -1;
    }

    /*simulate a project which may have a memory leak*/
    test();

    /*show memery leak check result*/
    safe_malloc_result();

    /*destroy memery leak check module*/
    safe_malloc_destroy();

    return 0;
}


