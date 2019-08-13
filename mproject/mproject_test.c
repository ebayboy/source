
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

/* TODO:
 * add sig process, when sigment print address contect 
 * */

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

int main()
{
    /* malloc */
    size_t plen = 4097;
    char *p = (char *)malloc_align_page(plen);
    if (p == NULL) {
        return -1;
    }

    /* write */
    strcpy(p, "hello world");
    p[4] = '1';

    /* lock */
    if (mprotect(p, (size_t)(plen), PROT_READ) == -1) {
        perror("Error: mportect %s:%d", __func__, __LINE__);
        return -1;
    }

    printf("before p:[%s]\n", p);

    /* error */
    p[4] = '2';
    printf("after p:[%s]\n", p);

    return 0;
}
