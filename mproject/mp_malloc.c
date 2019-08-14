
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <malloc.h>

void * malloc_align_page(size_t size)
{
    void *buf = NULL;

    if (size == 0) {
        return NULL;
    }

    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf err");
        return NULL;
    }

    buf = memalign(pagesize, size);
    if (buf == NULL) {
        perror("memalign failed!");
        return NULL;
    }

    return buf;
}


