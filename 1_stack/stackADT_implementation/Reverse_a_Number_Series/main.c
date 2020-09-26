#include <stdio.h>
#include <stdbool.h>
#include "stacksADT_myself.h"

int main(){
    STACK* stack;
    stack = createStack();
    bool condition = fullStack(stack);
    int* dataptr;

    while(!condition){
        dataptr = (int*)malloc(sizeof(int));
        printf("Enter a number: <EOF> to stop : ");   
        if((scanf("%d",dataptr)) == EOF || fullStack(stack)){
            condition = true;
        }else{
            pushStack(stack,dataptr);
            condition = fullStack(stack);
        }
    }
    printf("\n");
    
    printStack(stack);
    destroyStack(stack);
    
    return 0;
}