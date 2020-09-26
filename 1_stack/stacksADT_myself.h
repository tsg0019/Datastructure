#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    void* data;
    struct node* link;
}STACK_NODE;

typedef struct stack{
    int count;
    STACK_NODE* top;
} STACK;

STACK* createStack(void){
    STACK* stack;
    stack = (STACK*)malloc(sizeof(STACK));
    if(stack){
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;                              //starting address of metadata
}

bool pushStack (STACK* stack, void* dataInPtr){//after pushStack, it returns whether success or not
    STACK_NODE* nodeptr;
    nodeptr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if(nodeptr){
        nodeptr->data = dataInPtr;
        nodeptr->link = stack->top;             //first, put stack's top address into nodeptr's link

        stack->count++;
        stack->top = nodeptr;                   //now, stack's Top is nodeptr's address

        return true;
    }else{
        return false;
    }
} 
void* popStack(STACK* stack){                  //after popStack, it returns address of data which was data of TOS
    STACK_NODE* nodeptr;
    void* data_of_pop;
    if(stack->count >0){
        nodeptr = stack->top;                   //store current address of top
        stack->count--;                         //stack's count 1 decrease
        data_of_pop = stack->top->data;         //data_of_top indicates address of data which will vanish
        stack->top = stack->top->link;          //now, stack's top must indicates address of link of top
        free(nodeptr);                          //return the dynamic memory
        
        return data_of_pop;
    }else{
        return NULL;
    }
}
void* stackTop(STACK* stack){           //warning!!! it returns address of data in top!!
    if(stack->count > 0){               //it doesn't returns address of top!! address of data!!
        return stack->top->data;
    }
    return NULL;
}
bool emptyStack (STACK* stack){
    /*if(stack->count == 0){
        return true;
    }
    return false;*/
    return (stack->count == 0);
}
bool fullStack (STACK* stack){
    STACK_NODE* temp;
    if((temp = (STACK_NODE*)malloc(sizeof(stack->top)))){   //WHAT I WANT TO ASK
        free(temp);
        return true;
    }
    return false;
}

int stackCount(STACK* stack){
    return stack->count;
}
STACK* destroyStack(STACK* stack){      //function what I made
    STACK_NODE* temp;
    while(stack->top){
        temp = stack->top;
        free(stack->top->data);
        stack->top = stack->top->link;
        stack->count --;
        free(temp);
    }
    free(stack);
    return NULL;
}
void printStack(STACK* stack){
    while(stack->top){
        printf("%d\n",*(int*)(stack->top->data));
        stack->top = stack->top->link;
    }
}
/*int stackCount(STACK* stack){
    return stack->count;
}
STACK* destroyStack(STACK* stack){
    STACK_NODE* temp;
    if(stack){
        while(stack->top != NULL){
            free(stack->top->data);
            temp = stack->top;
            stack->top = stack->top->link;
            free(temp);
        }
        free(stack);
    }
    return NULL;
}
*/
/*void printStack(STACK* stack) {
    STACK_NODE* current = stack->top;

    while (current) {
        printf("%d ", *(int*)(current->data));
        current = current->link; 
    }
    printf("\n");
}*/