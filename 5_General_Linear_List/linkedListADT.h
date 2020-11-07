#include <stdio.h>

typedef struct node{
    void* dataptr;
    struct node* link;
}   NODE;
typedef struct{
    int count;
    NODE* pos;
    NODE* head;
    NODE* rear;
    int (*compare) (void* argu1, void* argu2);   //compare function pointer
} LIST;

LIST* createList (int (*compare)(void* argu1, void* argu2));
LIST* destroyList (LIST* list);
int addNode (LIST* pList, void* dataInPtr);
bool removeNode(LIST* pList, void* pArgu, void** pDataOut);
bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr);
bool traverse (LIST* pList, int fromWhere, void** dataOutPtr);
int listCount (LIST* pList);
bool emptyList(LIST* pList);
bool fullList(LIST* pList);

static int _insert(LIST* pList, NODE* pPre, void* dataInPtr);
static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr);
static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);

LIST* createList (int (*compare)(void* argu1, void* argu2)){
    LIST* list;
    list = (LIST*)malloc(sizeof(LIST));
    if(list){
        list->head = NULL;
        list->pos = NULL;
        list->rear = NULL;
        list->count = 0;
        list->compare = compare;
    }
    return list;
}
static bool _insert(LIST* pList, NODE* pPre, void* dataInPtr){
    NODE* pNew;
    if(!(pNew = (NODE*)malloc(sizeof(NODE)))){
        return false ; 
    }
    pNew->dataptr = dataInPtr;
    pNew->link = NULL;
    if(pPre = NULL){
        pNew->link = pList->head;
        pList->head = pNew;
        if(pList->count == 0){
            pList->rear = pNew;
        }
    }
    else{
        pNew->link = pPre->link;
        pPre->link = pNew;
        if(pNew->link == NULL){
            pList->rear = pNew;
        }
    }
    (pList->count)++;
    return true;
}
bool removeNode(LIST* pList, void* keyPtr, void** dataOutPtr){
    bool found;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, keyPtr);
    if(found){
        _delete(pList, pPre, pLoc, dataOutPtr);
    }
    return found;
}
void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr){
    *dataOutPtr = pLoc->dataptr;
    if(pPre == NULL){
        pList->head = pLoc->link;
    }
    else{
        pPre->link = pLoc->link;
    }
    if(pLoc->link = NULL){
        pList->rear = pPre;
    }
    (pList->count)--;
    free(pLoc);
    return;
}
bool searchList(LIST* pList, void* pArgu, void** pDataOut){
    bool found;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, pArgu);
    if(found){
        *pDataOut = pLoc->dataptr;
    }
    else{
        *pDataOut = NULL;
    }
    return found;
}
bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu){
    #define COMPARE ( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )
    #define COMPARE_LAST  ((* pList->compare) (pArgu, pList->rear->dataPtr))
    int result;
    *pPre = NULL;
    *pLoc = pList->head;
    if(pList->count == 0){
        return false;
    }
    if(COMPARE_LAST > 0){
        *pPre = pList->rear;
        *pLoc = NULL;
        return false;
    }
    while((result = COMPARE) > 0){
        *pPre = *pLoc;
        *pLoc = (*pLoc)->link;
    }
    if(result == 0){
        return true;
    }
    else{
        return false;
    }
}
static bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr){
    bool found;
    NODE* pPre;
    NODE* pLoc;
    found = _search(pList, &pPre, &pLoc, pArgu);
    if(found){
        *dataOutPtr = pLoc->dataptr;
        return true;
    }
    *dataOutPtr = NULL;
    return false;
}
bool emptyList(LIST* pList){
    return (pList->count == 0);
}
int listCount(LIST* pList){
    return pList->count;
}
bool fullList(LIST* pList){
    NODE* temp;
    if((temp = (NODE*)malloc(sizeof(*(pList->head))))){
        free(temp);
        return false;
    }
    return true;
}
bool traverse(LIST* pList, int fromWhere, void**dataPtrOut){
    if(pList->count == 0){
        return false;
    }
    if(fromwhere == 0){
        pList->pos = pList->head;
        *dataPtrOut = pList->pos->dataptr;
        return true;
    }
    else{
        if(pList->pos->link == NULL){
            return false;
        }
        else{
            pList->pos = pList->pos->link;
            *dataPtrOut = pList->pos->dataptr;
            return true;
        }
    }
}
LIST* destroyList(LIST* pList){
    NODE* deletePtr;
    if(pList){
        while(pList->count > 0){
            free(pList->head->dataptr);
            deletePtr = pList->head;
            pList->head = pList->head->link;
            pList->count--;
            free(deletePtr);
        }
        free(pList);
    }
    return NULL;
}