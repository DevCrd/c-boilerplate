#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct {
    char name[50];
    char phone[15];
} Contact;



int main(void) {
    
    Contact contacts[10] = {
        { "Alice Johnson",   "555-1234" },
        { "Bob Smith",       "555-2345" },
        { "Carol Martinez",  "555-3456" },
        { "Dave Thompson",   "555-4567" },
        { "Eve Nguyen",      "555-5678" }
    };
    
    int contact_count = 5;
    
    printf("Number of contacts: %d\n\n", contact_count);
    
    
    printf("Current contacts:\n");
    
    for (int i = 0; i < contact_count; i++) {
        printf("%d. %s %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
    
    // // Add new contact
    if (contact_count < 10) {

        printf("\nAdding a new contact:\n");
        
        printf("Enter name: ");
        
        fgets(contacts[contact_count].name, sizeof(contacts[contact_count].name), stdin);
        
        
        printf("Enter phone: ");
        fgets(contacts[contact_count].phone, sizeof(contacts[contact_count].phone), stdin);

        contact_count++;
        

        for (int i = 0; i < contact_count; i++) {

            printf("%d. %s %s\n", i + 1, contacts[i].name, contacts[i].phone);
        }


    } else {
        printf("\nContact list is full!\n");
    }
    
    return 0;
}

// typedef struct
// {
//     char name[50];
//     char phone[10];
// } Contact;

// int search (void)
// {
//         Contact contacts[5] = {
//         { "Alice Johnson",   "555-1234" },
//         { "Bob Smith",       "555-2345" },
//         { "Carol Martinez",  "555-3456" },
//         { "Dave Thompson",   "555-4567" },
//         { "Eve Nguyen",      "555-5678" }
//     };

//     int size = sizeof(contacts) / sizeof(Contact);
//     for(int i = 0; i < size; i++ ){
//         printf("  name %s  number  %s \n", contacts[i].name , contacts[i].phone);
//     }
//     printf("\n");
//     //Print each member of the above array
//     return 0;
// }




int box(int argc , char *argv[]){
    int target = atoi(argv[1]);

    for(int i= 0; i<target; i++){
        // int number = target * i;
        // if(target = i ){
            
        // }
        printf("%i",i);
        printf("####\n");
        if(argv[2]){

        }   

    }
    return 0;
}



int search(int argc , char *argv[])
{

    if(argc < 2){

        printf("Improper usage, argument expects a number e.g ./classfix 10 \n");
        return 1;
    };
    int data[] = {10, 20, 30, 40, 50};
    int found = -1;
    int target = atoi(argv[1]);
    int size = sizeof(data) / sizeof(data[0]);

    
    for(int i = 0; i < size ; i++){

        if(data[i] == target) {
            found = 1;
                printf("Number %d found at index %d\n", target, i);

            break;
        }

    }
   // Print the index of a number if found
    if(found == -1)
        printf("Number %d  not found \n", target);

    return 0;
}