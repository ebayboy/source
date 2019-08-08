
#ifndef MEM_LEAK_TEST_H
#define MEM_LEAK_TEST_H

#define test_free(p)    test_safe_free(__FILE__, __LINE__, p)
#define test_malloc(s)  test_safe_malloc(__FILE__, __LINE__, s)

extern void test_safe_free(const char * file, size_t line, void * ptr);
extern void * test_safe_malloc(const char * file, size_t line, size_t size);
extern void mem_leak_test_result(void);
extern int mem_leak_test_init(void);
extern void mem_leak_test_destroy(void);

#endif
