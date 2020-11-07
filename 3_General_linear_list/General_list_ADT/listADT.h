typedef struct node{
    void* dataPtr;
    struct node* link;
} NODE;
typedef struct{
    int count;
    NODE* head;
    NODE* rear;
    NODE* pos;
    int (*compare)(void* argu1,void* argu2);
}LIST;

LIST* createList(int (*compare)(void* argu1, void* argu2));
LIST* destroyList(LIST* list);
int addNode(LIST* pList, void* dataInPtr)
bool removeNode (LIST* pList, void* keyPtr, void** dataOutPtr);