#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 5
/*we could run into a race condition */
int counter = 0;
int array[BUFFER_SIZE];

void *producer(void *arg) {
    int item = 1;
    int i;
    int in=0;
    //put 10 items in array to be consumed by consumer
    while(1)
    {
        /*spin wait */
        while(counter==BUFFER_SIZE);
        array[in] = item;
        printf("put %i in array\n",item);
        in = (in + 1) % BUFFER_SIZE;
        counter++;

        //break after adding 10 items
        if(item==10) {
            printf("prod break\n");
            break;
        }
        item++;
    }
    printf("prod return\n");
}

void *consumer(void *arg) {
    int item = 0;
    int i;
    int out =0;
    //put 10 items in array to be consumed by consumer
    //producer consumer loops forever
    //we only loop 10 times so we can observe the array
    while(1)
    {
        //sit here and wait until counter is greater than 1
        //that means there is an item in the array to consume
        /*spin wait */
        while(counter==0);
        item = array[out];
        printf("retrieved %i from array\n", item);
        out = (out + 1) % BUFFER_SIZE;
        counter--;
        //break after retrieving 10 items
        if(item==10) {
            printf("cons break\n");
            break;
        } 
    }
        printf("cons return\n");
}

int main(int argc, char const *argv[])
{
    pthread_t prod;
    pthread_t cons1;
    pthread_t cons2;
    
    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons1, NULL,consumer,NULL);    
    
    //main thread and new thread run at the same time
    //if you don't call join, the main thread will print the result of sum before the
    //new thread has completed incrementing it
    pthread_join(prod, NULL);
    pthread_join(cons1, NULL);
    return 0;
}
