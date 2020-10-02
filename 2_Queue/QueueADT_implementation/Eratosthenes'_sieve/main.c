#include <stdio.h>
#include "queuesADT.h"
#include <stdbool.h>

int* find_prime();
int main(){
    QUEUE* queue = creatQueue();
    int* dataptr;
    int arr[101] = {0};      //a[0] ~ a[100] = 2~100      arr[i] = 0 means not prime  /// arr[i] = 1 means it is prime number
    for(int i = 0; i<= 100 ; i++){
        arr[i] = !arr[i];
    }
    printf("before\n");
    for(int i = 0; i<= 100 ; i++){
        if(i%10 == 0){
            printf("\n");
        }
        printf("%3d",arr[i]);
    }
    arr[0] = arr[1] = 0;
    int current = 2;
    int to_compare = 2;
    while(current <= 100){
        to_compare = current +1;
        while(to_compare<=100){
            if((to_compare%current) == 0){
                arr[to_compare] = 0;
            }
            to_compare++;

        }
        current ++;
        while(arr[current] == 0){
            current ++;
        }
    }
    printf("\n\nresult\n");
    for(int i = 0;i <= 100;i++){
        if(i%10 == 0){
            printf("\n");
        }
        if(arr[i]==1){
            dataptr = (int*)malloc(sizeof(int));
            *dataptr = i;
            printf("%3d",i);
            enqueue(queue, dataptr);
        }
    }
    printf("\n\n\nprintqueue : \n");
    printQueue(queue);

    destroyQueue(queue);
    return 0;
}
