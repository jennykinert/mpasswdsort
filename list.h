//
// Created by Jenny on 2017-07-27.
//

#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include <stdbool.h>

//typedef struct head{ unsigned int size; struct user_info *next;} list;
typedef struct head{ unsigned int size; void* next;} list;


//struct user_info{ unsigned int uid; char* uname; struct user_info *next;};

struct user_info{ unsigned int uid; char* uname; void* next;};

/**
 * Function: newEmptyLinkedList
 * Description: Creates a new empty linked list
 * @return: Pointer to the List
 */
list *newEmptyLinkedList();

/**
 * Name: addValue
 * Description: Adds a new value to the list
 * @param list
 * @param ui
 */
void addValue(list *list, struct user_info *ui);

/**
 * Name: isEmpty
 * Description: controls if the list is empty or not
 * @param: list
 * @return: boolean
 */
bool isEmpty(list *list);

/**
 * Name: sizeOfList
 * Description: Controls the size of the list and return the value
 * @param list
 * @return size
 */
int sizeOfList(list *list);

/**
 * Name: swap
 * Description: Function to help swapping elements when sorting the list with
 * bubblesort
 * @param list
 */
void swap(struct user_info *ui1, struct user_info *ui2);

/**
 * Name: getUserInfoFromIndex
 * Description: Resturns the user info positioned at the specified index
 * @param list
 * @param index
 * @return
 */
struct user_info *getUserInfoFromIndex(list *list, int index);

/**
 * Name: sortList
 * Description: Sorts the list according to the algorithm bubble sort
 * @param list
 */
void sortList(list *list);

/**
* Name: systemmCheck
* This function is only part of the implementation
* and not of the interface.
*/
void listSystemCheck(void *memory);


#endif //LINKEDLIST_LIST_H

