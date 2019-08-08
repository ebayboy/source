
/*safe_malloc.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <pthread.h>
#include <assert.h>
#include "safe_malloc.h"

#ifdef SAFE_MALLOC
static pthread_mutex_t lock;
static std::map<unsigned long, std::string> cache;

static void err_exit(const char * info)
{
    fprintf(stderr, "%s\n", info);
    exit(1);
}
#endif

void * safe_malloc_malloc(const char * file, size_t line, size_t size)
{
    void * mem = malloc(size);

#ifdef SAFE_MALLOC
    assert(size != 0);  
    if(mem)
    {
        char buf[266] = {0};
        snprintf(buf, sizeof(buf), "file[%s], line[%d]", file, line);

        pthread_mutex_lock(&lock);
        cache.insert(std::make_pair((unsigned long)mem, buf));
        pthread_mutex_unlock(&lock);
    }
#endif

    return mem;
}


void safe_malloc_free(const char * file, size_t line, void * ptr)
{
#ifdef SAFE_MALLOC
    size_t cnt;
    std::map<unsigned long, std::string>::iterator it;

    assert(ptr != NULL);    
#endif

    free(ptr);

#ifdef SAFE_MALLOC
    pthread_mutex_lock(&lock);

    cnt = cache.erase((unsigned long)ptr);
    if(cnt == 0)
    {
        err_exit("cache.erase nothing");
    }

    pthread_mutex_unlock(&lock);
#endif
}

void safe_malloc_result(void)
{
#ifdef SAFE_MALLOC
    std::map<unsigned long, std::string>::iterator it;

    pthread_mutex_lock(&lock);      

    if(cache.size() == 0)
    {
        printf("Congratulations, there is no memery leak!\n");
        return;
    }
    printf("memery leak info: \n"); 
    for(it = cache.begin(); it != cache.end(); it++)
    {
        printf("\tmem addr: %ld, location info: %s\n", it->first, it->second.c_str());
    }

    pthread_mutex_unlock(&lock);
#endif
}

int safe_malloc_init(void)
{
#ifdef SAFE_MALLOC
    if(pthread_mutex_init(&lock, NULL) != 0)
    {
        return -1;
    }
#endif

    return 0;
}

void safe_malloc_destroy(void)
{

#ifdef SAFE_MALLOC
    pthread_mutex_destroy(&lock);
#endif

}

