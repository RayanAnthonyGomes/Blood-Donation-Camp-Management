//Library files gula add kortesi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//COnsstant function gula define kortesi
#define MAX_SLOTS 5               
#define STACK_SIZE 20             
#define QUEUE_SIZE 20    

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
int top = -1, front = -1, rear = -1, nextId = 1;

