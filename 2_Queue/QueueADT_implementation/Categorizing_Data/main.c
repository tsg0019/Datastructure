#include <stdio.h>
#include <stdlib.h>
#include "queuesADT.h"

void fillQueues(QUEUE* q0to9,QUEUE* q10to19,QUEUE* q20to29,QUEUE* qover29);
void printQueues(QUEUE* q0to9,QUEUE* q10to19,QUEUE* q20to29,QUEUE* qover29);

int main(){
    QUEUE* q0to9;
    QUEUE* q10to19;
    QUEUE* q20to29;
    QUEUE* qover29;

    q0to9 = creatQueue();
    q10to19 = creatQueue();
    q20to29 = creatQueue();
    qover29 = creatQueue();

    fillQueues(q0to9, q10to19, q20to29, qover29);
    printQueues(q0to9, q10to19, q20to29, qover29);


    return 0;
}
void fillQueues(QUEUE* q0to9,QUEUE* q10to19,QUEUE* q20to29,QUEUE* qover29){
    int category;
    int item;
    int* dataptr;
    for(int i = 0;i<25;i++){
        if(i%11 == 0){
            printf("\n");
        }
        item = *dataptr = rand() % 51;      //  0~50 will generated uniformly
        category = item / 10;
        switch(category){
            case 0 : enqueue(q0to9,dataptr);
            case 1 : enqueue(q10to19,dataptr);
            case 2 : enqueue(q20to29,dataptr);
            default : enqueue(qover29,dataptr);
        }
    }
    printf("\nEnd of data categorization\n\n");
    return ;
}
void printQueues(QUEUE* q0to9,QUEUE* q10to19,QUEUE* q20to29,QUEUE* qover29){
    printf("Data    0..9 : ");
    printOneQueues(q0to9);
    printf("Data    10..19 : ");
    printOneQueues(q10to19);
    printf("Data    20..29 : ");
    printOneQueues(q20to29);
    printf("Data over 29 : ");
    printOneQueues(qover29);
}
void printOneQueues(QUEUE* pQueue){
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
            printf("\n          ");
        }
        printf("%3d",*dataptr);
    }
    printf("\n");
    return ;
}