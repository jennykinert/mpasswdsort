#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
/**
 * <mpasswdsort.c>
 * <Jenny><Kinert>
 * Laboration <1> <systemnära programmering> <HT2017>
 * Frågor kring filkontrollen. Kan man anta att kolona är där även om fältet är tomt?
 * @return
 */
bool controlLine(char *Buffer, int lineCounter);
FILE *openFile(int argc, char **argv);
struct user_info *extractUIFromBuffer(char buffer[]);
void systemCheck(void *memory);
void freeListItems(list *ls);


int main(int argc, char** argv ) {
    list *ls = newEmptyLinkedList();
    struct user_info *ui;
    char buffer[1023];
    int lineCounter=0;
    bool endWithExit = false;

    FILE *fp;
    // This option if no file is attached to program
    if(argc == 1)
    {
        fp = stdin;
        //printf ("\nEnter string below, finish with [ctrl + d]\n");
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
            addValue(ls, ui);
        }
        else {
            endWithExit = true;
        }
    }
    sortList(ls);
    for(int i = 0; i<sizeOfList(ls); i++){
        ui = getUserInfoFromIndex(ls, i);
        //unsigned int uid = ui->uid;
        //char *uname = malloc(sizeof(ui->uname));
        //uname = ui->uname;
        //printf("%d:%s\n", uid,ui->uname);
    }
    fclose(fp);
    freeListItems(ls);
    free(ls);
    if(endWithExit){
        exit(EXIT_FAILURE);
    }
    return 0;
}

/**
 * Name: extractUIFromBuffer
 * Description: Here the UID and uname information is extracted from the rest
 * of the file information.
 * @param Buffer
 * @return user_info (information to insert in the list)
 */
struct user_info *extractUIFromBuffer(char buffer[]){
    struct user_info *ui = malloc(sizeof(struct user_info));
    systemCheck(ui);
    int coloncounter = 0;
    int secondColon = 0;
    int max = (int)strlen(buffer);
    for(int i=0; i<= max ;i++ ){
        if(buffer[i] == ':' && coloncounter == 0){
            char *tempUname = (char *)malloc(1023);
            systemCheck(tempUname);
            strncpy(tempUname,buffer, i);
            ui->uname = tempUname;
            printf("%s",tempUname);
            coloncounter ++;
        }
        else if(buffer[i] == ':' && coloncounter == 2){
            char *tempUID = (char *)malloc(i-secondColon);
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
        fprintf(stderr, "%s\n", "Couldn't open file");
        exit(EXIT_FAILURE);
    }
    //Kan inte ha den här kollen då den första raden försvinner
    /**char buffer[BUFSIZ];
    fgets(buffer, 1024,fp);
    if(buffer == NULL){
        fprintf(stderr, "%s\n", "Failed to read file");
        fprintf(stderr, "%s\n", "Best guess is that file was empty!");
        exit(EXIT_FAILURE);
    }**/
    return fp;
}

/**
 * Name: control Line
 * Description: Controls if the line is missing any fields or is written in the
 * wrong format.
 * @param buffer
 * @return bool (variable to now if something in the format is wrong)
 */
bool controlLine(char buffer[], int lineCounter){
    int bufferLenght = (int) strlen(buffer);
    char buffercpy[100];
    int colonCounter=0;
    int lastColonPosition=0;
    bool control = false;

    for(int i=0; i<=bufferLenght; i++ ){
        memset(buffercpy, '\0', sizeof(buffercpy));
        if(buffer[i]==':'){
            colonCounter ++;
            strncpy(buffercpy,buffer+lastColonPosition, (size_t)
                    (i - lastColonPosition));
            lastColonPosition=i;
            switch(colonCounter){
                case 1:
                    if(strlen(buffercpy)== 0){
                        fprintf(stderr,"Line %d: %s",lineCounter, "The username"
                                "cannot be empty \n");
                        return control = true;
                    }
                    else if(strlen(buffercpy)>32){
                        fprintf(stderr,"Line %d %s",lineCounter, "The username"
                                "cannot be longer than 32 letters\n");
                        return control = true;
                    }
                    break;
                case 3:
                    if(strlen(buffercpy)== 1){
                        fprintf(stderr,"Line %d: %s",lineCounter, "the UID "
                                "cannot be empty \n");
                        return control = true;
                    }
                    else if(buffercpy[1]=='-'){
                        fprintf(stderr,"Line %d: %s",lineCounter, "the UID "
                                "cannot be negative \n");
                        return control = true;
                        }
                    break;
                case 4:
                    if(strlen(buffercpy)== 1){
                        fprintf(stderr,"Line %d: %s",lineCounter, "the GID "
                                "cannot be empty \n");
                        return control = true;
                    }
                    int lengthOfCpy = (int)strlen(buffercpy);
                    for(int i =1; i<lengthOfCpy; i++){
                        int digit = buffercpy[i];
                        if(!isdigit(digit)){
                            fprintf(stderr,"Line %d: %s",lineCounter, "the GID "
                                    "is not a number \n");
                            return control = true;
                        }
                    }
                    break;
                case 6:
                    if(strlen(buffercpy)== 1){
                        fprintf(stderr,"Line %d: %s",lineCounter, "the "
                                "directory cannot be empty \n");
                        return control = true;
                    }
                    break;
                default:break;
            }
        }
    }
    if(colonCounter == 0 || colonCounter!=6 ){
        fprintf(stderr,"Line %d: %s",lineCounter,"The format of "
                "line is wrong\n");
        return control = true;
    }
    else{
        return control;
    }
}

void systemCheck(void *memory){
    if(memory==NULL){
        fprintf(stderr, "%s\n", "Something went wrong when allocating memory!");
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
        struct user_info *ui = ls->next;
        struct user_info *tempUI = ui->next;
        free(ui->uname);
        free(ui);
        ls->next = tempUI;
    }
}