#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>

 

typedef struct node {
    void* dataptr;
    struct node* link;
}   NODE;

typedef struct {
    int count;
    NODE* pos;
    NODE* head;
    NODE* rear;
    int (*compare) (void* argu1, void* argu2);   //compare function pointer
} LIST;

 

LIST* createList(int (*compare)(void* argu1, void* argu2));
LIST* destroyList(LIST* list);
int addNode(LIST* pList, void* dataInPtr);
bool removeNode(LIST* pList, void* pArgu, void** pDataOut);
bool traverse(LIST* pList, int fromWhere, void** dataOutPtr);
bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr);
int listCount(LIST* pList);
bool emptyList(LIST* pList);
bool fullList(LIST* pList);

 

static bool _insert(LIST* pList, NODE* pPre, void* dataInPtr);
static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr);
static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);

 

LIST* createList(int (*compare)(void* argu1, void* argu2)) {
    LIST* list;
    list = (LIST*)malloc(sizeof(LIST));
    if (list) {
        list->head = NULL;
        list->pos = NULL;
        list->rear = NULL;
        list->count = 0;
        list->compare = compare;
    }
    return list;
}
int addNode(LIST* pList, void* dataInPtr) {
    bool found;//성공하면 0, 오버플로우 발생은 -1, 같은 값 존재하면 1 반환
    bool success;
    NODE* pPre ;
    NODE* pLoc;
    found = _search(pList, &pPre, &pLoc, dataInPtr);
    if (found) {
        return (+1);//똑같은 값을 찾은 경우 이므로 값을 넣어줄 필요 없어서 종료
    }   //나머지 결과가 false인 경우에 대해서는 모두 삽입연산을 수행
    success = _insert(pList, pPre, dataInPtr);
    if (!success) {//success == false 일 때 실행
        return (-1);   //삽입에 실패한 경우
    }
    return (0);//정상처리 된 경우 +1
}

static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu) {
#define COMPARE ( ((* pList->compare) (pArgu, (*pLoc)->dataptr)) )
#define COMPARE_LAST  ((* pList->compare) (pArgu, pList->rear->dataptr))
    int result;
    *pPre = NULL;
    *pLoc = pList->head;
    if (pList->count == 0) {
        return false;   //list가 비어있는 경우 fals
    }
    else if(COMPARE < 0){   //내가 추가한 case
        *pPre = NULL;
        *pLoc = pList->head;
        return false;
    }

    else if (COMPARE_LAST > 0) {
        *pPre = pList->rear;
        *pLoc = NULL;
        return false;   //최대값 보다 큰 경우 false
    }
    while ((result = COMPARE) > 0) {
        *pPre = *pLoc;
        *pLoc = (*pLoc)->link;  //  하나씩 옮겨가면서 비교
    }
    if (result == 0) {
        return true;    //  똑같은 값을 찾았을 경우 true
    }
    else {//이때는 비교함수의 return값이 -1이라는 거니깐 
        return false;   //결국 똑같은 값을 찾지 못했다면 false
    }                      //그리고 pPre,pLoc에는 넣을 자리가 저장돼 있을건데.. 
}

static bool _insert(LIST* pList, NODE* pPre, void* dataInPtr) {
    NODE* pNew;
    if (!(pNew = (NODE*)malloc(sizeof(NODE)))) {
        return false;       //자리가 없는 경우 아니면 다 삽입하여 true반환
    }
    pNew->dataptr = dataInPtr;
    pNew->link = NULL;
    if (pPre == NULL) { //젤 앞에 들어가야 하는 경우
        pNew->link = pList->head;
        pList->head = pNew;
        if (pList->count == 0) {
            pList->rear = pNew;
        }
    }
    else{
        pNew->link = pPre->link;
        pPre->link = pNew;
        if (pNew->link == NULL) {
            pList->rear = pNew;
        }
    }
    (pList->count)++;
    return true;
}

bool removeNode(LIST* pList, void* keyPtr, void** dataOutPtr) {
    bool found;
    NODE* pPre;
    NODE* pLoc;
    found = _search(pList, &pPre, &pLoc, keyPtr);
    if (found) {
        _delete(pList, pPre, pLoc, dataOutPtr);
    }
    return found;
}

static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr) {
    *dataOutPtr = pLoc->dataptr;
    if (pPre == NULL) {
        pList->head = pLoc->link;
    }
    else {
        pPre->link = pLoc->link;
    }
    if (pLoc->link == NULL) {
        pList->rear = pPre;
    }
    (pList->count)--;
    free(pLoc);
    return;
}

bool searchList(LIST* pList, void* pArgu, void** pDataOut) {
    bool found;
    NODE* pPre;
    NODE* pLoc;
    found = _search(pList, &pPre, &pLoc, pArgu);
    if (found) {
        *pDataOut = pLoc->dataptr;
    }
    else {
        *pDataOut = NULL;
    }
    return found;
}

bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr) {
    bool found;
    NODE* pPre;
    NODE* pLoc;
    found = _search(pList, &pPre, &pLoc, pArgu);
    if (found) {
        *dataOutPtr = pLoc->dataptr;
        return true;
    }
    *dataOutPtr = NULL;
    return false;
}

bool emptyList(LIST* pList) {
    return (pList->count == 0);
}
int listCount(LIST* pList) {
    return pList->count;
}
bool fullList(LIST* pList) {
    NODE* temp;
    if ((temp = (NODE*)malloc(sizeof(*(pList->head))))) {
        free(temp);
        return false;
    }
    return true;
}

bool traverse(LIST* pList, int fromWhere, void** dataPtrOut) {
    if (pList->count == 0) {
        return false;
    }
    if (fromWhere == 0) {
        pList->pos = pList->head;
        *dataPtrOut = pList->pos->dataptr;
        return true;
    }
    else {
        if (pList->pos->link == NULL) {
            return false;
        }
        else {
            pList->pos = pList->pos->link;
            *dataPtrOut = pList->pos->dataptr;
            return true;
        }
    }
}
LIST* destroyList(LIST* pList) {
    NODE* deletePtr;
    if (pList) {
        while (pList->count > 0) {
            free(pList->head->dataptr);
            deletePtr = pList->head;
            deletePtr = deletePtr->link;
            pList->count--;
            free(deletePtr);
        }
        free(pList);
    }
    return NULL;
}