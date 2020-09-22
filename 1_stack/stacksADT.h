#include <stdio.h>
#include <stdlib.h>

typedef struct node {        //STACK_NODE had address of data and address of next stack step
    void* dataPtr;
    struct node* link;
} STACK_NODE;


typedef struct stack    //STACK has number of stack count and address of stack top
{
    int count ;
    STACK_NODE* top ;
} STACK;

STACK* creatStack(void){
    STACK* stack;

    stack = (STACK*)malloc(sizeof(STACK));
    if(stack){
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;
}

int pushStack(STACK* stack, void* dataInPtr){
    STACK_NODE* newPtr;

    newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));

    if(!newPtr){
        return 0;    
    }
    newPtr->dataPtr = dataInPtr;
    newPtr->link = stack->top;
    stack->top = newPtr;
    (stack->count)++;
    return 1;
}
void* popStack(STACK* stack){
    void* dataOutPtr;
    STACK_NODE* temp;
    if(stack->count == 0){
        dataOutPtr = NULL;
    }
    else{
        temp = stack->top; 
        dataOutPtr = stack->top->dataPtr;
        stack->top = stack->top->link;
        free(temp);
        (stack->count)--;
    }

    return dataOutPtr;
}
void* stackTop(STACK* stack){
    if(stack->count == 0){
        return NULL;
    }else
    {
        return stack->top->dataPtr;
    }
}
int emptyStack(STACK* stack){  //Only if stack->count == 0 then it will return 1
    return (stack->count == 0);
}
int fullStack (STACK* stack){
    STACK_NODE* temp;
    if(temp = (STACK_NODE*)malloc(sizeof(STACK_NODE))){
        free(temp);
        return 0;       //return false if there is free space in Heap
    }
    return 1;            //it means temp=NULL, there is no space in Heap space
}
int stackCount(STACK* stack){
    return stack->count;
}
STACK* destroyStack(STACK* stack){
    STACK_NODE* temp;
    if(stack){
        while(stack->top != NULL){
            free(stack->top->dataPtr);
            temp = stack->top;
            stack->top = stack->top->link;
            free(temp);
        }
        free(stack);
    }
    return NULL;
}

void printStack(STACK* stack) {
    STACK_NODE* current = stack->top;

    while (current) {
        printf("%d ", *(int*)(current->dataPtr));
        current = current->link; 
    }
    printf("\n");
}