//
// Created by Jenny on 2017-07-26.
//

#ifndef LINKEDLIST_MPASSWDSORT_H
#define LINKEDLIST_MPASSWDSORT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

/**
 * Name: controlLine
 * Description: controls the format of the lines. If something departs message
 * is written on stderr
 * @param buffer
 * @param lineCounter
 * @return (true or false if the program should exit with !=0)
 */
bool controlLine(char *buffer, int lineCounter);
/**
 * Name: extractUIFromBuffer
 * Description: Here the UID and uname information is extracted from the rest
 * of the file information.
 * @param Buffer
 * @return user_info (information to insert in the list)
 */
struct userInfo *extractUIFromBuffer(char *buffer);

/**
 * Name: getDataFields
 * Description: Extract the fields of file passwd into an matrix
 * @param buffer
 * @return (the matrix with data)
 */
char **getDataFields(char *buffer);

/**
 * Name: controlIfEmpty
 * Description: controls if a mandatory field is empty
 * @param parameter
 * @return
 */
bool controlIfEmpty(char *parameter);

/**
 * Name: controlIfNumber
 * Description: Controls if the field is a number or not.
 * @param parameter
 * @return
 */
bool controlIfNumber(char *parameter);

/**
 * Helper function to get the name of fields UID GID and user name
 * @param field
 * @return
 */
const char* getFieldName(int field);
/**
 * Name: openfile
 * Description: Open a textfile and control if the textfile is possible to open,
 * failed to read or might be empty.
 * @return fp (pointer to the file)
 */
FILE *openFile(int argc, char **argv);

/**
 * Name: freeDataFields
 * Description: frees the memory allocated in a matrix.
 * @param dataFields (the matrix items to be freed)
 */
void freeDataFields(char **dataFields);


/**
 * Name: systemCheck
 * Description: A function to control if mempory was allocated for pointer.
 * @param memory
 */
void systemCheck(void *memory);

/**
 * Name: freeListItems
 * Description: frees the memory of the lists allocated items
 * @param ls: list to be freed
 */
void freeListItems(list *ls);
#endif //LINKEDLIST_MPASSWDSORT_H

