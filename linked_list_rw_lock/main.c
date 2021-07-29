#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "linked_list_rw_struct.h"

//Config
#define NUMBER_COUNT 1000
#define METHOD_COUNT 10000
int thread_count = 4;
int n = NUMBER_COUNT; //1000
int m = METHOD_COUNT; //10000


double m_frac = 0.99;
double i_frac = 0.005;
double d_frac = 0.005;


int m_num;
int i_num;
int d_num;

void *thread_function(void *);

int process_order[METHOD_COUNT];   //the random order of processes according to the fractions

LinkedList *l_list;

int main()
{
    int no_of_observations = 30;
    int observation_n = 0;


    while (no_of_observations>observation_n){
        srand(time(0));

        m_num = (int) m * m_frac;
        i_num = (int) m * i_frac;
        d_num = (int) m - (m_num + i_num);

        l_list = createLinkedList();

        int code = 0;

        for (int i=0; i<n; i++){
            code = Insert(l_list,rand() % 65535);
            if (code==0) i--;
        }

        //printLinkedList(l_list);


        int c = 0;
        int rand_int;

        while (m_num>0 || i_num>0 || d_num>0){
            rand_int = rand()%3;
            switch (rand_int){
            case 0:
                if (m_num==0) break;
                process_order[c] = rand_int;
                m_num--;
                c++;
                break;
            case 1:
                if (i_num==0) break;
                if (rand()%(int)(m_frac*100)!=0) break;//to distribute 1(instert),2(delete)
                process_order[c] = rand_int;
                i_num--;
                c++;
                break;
            case 2:
                if (d_num==0) break;
                if (rand()%(int)(m_frac*100)!=0) break; //to distribute 1(instert),2(delete)
                process_order[c] = rand_int;
                d_num--;
                c++;
                break;
            }
        }

        //for(int k=0; k<m; k++)
            //printf("%d",process_order[k]);

        //------PTHREADS-----------
        pthread_t* thread_handles;
        thread_handles=(pthread_t*)malloc(thread_count*sizeof(pthread_t));

        //time
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        //--------------------------

        for (int i=0; i< thread_count; i++){
           pthread_create(&thread_handles[i], NULL, thread_function, (void*)i);
        }

        for (int i=0; i < thread_count; i++)
            pthread_join(thread_handles[i], NULL);

        //--------------------------
        end = clock();

        free(thread_handles);

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("%d time -- : %1f \n",observation_n, cpu_time_used);
        observation_n++;
    }
    return 0;
}

void *thread_function(void* rank){
    int my_rank = (int) rank;
    //printf("Hello from thread %ld of %d\n", my_rank, thread_count);

    int start_point = (int)my_rank*(m/thread_count);
    int end_point = (int)(my_rank+1)*(m/thread_count);

    //printf("rank : %d, s: %d, e: %d\n",my_rank,start_point,end_point );

    for(int curr_method = start_point; curr_method<end_point; curr_method++){
        //0,1,2 of process_order[curr_method] decide which method to run member | insert | delete
        switch (process_order[curr_method]){
            case 0:
                pthread_rwlock_rdlock( &l_list->rwlock );
                Member(l_list, rand() % 65535);
                pthread_rwlock_unlock( &l_list->rwlock );
                break;
            case 1:
                pthread_rwlock_wrlock( &l_list->rwlock );
                Insert(l_list, rand() % 65535);
                pthread_rwlock_unlock( &l_list->rwlock );
                break;
            case 2:
                pthread_rwlock_wrlock( &l_list->rwlock );
                Delete(l_list, rand() % 65535);
                pthread_rwlock_unlock( &l_list->rwlock );
                break;
        }
    }


    return NULL;
}
