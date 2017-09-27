//
// Created by Jenny on 2017-07-27.
//

#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include <stdbool.h>

/**
 * Name: node
 * Description: struct for the nodes to be placed in the list. Every node
 * contain data and a pointer to the next node
 * @param data (data to hold in list)
 * @param next (next node in list)
 */
typedef struct node{void *data; struct node *next;} node;

/**
 * Name: c
 * Description: typedef for compare function to be sent to the list when
 * creating it.
 * @param data (nodes to be compared in function)
 */
typedef bool c(node *data1 , node *data2);
/**
 * Name: list
 * Description: This is the head of the list. which keep track of the list size
 * and the first element of the list
 * @param size (the number of elements in the list)
 * @parm next (pointer to an element in this list)
 * @param c (funktionpointer to compare function)
 */
typedef struct head{ unsigned int size; void* next; c *compare;} list;


/**
 * Function: newEmptyLinkedList
 * Description: Creates a new empty linked list
 * @return: Pointer to the List
 */
list *newEmptyLinkedList(c *comp);

/**
 * Name: addValue
 * Description: Adds a new value to the list
 * @param list
 * @param node
 */
void addValue(list *list, node *node);

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
void swap(node *element1, node *element2);

/**
 * Name: getNodeFromIndex
 * Description: Resturns the Node positioned at the specified index
 * @param list
 * @param index
 * @return
 */
node *getNodeFromIndex(list *list, int index);

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

