#include <stdio.h>
#include <stdlib.h>
#include "queuesADT.h"

void fillQueues(QUEUE* q0to9,QUEUE* q10to19,QUEUE* q20to29,QUEUE* qover29);
void printQueues(QUEUE* q0to9, QUEUE* q10to19, QUEUE* q20to29, QUEUE* qover29);
void printOneQueue(QUEUE* pQueue);

int main(){
    QUEUE* q0to9;
    QUEUE* q10to19;
    QUEUE* q20to29;
    QUEUE* qover29;
    printf("Welcome to a demonstration of categorizing data.\n"
    "We generate 25 random numbers and then group them into categories using queues.\n\n");
    q0to9 = creatQueue();
    q10to19 = creatQueue();
    q20to29 = creatQueue();
    qover29 = creatQueue();

    fillQueues(q0to9, q10to19, q20to29, qover29);
    printQueues(q0to9, q10to19, q20to29, qover29);
   
    printf("\ndone**main\n");
    return 0;
}
void fillQueues(QUEUE* q0to9,QUEUE* q10to19,QUEUE* q20to29,QUEUE* qover29){
    printf("Categorizing data :\n");
    srand(79);
    int category;
    int item;
    int* dataptr;
    for(int i = 1;i<=25;i++){
        if(!(dataptr = (int*)malloc(sizeof(int)))){
            printf("Overflow in fillQueues\a\n"),exit(100);
        }
        item = *dataptr = rand() % 51;      //  0~50 will generated uniformly
        category = item / 10;
        printf("%3d",item);
        if(!(i%11)){
            printf("\n");
        }
        switch(category)
        {
            case 0 : enqueue(q0to9,dataptr);
                break;
            case 1 : enqueue(q10to19,dataptr);
                break;
            case 2 : enqueue(q20to29,dataptr);
                break;
            default : enqueue(qover29,dataptr);
                break;
        }
    }
    printf("\nEnd of data categorization\n\n");
    return ;
}
void printQueues(QUEUE* q0to9, QUEUE* q10to19, QUEUE* q20to29, QUEUE* qover29) {
    printf("Data    0..9 : ");
    printOneQueue(q0to9);
    printf("Data  10..19 : ");
    printOneQueue(q10to19);
    printf("Data  20..29 : ");
    printOneQueue(q20to29);
    printf("Data over 29 : ");
    printOneQueue(qover29);
}
void printOneQueue(QUEUE* pQueue){
    /*while(queue->count > 0){
        printf("%d",(int)(queue->front->dataptr));
        (queue->count)--;
        queue->front = queue->front->next;
    }*/
    int lineCount = 0;
    int* dataptr;
    while(!emptyQueue(pQueue)){
        dequeue(pQueue,(void*)&dataptr);
        if(lineCount++ >= 10){
            lineCount = 1;
            printf("\n               ");
        }
        printf("%3d",*dataptr);
    }
    printf("\n");
    return ;
}