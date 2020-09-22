#include <stdio.h>
#include "stacksADT.h"

int main(){
    unsigned int num;
    int* digit;
    STACK* stack;

    stack = creatStack();
    printf("Enter an integer :  ");
    scanf("%d",&num);

    while(num > 0){
        digit = (int*)malloc(sizeof(int));
        *digit = num % 2;
        // printf("%d",*digit);
        pushStack(stack, digit);
        num = num / 2;
        
    }

    printStack(stack);

    printf("The binary number is : ");
    while(!emptyStack(stack)){      //executed until returned value becomes 1
        digit = (int*)popStack(stack);
        printf("%d",*digit);
    }
    printf("\n");

    destroyStack(stack);
    return 0;
}