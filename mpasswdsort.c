#include "mpasswdsort.h"
#define MAXSIZE 1023
/**
 * <mpasswdsort.c>
 * <Jenny><Kinert>
 * Laboration <1> <systemnära programmering> <HT2017>
 * @return
 */


int main(int argc, char** argv ) {

    //some variable declarations
    FILE *fp;
    struct userInfo *ui;
    int lineCounter=0;
    bool endWithExit = false;
    char *buffer = malloc(MAXSIZE);
    systemCheck(buffer);


    //list *ls = newEmptyLinkedList();
    list *ls = newEmptyLinkedList(comparefunc);
    // This option if no file is attached to program
    if(argc == 1)
    {
        fp = stdin;
    }

    //This option if a file is attached to program
    else if(argc == 2)
    {
        fp = openFile(argc,argv);
    }

    //This if more than two arguments is passed to the program
    else
    {
        fprintf(stderr, "To many arguments where passed to program \n");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, 1024, fp)!=NULL) {
        lineCounter++;
        bool control = controlLine(buffer, lineCounter);
        if (control == false) {
            ui = extractUIFromBuffer(buffer);
            node *myNode = calloc(1,sizeof(node));
            systemCheck(myNode);
            myNode->data = ui;
            addValue(ls, myNode);
        }
        else {
            endWithExit = true;
        }
    }
    sortList(ls);
    for(int i = 0; i<sizeOfList(ls); i++){
        node *tempNode = getNodeFromIndex(ls, i);
        ui = tempNode->data;
        printf("%d:%s\n", ui->uid,ui->uname);
    }
    fclose(fp);
    free(buffer);
    freeListItems(ls);
    free(ls);
    if(endWithExit){
        exit(EXIT_FAILURE);
    }
    return 0;
}
/**
 * Name: comparefunc
 * Description: Compare function to be send to the list for comparing elements
 * in the list.
 * @param element1
 * @param element2
 * @return
 */
bool comparefunc(node *element1, node *element2){
    bool compareVariable = false;
    struct userInfo *ui1;
    struct userInfo *ui2;
    ui1=element1->data;
    ui2 = element2->data;
    if(ui1->uid > ui2->uid){
        return compareVariable = true;
    }
    else{
        return compareVariable;
    }
}

/**
 * Name: extractUIFromBuffer
 * Description: Here the UID and uname information is extracted from the rest
 * of the file information.
 * @param Buffer
 * @return user_info (information to insert in the list)
 */
struct userInfo *extractUIFromBuffer(char *buffer){
    struct userInfo *ui = malloc(sizeof(struct userInfo));
    systemCheck(ui);
    int coloncounter = 0;
    int secondColon = 0;
    int max = (int)strlen(buffer);

    for(int i=0; i<= max ;i++ ){
        if(buffer[i] == ':' && coloncounter == 0){
            char *tempUname = malloc(MAXSIZE);
            systemCheck(tempUname);
            strncpy(tempUname,buffer, i);
            tempUname[i]='\0';
            ui->uname = tempUname;
            coloncounter ++;
        }
        else if(buffer[i] == ':' && coloncounter == 2){
            char *tempUID = malloc(i-secondColon);
            systemCheck(tempUID);
            strncpy(tempUID,buffer+secondColon+1, i - secondColon-1);
            tempUID[i-secondColon-1]='\0';
            int temp = atoi(tempUID);
            ui->uid=temp;
            free(tempUID);
            coloncounter ++;
        }

        else if(buffer[i] == ':'){
            if(coloncounter == 1) {
                secondColon = i;
            }
            coloncounter ++;
        }
    }
    return ui;
}
/**
 * Name: openfile
 * Description: Open a textfile and control if the textfile is possible to open,
 * failed to read or might be empty.
 * @return fp (pointer to the file)
 */
FILE *openFile(int argc, char **argv){
    FILE *fp;
    fp = fopen(argv[argc-1],"r");
    if(fp==NULL){
        perror("Error in mpasswdsort openFile: ");
        exit(EXIT_FAILURE);
    }
    return fp;
}

/**
 * Name: getDataFields
 * Description: Extract the fields of file passwd into an matrix
 * @param buffer
 * @return (the matrix with data)
 */
char **getDataFields(char *buffer){
    char **dataFields = calloc(8, sizeof(char*));
    systemCheck(dataFields);
    int bufferLength = (int)strlen(buffer);
    int lastcolonposition = 0;
    int colonCounter = 0;
    for(int i =0; i<bufferLength;i++){
        if(buffer[i]==':'){
            char *parameter = calloc(100, sizeof(char));
            systemCheck(parameter);
            strncpy(parameter,buffer+lastcolonposition,(size_t)(i-lastcolonposition));
            lastcolonposition=i;
            dataFields[colonCounter] = parameter;
            colonCounter++;
        }
    }
    if(colonCounter == 0 || colonCounter!=6 ){
        dataFields[0] = 0;
    }
    return dataFields;
}
/**
 * Name: controlLine
 * Description: controls the format of the lines. If something departs message
 * is written on stderr
 * @param buffer
 * @param lineCounter
 * @return
 */
bool controlLine(char *buffer, int lineCounter){
    bool control = false;
    char **dataFields = getDataFields(buffer);
    int numberOfFields = (int)sizeof(dataFields);

    if(dataFields[0]==0){
        fprintf(stderr,"Line %d: %s",lineCounter,"The format of "
                "line is wrong\n");
        control = true;
    }
    for(int i =0; i<numberOfFields; i++){
        if(i==0|| i==2 || i==3 ){
            control = controlIfEmpty(dataFields[i]);
            if(control){
                const char *typeOfField = getFieldName(i);
                fprintf(stderr,"Line %d: %s cannot be empty \n",lineCounter,
                        typeOfField);
                control = true;
            }
        }
        if(i == 2 || i == 3){
            control = controlIfNumber(dataFields[i]);
            if(control){
                const char *typeOfField = getFieldName(i);
                fprintf(stderr,"Line %d: %s is not a number \n",lineCounter,
                        typeOfField);
                control = true;
            }
        }
        if(i==0){
            if(strlen(dataFields[i])>32) {
                fprintf(stderr, "Line %d: The username"
                        "cannot be longer than 32 letters\n", lineCounter);
                control = true;
            }
        }
    }
    freeDataFields(dataFields);
    free(dataFields);
    return control;

}
/**
 * Name: controlIfNumber
 * Description: Controls if the field is a number or not.
 * @param parameter
 * @return
 */
bool controlIfNumber(char *parameter){
    int lengthOfCpy = (int)strlen(parameter);
    bool control = false;
    for(int i =1; i<lengthOfCpy; i++){
        int digit = parameter[i];
        if(!isdigit(digit)){
            return control = true;
        }
    }
    return control;
}
/**
 * Name: controlIfEmpty
 * Description: controls if a mandatory field is empty
 * @param parameter
 * @return
 */
bool controlIfEmpty(char *parameter){
    bool control = false;
    if(strlen(parameter) == 0){
        return control = true;
    }
    else{
        return control;
    }
}

/**
 * Helper function to get the name of fields UID GID and user name
 * @param field
 * @return
 */
const char* getFieldName(int field)
{
    switch (field)
    {
        case 0: return "User Name";
        case 2: return "UID";
        case 3: return "GID";
        default:
            return "something went wrong in getFieldName function";
    }

}

/**
 * Name: systemCheck
 * Description: A function to control if mempory was allocated for pointer.
 * @param memory
 */
void systemCheck(void *memory){
    if(memory==NULL){
        perror("Error in mpasswdsort systemCheck");
        exit(EXIT_FAILURE);
    }
}

/**
 * Name: freeListItems
 * Description: frees the memory of the lists allocated items
 * @param ls: list to be freed
 */
void freeListItems(list *ls){
    while(ls->next!=NULL){
        node *freenode = ls->next;
        struct userInfo *ui = freenode->data;
        free(ui->uname);
        node *tempNode = freenode->next;
        free(freenode->data);
        free(freenode);
        ls->next = tempNode;
    }
}

/**
 * Name: freeDataFields
 * Description: frees the memory allocated in a matrix.
 * @param dataFields (the matrix items to be freed)
 */
void freeDataFields(char **dataFields){
    int length = (int)sizeof(dataFields);
    for(int i =0; i<length; i++){
        free(dataFields[i]);
    }
}