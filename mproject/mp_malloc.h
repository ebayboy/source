
#ifndef __MP_MALLOC_H__
#define __MP_MALLOC_H__

#include <sys/mman.h>

#define MP_MALLOC(slen) malloc_align_page(slen)
#define MP_RLOCK(start, slen) mprotect(start, (size_t)(slen), PROT_READ)
#define MP_FREE(start) free(start)

void * malloc_align_page(size_t memsize);

#endif


