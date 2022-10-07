

#include <stdio.h>
#include <thread>
#include <pthread.h>
#include <chrono>


void work(int load)
{
    unsigned int total = 0;
    for (int i = 1; i < load; i++)
    {
        for (int j = 1; j < load; j++)
            total += j;
    }
    if (total > 1) 
        printf("\0");
}


void s_work(int load)
{
    work(load);
}

void * p_work(void* load)
{
    work(*(int*) load);
    return NULL;
}


int main()
{
    printf("Test 1: Single Thread\n");
    const int test1load = 50000;
    {   
        printf("std::thread: \t");
        auto t1 = clock();

        std::thread thread(s_work,test1load);
        thread.join();

        auto t2 = clock();
        printf("Took %f sec\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
    }
    {
        printf("pthread: \t");
        auto t1 = clock();

        pthread_t thread;
        pthread_create(&thread, NULL, p_work, (void *) &test1load);
        pthread_join(thread, NULL);
        
        auto t2 = clock();
        printf("Took %f sec\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
    }


    printf("Test 2: Many threads\n");
    const int spawns = 30000;
    const int testload2 = 10;
    {   
        printf("std::thread: \t");
        auto t1 = clock();

        for (int i = 0; i < spawns; i++)
        {
            std::thread thread(s_work,testload2);
            thread.join();    
        }

        auto t2 = clock();
        printf("Took %f sec\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
    }
    {
        printf("pthread: \t");
        auto t1 = clock();

        for (int i = 0; i < spawns; i++)
        {
            pthread_t thread;
            pthread_create(&thread, NULL, p_work, (void *) &testload2);
            pthread_join(thread, NULL);
        } 
        
        auto t2 = clock();
        printf("Took %f sec\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
    }


}




