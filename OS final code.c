#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


int s = 6; // Number of students
int n = 3; // capactiy / threads
int q = 3; // questions per Student

int num_questions[];

sem_t Wait;

int Advisor(int S_number)
    {   sem_wait(&Wait);
        printf("Advisse ");
        printf("%d", S_number);
        printf(" enters the office. \n");
        sem_post(&Wait);


         //while(num_questions[S_number]);
         for(int i=0; i <= q; i++)
           {


            sem_wait(&Wait);
            printf("Advisse ");
            printf("%d", S_number);
            printf(" question Answered. \n");
            num_questions[S_number]--;

            printf("%d", num_questions[S_number]);
            printf(" Questions left. \n");
            sem_post(&Wait);

            if(num_questions[S_number] == 0)
            {
                printf("Advisse ");
                printf("%d", S_number);
                printf(" Leaves the office. \n");
                S_number += n;

                if(S_number >= s)
                    {
                        return 0;
                    }
                printf("Advisse ");
                printf("%d", S_number);
                printf(" enters the office. \n");
                i=0;

            }

           }


    }

int main()
{

    sem_init(&Wait,0, 1);
    pthread_t thread[n];

    for(int i = 0; i < s; i++)
    {
        num_questions[i] = q;
        //printf("%d", num_questions[i]);
        //puts("");
    }

    for(int x = 0; x < n; x++)
    {
        pthread_create(&thread[x], NULL, Advisor, x);
    }

    for(int x = 0; x < n; x++)
    {
        pthread_join(thread[x], NULL);
    }

    return 0;
}
