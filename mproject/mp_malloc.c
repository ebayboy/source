
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include "mp_malloc.h"

void * malloc_align_page(size_t memsize)
{
    void *start = NULL;

    if (memsize == 0) {
        return NULL;
    }

    long pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf err");
        return NULL;
    }

    size_t datasize = memsize + pagesize * 2;
    void *origin_start = malloc(datasize);
    if(origin_start == NULL) {
        perror("malloc");
        return NULL;
    }
    memset(origin_start, 0, datasize);

    long mask = pagesize - 1;
    start = (void *)((long)(origin_start + pagesize) & ~mask);

    return start;
}


