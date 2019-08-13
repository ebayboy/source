
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

/* TODO:
 * add sig process, when sigment print address contect 
 * */

struct mem_align {
    void *origin_start;  // for free
    void *start;         // data addr start, align page size
    void *end;           // data addr end,   align page size
    void *origin_end;
};

int malloc_align_page(size_t memsize, struct mem_align *mem)
{
    if (memsize == 0 || mem == NULL)
        return -1;

    memset(mem, 0, sizeof(*mem));
    long pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf err");
        return -1;
    }

    size_t datasize = memsize + pagesize * 2;
    mem->origin_start = malloc(datasize);
    if(mem->origin_start == NULL)
        return -1;
    mem->origin_end = mem->origin_start + datasize;

    long mask = pagesize - 1;
    mem->start = (void *)((long)(mem->origin_start + pagesize) & ~mask);
    long pagenum = memsize / pagesize + 1;
    mem->end = mem->start + pagesize * pagenum;

    return 0;
}

int main()
{
    int ret;
    struct mem_align mem;

    /* malloc */
    ret = malloc_align_page(4097, &mem);
    if (ret != 0) {
        return ret;
    }

    /* write */
    char *p = mem.start;
    strcpy(p, "hello world");
    p[4] = '1';

    /* lock */
    ret = mprotect(mem.start, (size_t)(mem.end - mem.start), PROT_READ);
    if (ret == -1) {
        perror("mportect");
        return ret;
    }
    printf("before mem.start:[%s]\n", p);

    /* error */
    p[4] = '2';
    printf("after mem.start:[%s]\n", p);

    return 0;
}
