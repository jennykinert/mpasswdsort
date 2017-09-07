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
list *newEmptyLinkedList(){
    list* list1 = malloc(sizeof(list));
    listSystemCheck(list1);
    list1->size=0;
    list1->next=NULL;
    return list1;
}

/**
 * Name: addValue
 * Description: Adds a new value to the list
 * @param list
 * @param ui
 */
void addValue(list *list, struct user_info *ui){
    ui->next = list->next;
    list->next = ui;
    list->size++;
}
/**
 * Name: isEmpty
 * Description: controls if the list is empty or not
 * @param: list
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
void swap(struct user_info *ui1, struct user_info *ui2){

    //Swap the usernames
    char *temp = ui1->uname;
    ui1->uname = ui2->uname;
    ui2->uname = temp;

    //Swap the UID
    unsigned int tempUID;
    tempUID = ui1->uid;
    ui1->uid = ui2->uid;
    ui2->uid = tempUID;

}

/**
 * Name: getUserInfoFromIndex
 * Description: Resturns the user info positioned at the specified index as a
 * pointer
 * @param list
 * @param index
 * @return *ui (The user info at the index)
 */
struct user_info *getUserInfoFromIndex(list *list, int index){
    struct user_info *ui = list->next;
    unsigned int temp = index;
    if(temp >= list->size){
        return NULL;
    }
    for(int i = 0; i<index ; i++){
        ui = ui->next;
    }
    return ui;
}

/**
 * Name: sortList
 * Description: Sorts the list according to the algorithm bubblesort
 * @param list
 */
void sortList(list *list){
    struct user_info *first= list->next;

    while(first != NULL ){
        struct user_info *second = first->next;
        while(second != NULL){
            if(first->uid > second->uid){
                swap(first, second);
            }
            second = second->next;
        }
        first=first->next;
    }
/**int size = sizeOfList(list);

    int i,j;

    for(i = 0; i < size; i++){
        for(j = 0; j<size-1; j++){
            struct user_info *first = getUserInfoFromIndex(list, j);
            struct user_info *second = getUserInfoFromIndex(list,j+1);
            if(first->uid > second->uid){
                swap(first,second);
            }
        }
    }**/
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






