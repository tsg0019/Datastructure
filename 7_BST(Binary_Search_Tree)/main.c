#include <stdio.h>
#include <stdlib.h>
#include "bstADT.h"

int compareInt(void* num1, void* num2);
void printBST(void* num1);
void sumBST(void* num2);
void Insert_Delete_TEST(BST_TREE* tree);
void does_Destroy_works_well(BST_TREE* tree);

int main(void){
    BST_TREE* BSTRoot;
    int* dataPtr;
    int dataIn = +1;

    printf("Begin BST Demonstration\n");

    BSTRoot = BST_Create(compareInt);
    Insert_Delete_TEST(BSTRoot);  //to test

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
void Insert_Delete_TEST(BST_TREE* tree){
    int* num_to_put_delete = (int*)malloc(sizeof(int));
    *num_to_put_delete = 5;

    printf("\n/***********Test************/\n");
    printf("Let me see BST_Insert works well\n");
    BST_Insert(tree, (void*)num_to_put_delete);
    printf("Resulf of put number into NULL tree : ");
    BST_Traverse(tree, printBST);
    printf("BST_Insert works well\n");

    bool Destroy_success;
    printf("\nLet me see BST_Delete works well\n");
    Destroy_success = BST_Delete(tree,(void*)num_to_put_delete);
    if(Destroy_success){
        printf("success = true\n");
        printf("BST_Delete works well\n");
        printf("/***********Test DONE***********/\n\n");
    }
    return;
}
void does_Destroy_works_well(BST_TREE* tree){
    BST_TREE* Destroy_TEST = BST_Destroy(tree); //<--made by junghoon Lee
    if(!Destroy_TEST)
        printf("We can notice that Destroy completely works\n");
    return;
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