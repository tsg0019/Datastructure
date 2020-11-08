#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "linkedListADT.h"
const short STR_MAX = 41;
typedef struct {
    short number;
}PICTURE;
void printInstr(void);
LIST* buildList(void);
void process(LIST* list);
char getChoice(void);
void printList(LIST* list);
void search(LIST* list);
int cmpint(void* integer1, void* integer2);

int main(void) {
    LIST* list = NULL;
    printInstr();
    short newdata;    int status;
    list = createList(list);
    newdata = 10;
    printf("\n///insert a node before the first data node\n");
    addNode(list, &newdata);
    printList(list);
    list = buildList();
    int newdata2 = 1;    
    status = addNode(list, &newdata2);    
    printf("\n//////// case : insert a node before the first data node");
    printList(list);
    int newdata1 = 11;
    status = addNode(list, &newdata1);    
    printf("\n////////case : insert a node after the last nodes");
    printList(list);
    int newdata3 = 8;
    status = addNode(list, &newdata3);    
    printf("\n////////case : insert a node between data nodes");
    printList(list);
     process(list);
    printf("\nEveryting done\n");
    return 0;
}

void printInstr(void) {
    printf("지금부터 linkedListADT.h의 테스트를 진행하겠습니다.\n");
}

LIST* buildList(void) {
    FILE* fpData;
    LIST* list;
    short numIn;

    int addResult;

 

    PICTURE* pPic;

    list = createList(cmpint);

    if (!list) {

        printf("\a Cannot create list\n"), exit(100);

    }

    fpData = fopen("numbers.dat", "r");

 

    printf("\n=======numbers.dat에 있는 data를 link에 추가======");

    if (!fpData) {  

        printf("\aError opening input file\n"), exit(100);

    }

    while (fscanf(fpData, "%hd", &numIn) == 1) {

        pPic = (PICTURE*)malloc(sizeof(PICTURE));

        if (!(pPic)) {

            printf("\aOut of Memory in build list\n"), exit(100);

        }

        pPic->number = numIn;

        printf("\n현재 리스트에 추가 될 numIn : %d \n", numIn);

        while ((fgetc(fpData)) != '\t') {

            ;

        }

        addResult = addNode(list, pPic);

        printList(list);

        

        if (addResult != 0) {

            if (addResult == -1) {

                printf("NOTE!! : 메모리 overflow 발생\a\n"), exit(120);

            }

            else {

                printf("이미 key 값 %hd를 가지는 노드가 존재합니다. 추가하지 않았습니다.\n\a", pPic->number);

                printf("\n=======numbers.dat에 있는 data를 link에 추가끝!!!======\n");

                return list;

            }

        }

    }

    printf("=======numbers.dat에 있는 data를 link에 추가끝!!!======\n");

    return list;

}

void process(LIST* list) {

    char choice;

    do {

        printf("\n**TEST\n");

        choice = getChoice();

        switch (choice) {

        case 'P': printList(list);

            break;

        case 'S': search(list);

        case 'Q': break;

        }

    } while (choice != 'Q');

    return;

}

char getChoice(void) {

    char choice;

    bool valid;

    printf("======== MENU =======\n"

        "Here are your choices : \n"

        "   S : Search for a number\n"

        "   P : Print all numbers\n"

        "   Q : Quit            \n\n"

        "Enter your choice: ");

    do {

        scanf("%c", &choice);

        choice = toupper(choice);

        while (choice == '\n') { 

            choice = getchar();

        }

        printf("\nChoice는 현재 %c\n",choice);

        switch (choice) {

        case 'S':

        case 'P':

        case 'Q':   valid = true;

                    break;

        /*case '\n':  getchar();

            valid = false; break;*/

        default:    valid = false;

                    printf("\a\n Invalid choice Please try again\n");

                    break;

        }

    } while (!valid);

    return choice;

}

void printList(LIST* list) {

    PICTURE* pPic;

    if (listCount(list) == 0) {

        printf("현재 빈 리스트 입니다.\n");

    }

    else {

        printf("\n-------------현재 List\n");

        traverse(list, 0, (void**)&pPic);

        do {

            printf("%hd ", pPic->number);

        } while (traverse(list, 1, (void**)&pPic));

    }

    printf("\n-------------현재 List 출력완료\n\n");

}

void search(LIST* list) {

    short number;

    bool found;

    PICTURE pSrchArgu;

    PICTURE* pPic;

    printf("Enter number : ");

    scanf("%hd", &number);

    pSrchArgu.number = number;

    found = searchList(list, &pSrchArgu, (void**)&pPic);

    if (found) {

        printf("%hd는 현재 리스트 내에 존재한답니다.\n", pPic->number);

    }

    else {

        printf("죄송합니다. %d 는 존재하지 않습니다..\n", number);

    }

    return;

}

int cmpint(void* integer1, void* integer2) {

    int result;

    short num1;

    short num2;

    num1 = ((PICTURE*)integer1)->number;

    num2 = ((PICTURE*)integer2)->number;

 

    if (num1 < num2) {

        result = -1;

    }

    else if (num1 > num2) {

        result = +1;

    }

    else {

        result = 0;

    }

    return result;

}