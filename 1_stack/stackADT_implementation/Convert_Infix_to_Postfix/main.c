#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stacksADT_myself.h"

int priority(char token);
bool isOperator(char token);

int main(){
    char postfix[80] = {0,};
    char temp[2] = {0};
    char token;
    char* dataptr;
    STACK* stack = createStack();
    
    printf("Enter an infix formula : ");
    while((token = getchar()) != '\n'){
        if(token == '('){
            dataptr = (char*)malloc(sizeof(char));
            *dataptr = token;
            pushStack(stack,dataptr);
        }
        else if(token == ')'){
            dataptr = (char*)popStack(stack);
            while(*dataptr == '('){
                temp[0] = *dataptr;
                strcat(postfix,temp);
                dataptr = (char*)popStack(stack);
            }
        }
        else if(isOperator(token)){
            dataptr = (char*)stackTop(stack);
            while((!emptyStack(stack)) && (priority(token)<=priority(*dataptr))){
                dataptr = (char*)popStack(stack);
                temp[0] = *dataptr;
                strcat(postfix,temp);
                dataptr = (char*)stackTop(stack);
            }
            dataptr = (char*)malloc(sizeof(char));
            *dataptr = token;
            pushStack(stack, dataptr);
        }
        else{
            temp[0] = token;
            strcat(postfix,temp);
        }
    }
    while(!emptyStack(stack)){
        dataptr = (char*)popStack(stack);
        temp[0] = *dataptr;
        strcat(postfix,temp);
    }
    printf("The postfix formula is : ");
    puts(postfix);

    destroyStack(stack);
    return 0;
}
//extra functions start
int priority(char token){
    if(token == '*' || token == '/'){
        return 2;
    }
    else if(token == '+' || token == '-'){
        return 1;
    }
    return 0;
}
bool isOperator(char token){
    if(token == '*' || token == '/' || token == '+' || token == '-'){
        return true;
    }
    return false;
}