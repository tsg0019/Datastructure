#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "linkedListADT.h"
/*- 노드가 가리키는 데이터는 양의 정수인 키(Key) 값으로만 구성된다고 가정
- 테스트 절차를 수행하는 main 함수는 자유롭게 작성하면 됨
- 추가로 탐색(search)도 테스트해보면 좋겠음 (리스트 내에 target 데이터가 있는 경우와 없는 경우)
- 정상적인 동작 확인을 위해, 각 테스트 로직을 수행한 후 리스트 내의 전체 데이터들을 순회(traverse)하면서 화면에 출력해 보면 됨 (이를 화면 캡쳐하여 제출)
- ADT 라이브러리의 활용은 PPT에서 설명한 Academy Awards 예를 참조*/
const short STR_MAX = 41;
typedef struct {
    short number;
}PICTURE;
void printInstr(void);
LIST* buildList(void);
void process(LIST* list);
char getChoice(void);
void printList (LIST* list);
void search (LIST* list);

int cmpint(void* integer1,void* integer2);

int main(void){
    LIST* list;
    printInstr();
    list = buildList();
    //process(list);
    printf("\nEveryting done\n");
    printf("**TEST\n");
    return 0;
}

void printInstr(void){
    printf("지금부터 linkedListADT.h의 테스트를 진행하겠습니다.\n");
}

LIST* buildList(void){
    FILE* fpData;
    LIST* list;

    short numIn;
    int addResult;

    PICTURE* pPic;
    list = createList(cmpint);
    if(!list){
        printf("\a Cannot create list\n"), exit(100);
    }
    fpData = fopen("numbers.dat","r");
    
    printf("\n무사히 buildList 진입\n");//여기까지 문제 없는 것 확인.
    printf("\n현재 파일의 위치 : %p\n",fpData);
    if(!fpData){  //문제발생 예측되는 지역
        printf("\aError opening input file\n"), exit(100);
    }
    while(fscanf(fpData,"%hd",&numIn) == 1){
        printf("\nnow Inside the loop\n");//여기까지 문제 없는 것 확인.
        pPic = (PICTURE*)malloc(sizeof(PICTURE));
        if(!(pPic)){
            printf("\aOut of Memory in build list\n"), exit(100);
        }
        pPic->number = numIn;
        printf("\nnumIn : %d \n\n\n",numIn);
        while((fgetc(fpData)) != '\t'){//문제발생지역!!!!!!!무한루프!!!!!!!!!
            printf("\n**TEST**\n");
            ;
        }
        addResult = addNode(list,pPic);
        printList(list);
        printf("\n**TEST**\n");
        if(addResult != 0){
            if(addResult == -1){
                printf("Memory oerflow adding\a\n"),exit(120);
            }else{
                printf("Duplicate year %hd not added\n\a",pPic->number);
                while(fgetc(fpData) != '\n')
                    ;
            }
        }
    }
    printf("\n무사히 buildList 빠져나가는지 확인\n");//여기까지 문제 없는 것 확인.
    return list;
}
void process(LIST* list){
    char choice;
    do{
        choice = getChoice();
        switch(choice){
            case 'P' : printList(list);
            break;
            case 'S' : search(list);
            case 'Q' : break;
        }
    }while(choice != 'Q');
    return;
}
char getChoice(void){
    char choice;
    bool valid;
    printf("======== MENU =======\n"
    "Here are your choices : \n"
    "   S : Search for a number\n"
    "   P : Print all numbers\n"
    "   Q : Quit            \n\n"
    "Enter your choice: ");
    do{
        scanf("%c",&choice);
        choice = toupper(choice);
        switch(choice){
            case 'S' : 
            case 'P' :
            case 'Q' : valid = true;break;
            default : valid = false;
            printf("\a\n Invalid choice \n Please try again\n");
            break;
        }
    }while(!valid);
    return choice;
}
void printList (LIST* list){
    PICTURE* pPic;
    if(listCount(list) == 0){
        printf("현재 빈 리스트 입니다.\n");
    }
    else{
        printf("\n Best Pictures List\n");
        traverse(list,0,(void**)&pPic);
        do{
            printf("%hd\n",pPic->number);
        }while(traverse(list,1,(void**)&pPic));
    }
    printf("Complete to Print All List\n");
}
void search(LIST* list){
    short number;
    bool found;
    PICTURE pSrchArgu;
    PICTURE* pPic;
    printf("Enter number : ");
    scanf("%hd", &number);
    pSrchArgu.number = number;
    found = searchList(list,&pSrchArgu,(void**)&pPic);
    if(found){
        printf("%hd\n", pPic->number);
    }else{
        printf("Sorry, but %d is not abailable.\n",number);
    }
    return;
}
int cmpint(void* integer1,void* integer2){
    int result;
    short num1;
    short num2;
    num1 = ((PICTURE*)integer1)->number;
    num2 = ((PICTURE*)integer2)->number;

    if(num1 < num2){
        result = -1;
    }else if(num1 > num2){
        result = +1;
    }else{
        result = 0;
    }
    return result;
}