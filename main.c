//Library files gula add kortesi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//COnsstant function gula define kortesi
#define MAX_SLOTS 5               
#define STACKSIZE 20             
#define QUEUESIZE 20    

//Donor er structure define kortesi
struct Donor {
    int id;
    char name[50], bloodgroup[4], contact[20];
    struct Donor* next;
};

//Donor er action gula define kortesi
        struct selectedAction {
    char type[10]; // "REGISTRATION" naki "CANCEL"
    struct Donor donor;
};

//Waiting list er structure define kortesi
        struct waitEntry {
    char name[50], bg[4], contact[20];
};

//Initial stage e top, front, rear egula linked list er jonno
struct Donor* donorList = NULL;  // linked list er head
struct Action stack[STACKSIZE]; // Undo er option er jonno stack
struct waitEntry waitQueue[QUEUESIZE]; // Waiting list queue
int top = -1, front = -1, rear = -1, nextId = 1;

const char* bloodGroups[] = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};
int BG_COUNT = 8;
