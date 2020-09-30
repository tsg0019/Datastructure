#include <stdio.h>
#include "queuesADT.h"
int main(){
    QUEUE* queue;
    int* dataptr;
    bool howgoing;

    int a = 1;
    int b = 2;
    int c = 3;

    enqueue(queue,&a);
    enqueue(queue,&b);
    enqueue(queue,&c);
    printQueue(queue);

    return 0;
}