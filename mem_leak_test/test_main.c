
/*test_main.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_leak_test.h"


#define my_malloc(s)    test_malloc(s)
#define my_free(p)      test_free(p)
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
        arr[i] = my_malloc(sizeof(int));
        if(!arr[i])
        {
            err_exit("my_malloc failed!");
        }
    }

    /*there is lack of 2 free() deliberately*/
    for(i = 0; i < ARR_SIZE - 2; ++i)
    {
        my_free(arr[i]);
    }       
}

int main(int argc, const char * const argv[])
{
    /*init memery leak check module*/
    if(mem_leak_test_init() != 0)
    {
        return -1;
    }

    /*simulate a project which may have a memory leak*/
    test();

    /*show memery leak check result*/
    mem_leak_test_result();

    /*destroy memery leak check module*/
    mem_leak_test_destroy();

    return 0;
}


