#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    struct node* next;
    void* dataptr;
} QUEUE_NODE;

typedef struct queue{
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
    int count;
} QUEUE;

QUEUE* creatQueue(void){
    QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
    if(queue){
        queue->count = 0;
        queue->front = NULL;
        queue->rear = NULL;
    }
    return queue;
}
QUEUE* destroyQueue(QUEUE* queue){
    QUEUE_NODE* node_to_delete;
    if(queue){
        while(queue->count > 0){
            free(queue->front->dataptr);
            node_to_delete = queue->front;
            queue->front = queue->front->next;
            (queue->count)--;
        }
        free(queue);
    }
    return NULL;
}
bool enqueue(QUEUE* queue, void* itemptr){
    QUEUE_NODE* newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
    if(!newnode){
        return false;
    }else{
        newnode->dataptr = itemptr;
        newnode->next = NULL;
        if(queue->count == 0){
            queue->front = queue->rear = newnode;
        }else{
            queue->rear->next = newnode;
            queue->rear = newnode;
        }
        (queue->count)++;
        return true;
    }
}
bool dequeue(QUEUE* queue, void** itemptr){
    QUEUE_NODE* node_to_delete;
    if(queue->count == 0){
        return false;
    }
    else{
        *itemptr = queue->front->dataptr;       //사실상 이게 return 하고자하는 것.
        node_to_delete = queue->front;
        if(queue->count == 1){
            queue->front = queue->rear = NULL;
        }else{
            queue->front = queue->front->next;
        }
        (queue->count)--;
        free(node_to_delete);

        return true;
    }
}
bool queueFront(QUEUE* queue, void** itemptr){
    if(queue->count == 0){
        return false;
    }
    else{
        *itemptr = queue->front->dataptr;
        return true;
    }
}
bool queueRear(QUEUE* queue, void** itemptr){
    if(queue->count == 0){
        return false;
    }else{
        *itemptr = queue->rear->dataptr;
        return true;
    }
}
int queueCount(QUEUE* queue){
    return queue->count;
}

bool emptyQueue(QUEUE* queue){
    return (queue->count == 0);
}
bool fullQueue(QUEUE* queue){
    QUEUE_NODE* temp = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE)); //WHAT I WANT TO ASK!!!!!!!!!!!!!!***********
    if(temp){                                                   //Acturally It works well too, but textbooks's cord is little different with me
        free(temp);
        return true;
    }
    return false;
}
void printQueue(QUEUE* queue){
    if(queue->count == 0){
        printf("No Queue_Node there\n");
    }
    while((queue->count) > 0){
        printf("%d  ",*(int*)(queue->front->dataptr));
        queue->front = queue->front->next;
        (queue->count)--;
    }
    printf("\n");
}
