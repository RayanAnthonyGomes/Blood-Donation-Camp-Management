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
struct Action {
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

const char* bloodGroups[] = {"A+","A-","B+","B-","AB+","AB-","O+","O-"}; //blood groups er array
int BG_COUNT = 8; //total blood groups er count 8 ta

//Register kora donor der list
int countList() {
    int c = 0;
    struct Donor* t = donorList;
    while (t) { c++; t = t->next; }
    return c;
}

//undo stack er push  to undo stack-> action type ar donor details duitia copy kore
void push(char type[], struct Donor* d) {
    if (top < STACKSIZE-1) { 
        top++;
        strcpy(stack[top].type, type);
        stack[top].donor = *d;
    }
}

struct Action pop() { //last action ta undo stack theke pop kore 
    return stack[top--]; 
}
//Donor ke waiting queue te add kore and queue full thakle ignore kore
void enqueue(char name[], char bg[], char contact[]) {
    if (rear == QUEUESIZE-1) {
        return;}
    if (front == -1) {
        front = 0;
        rear++;
    }
    strcpy(waitQueue[rear].name, name);
    strcpy(waitQueue[rear].bg, bg);
    strcpy(waitQueue[rear].contact, contact);
}
//First donor ta re remove kore waiting list theke, ekei sathe store kore pointer W e. Jodi queue empty thake tahole return 0 kore.
int dequeue(struct waitEntry* w) {
    if (front == -1 || front > rear){ 
        return 0; //Queueu empty check kortesi
    }else{
        *w = waitQueue[front++];
    }
    return 1;
}



