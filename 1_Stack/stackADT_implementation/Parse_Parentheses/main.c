#include <stdio.h>
#include "stacksADT_myself.h"

const char closeMiss[] = "Close paren missing at line";
const char openMiss[] = "Open paren missing at line";

int main(){
    STACK* stack;
    char token;
    char fileID[25];
    FILE* fpIn;
    char* dataptr;
    int lineCount = 1;
    stack = createStack();
    printf("Enter file ID for file to be parsed : ");
    scanf("%s",fileID);

    fpIn = fopen(fileID,"r");

    if(!fpIn){printf("Error opening %s\n",fileID);exit(100);}

    while((token = fgetc(fpIn)) != EOF){
        if(token == '\n'){
            lineCount++;
        }
        else if(token == '('){
            dataptr = (char*)malloc(sizeof(char));
            pushStack(stack,dataptr);
        }else if (token == ')'){
            if(emptyStack(stack)){
                printf("%s\nand the line number is %d\n",openMiss, lineCount);
                destroyStack(stack);
                return 1;
            }else{
                popStack(stack);
            }
        }
    }
    if(!emptyStack(stack)){
        printf("%s\n",closeMiss);       //hard to find where the closemiss problem occured
        destroyStack(stack);
        return 1;
    }
    destroyStack(stack);
    printf("Parsing is OK : %d Lines parsed.\n",lineCount);

    return 0;
}