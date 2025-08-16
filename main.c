//Library files gula add kortesi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//COnsstant function gula define kortesi
#define MAX_SLOTS 3               
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
int countList() { //Counts how many donors are currently registered, Traverses the linked list donorList and increments c until reaching NULL
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
    if (rear == QUEUESIZE-1) { // Queue full check kortesi
        return;
    }
    if (front == -1) { // Prothom entry hole front set kortesi
        front = 0;
    }
    rear++;
    strcpy(waitQueue[rear].name, name);
    strcpy(waitQueue[rear].bg, bg);
    strcpy(waitQueue[rear].contact, contact);
}

//First donor ta re remove kore waiting list theke, ekei sathe store kore pointer W e. Jodi queue empty thake tahole return 0 kore.
int dequeue(struct waitEntry* w) {
    if (front == -1 || front > rear){ 
        return 0; //Queueu empty check kortesi
    } else {
        *w = waitQueue[front++];
    }
    return 1;
}

//valid blood group check kore, jodi valid hoy tahole 1 return kore, na hole 0 return kore
int validBloodGroup(char bg[]) {
    for (int i = 0; i < BG_COUNT; i++) {
        if (strcmp(bg, bloodGroups[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerDonor(char name[], char bg[], char contact[]) {

    //validBloodGroup function call kore check kortesi
    if (!validBloodGroup(bg)) { 
        printf("Invalid BG!\n"); 
        return;
    }
    //Donor er list full thakle waiting list e add kore
    if (countList() >= MAX_SLOTS) {
        printf("Full! You Added to waiting list.\n");
        enqueue(name, bg, contact);
        return;
    }

    struct Donor* d = malloc(sizeof(struct Donor));
    d->id = nextId++;
    strcpy(d->name, name);
    strcpy(d->bloodgroup, bg);
    strcpy(d->contact, contact);
    d->next = donorList;
    donorList = d;
    push("REG", d);
    printf("Registered ID %d: %s (%s, %s)\n", d->id, d->name, d->bloodgroup, d->contact);
}

// first e donor id search kori, cancel action undo te push kortesi, more specifically "CAN", Linked list theke remove kortesi and jodi waiting list e manush thake tahole first one ta re register korai QUEUE er fifo principle use kore
void cancelDonor(int id) {
    struct Donor *t = donorList, *p = NULL;
    while (t && t->id != id) { p = t; t = t->next; }
    if (!t) { printf("Not found!\n"); return; }
    push("CAN", t);
    if (p) p->next = t->next;
    else donorList = t->next;
    free(t);
    printf("Cancelled ID %d.\n", id);
    struct waitEntry w;
    if (dequeue(&w)) registerDonor(w.name, w.bg, w.contact);
}

//Linked list er sob donor der view kortesi, jodi list empty thake tahole "No donors" print kore
void viewDonors() {
    struct Donor* t = donorList;
    if (!t) { printf("No donors.\n"); return; }
    while (t) {
        printf("ID %d: %s (%s, %s)\n", t->id, t->name, t->bloodgroup, t->contact);
        t = t->next;
    }
}

//Waiting list er sob entry gula view kortesi, jodi queue empty thake tahole "Empty" print kore
void viewWait() {
    if (front == -1 || front > rear) { 
        printf("Empty.\n"); return; 
    }
    for (int i = front; i <= rear; i++)
        printf("%s (%s, %s)\n", waitQueue[i].name, waitQueue[i].bg, waitQueue[i].contact);
}

//Undo action gula perform kortesi, jodi stack empty thake tahole "Nothing to undo" print kore
//Jodi last e reg kore cancel korbo, jodi cancel kore reg korbo
void undo() {
    if (top == -1) { printf("Nothing to undo.\n"); return; }
    struct Action a = pop();
    if (strcmp(a.type,"REG")==0)
        cancelDonor(a.donor.id);
    else if (strcmp(a.type,"CAN")==0)
        registerDonor(a.donor.name, a.donor.bloodgroup, a.donor.contact);
}

int main() {
    int choice,id;
    char name[50],bg[4],contact[20];
    while (1) {
        printf("\033[1;36m");
        printf("Blood Donation Management System\n");
        printf("Saving Lives, One Drop at a Time\n");
        printf("\033[0m");
        printf("------------------------------------\n");
        printf("1.Register as a Donor\n2.Cancel Donor \n3.View all Donors\n4.Waiting List\n5.Undo\n6.Exit\nChoice: ");
        scanf("%d",&choice);
        if (choice==1) {
            printf("Name: "); scanf("%s",name);
            printf("BG: "); scanf("%s",bg);
            printf("Contact: "); scanf("%s",contact);
            registerDonor(name,bg,contact);
        }
        else if (choice==2) {
            printf("ID: "); scanf("%d",&id);
            

        }
        else if (choice==3) {
            viewDonors();
        }
        else if (choice==4) {
            viewWait();
        }
        else if (choice==5) {
            undo();
        }
        else if (choice==6) {
            break;
            printf("Exiting Program!...\n");
        }
    }
}
