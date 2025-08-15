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

