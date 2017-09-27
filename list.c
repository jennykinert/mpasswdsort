//
// Created by Jenny on 2017-07-27.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/**
 * Name: newEmptyLinkedList
 * Description: Creates a new empty linked list
 * @return: Pointer to the List
 */
list *newEmptyLinkedList(c *comp){
    list* list1 = malloc(sizeof(list));
    listSystemCheck(list1);
    list1->size=0;
    list1->next=NULL;
    list1->compare = comp;
    return list1;
}

/**
 * Name: addValue
 * Description: Adds a new value to the list
 * @param list
 * @param ui
 */
void addValue(list *list, node *node){
    node->next = list->next;
    list->next = node;
    list->size++;
}

/**
 * Name: isEmpty
 * Description: controls if the list is empty or not
 * @param:
 * @return: boolean
 */
bool isEmpty(list *list){
    if(list->size==0){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Name: sizeOfList
 * Description: Controls the size of the list and return the value
 * @param list
 * @return size
 */
int sizeOfList(list *list){
    int size = list->size;
    return size;
}

/**
 * Name: swap
 * Description: Function to help swapping elements when sorting the list with
 * bubblesort
 * @param list
 */
void swap(node *element1, node *element2){
    void *temp = element1->data;
    element1->data = element2->data;
    element2->data=temp;
}

/**
 * Name: getNodeFromIndex
 * Description: Resturns the Node positioned at the specified index
 * @param list
 * @param index
 * @return
 */
node *getNodeFromIndex(list *list, int index){
    node *node = list->next;
    unsigned int temp = index;
    if(temp >= list->size){
        return NULL;
    }
    for(int i = 0; i<index ; i++){
        node = node->next;
    }
    return node;
}

/**
 * Name: sortList
 * Description: Sorts the list according to the algorithm bubblesort
 * @param list
 */
void sortList(list *list){
    node *first= list->next;

    while(first != NULL ){
        node *second = first->next;
        while(second != NULL){
            bool control = list->compare(first,second);
            if(control){
                swap(first, second);
            }
            second = second->next;
        }
        first=first->next;
    }
}

/**
 * This function is only part of the implementation
 * and not of the interface. Used for checking of malloc returns
 */
void listSystemCheck(void *memory){
    if(memory==NULL){
        perror("Error in list listSystemCheck: ");
        exit(EXIT_FAILURE);
    }
}






