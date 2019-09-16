
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "mp_malloc.h"

/* TODO:
 * add sig process, when sigment print address content 
 * */

int main()
{
    /* malloc */
    size_t plen = 160;

    char *p = (char *)MP_MALLOC(plen);
    if (p == NULL) {
        return -1;
    }

    /* write */
    strcpy(p, "hello world");

    p[4] = '1';

    /* lock */
    if (MP_RLOCK(p, plen) == -1) {
        perror("Error: mportect");
        return -1;
    }

    printf("before p:[%s]\n", p);

    /* when rlock, error */
    char *p2 = (char *)MP_MALLOC(plen);
    strcpy(p2, "1111");
    if (MP_RLOCK(p2, plen) == -1) {
        perror("Error: mportect");
        return -1;
    }
    fprintf(stderr, "p2:%s\n", p2);

#if 0
    if (p) { 
        MP_RWLOCK(p, plen);
        free(p); 
    }
#endif

#if 0
    /* error */
    p[4] = '2';
    printf("after p:[%s]\n", p);
#endif

    return 0;
}
