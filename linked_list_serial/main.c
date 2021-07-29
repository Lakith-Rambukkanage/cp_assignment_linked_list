#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list_serial_struct.h"

//Config
#define NUMBER_COUNT 1000
#define METHOD_COUNT 10000
int n = NUMBER_COUNT; //1000
int m = METHOD_COUNT; //10000


double m_frac = 0.99;
double i_frac = 0.005;
double d_frac = 0.005;


int m_num;
int i_num;
int d_num;


int process_order[METHOD_COUNT];   //the random order of processes according to the fractions

LinkedList *l_list;

int main()
{
    int no_of_observations = 30;
    int observation_n = 0;

    while (no_of_observations>observation_n){
        //config
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
                if (rand()%(int)(m_frac*100)!=0) break; //to distribute 1(instert),2(delete)
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
        //printf("%d \n",sizeof(process_order)/sizeof(process_order[0]));

        //time
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        //--------------------------
        for (int i = 0; i<m; i++){
            switch (process_order[i]){
            case 0:
                Member(l_list, rand() % 65535);
                break;
            case 1:
                Insert(l_list, rand() % 65535);
                break;
            case 2:
                Delete(l_list, rand() % 65535);
                break;
            }
        }
        //--------------------------
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("%d time -- : %1f \n",observation_n, cpu_time_used);
        observation_n++;
    }
    return 0;
}
