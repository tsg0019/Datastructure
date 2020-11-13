#include <stdio.h>
#include <stdlib.h>
#include "bstADT.h"

int compareInt(void* num1, void* num2);
void printBST(void* num1);

int main(void){
    BST_TREE* BSTRoot;
    int* dataPtr;
    int dataIn = +1;

    printf("Begin BST Demonstration\n");
    BSTRoot = BST_Create(compareInt);
    printf("Enter a list of positive integers;\n");
    printf("Enter a negative number to stop.\n");
    do{
        printf("Enter a number : ");
        scanf("%d",&dataIn);
        if(dataIn > -1){
            dataPtr = (int*)malloc(sizeof(int));
            if(!dataPtr){
                printf("Memory Overflow in add\n"), exit(100);
            }
            *dataPtr = dataIn;
            BST_Insert(BSTRoot,dataPtr);
        }
    }while(dataIn > -1);
    printf("\nBST contains : \n");
    BST_Traverse(BSTRoot,printBST);
    printf("\nEnd BST Demonstration\n");
    return 0;
}
int compareInt(void* num1, void* num2){
    int key1;
    int key2;
    key1 = *(int*)num1;
    key2 = *(int*)num2;
    if(key1 < key2)
        return -1;
    if(key1 == key2)
        return 0;
    return +1;
}
void printBST(void* num1){
    printf("%4d\n",*(int*)num1);
    return;
}