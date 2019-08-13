
#ifndef SAFE_MALLOC_H__
#define SAFE_MALLOC_H__

#define SAFE_FREE(p)    safe_malloc_free(__FILE__, __LINE__, p)
#define SAFE_MALLOC(s)  safe_malloc_malloc(__FILE__, __LINE__, s)

extern int safe_malloc_init(void);

extern void * safe_malloc_malloc(const char * file, size_t line, size_t size);

extern void safe_malloc_free(const char * file, size_t line, void * ptr);

extern void safe_malloc_result(void);

extern void safe_malloc_destroy(void);

#endif
