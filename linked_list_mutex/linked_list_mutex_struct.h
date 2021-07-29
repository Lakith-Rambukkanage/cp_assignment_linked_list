#include <pthread.h>

#ifndef LINKED_LIST_MUTEX_STRUCT_H_INCLUDED
#define LINKED_LIST_MUTEX_STRUCT_H_INCLUDED

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct LinkedList {
    struct Node *head;
    pthread_mutex_t mutex;
} LinkedList;


LinkedList *createLinkedList(){
    LinkedList *l_list = malloc(sizeof(LinkedList));
    l_list->head = NULL;
    pthread_mutex_init(&l_list->mutex, NULL);
    return l_list;
}

int Member(LinkedList *l_list, int search_value){
    Node *curr = l_list->head;
//    printf("mem\n");

    while (curr!=NULL && curr->value<search_value)
        curr = curr->next;

    if (curr==NULL || curr->value>search_value)
        return 0;

    return 1; //found
}

int Insert(LinkedList *l_list, int value){
    Node *curr = l_list->head;
    Node *prev = NULL;
//    printf("ins\n");

    while (curr!=NULL && curr->value<value){
        prev = curr;
        curr = curr->next;
    }

    if (curr==NULL || curr->value>value){
        Node *newNode = malloc(sizeof(Node));
        newNode->value = value;
        newNode->next = curr;

        if (prev == NULL)
            l_list->head = newNode;
        else
            prev->next = newNode;

        return 1;
    }

    //already in list : current->value==value
    return 0;
}

int Delete(LinkedList *l_list, int search_value){
    Node *curr = l_list->head;
    Node *prev = NULL;
//    printf("del\n");

    while (curr!=NULL && curr->value<search_value){
        prev = curr;
        curr = curr->next;
    }

    if (curr!=NULL && curr->value ==search_value ){
        if (prev==NULL) // delete head
            l_list->head = NULL;
        else
            prev->next = curr->next;

        free(curr);
        return 1;
    }
    //value not in list
    return 0;
}



void printLinkedList(LinkedList *l_list){
    printf("Linked List: ");
    Node *temp = l_list->head;
    while (temp!=NULL){
        printf(" %d |",temp->value);
        temp = temp->next;
    }
    printf("\n");
}


#endif // LINKED_LIST_MUTEX_STRUCT_H_INCLUDED
