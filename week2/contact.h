#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 100
#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Contact;

typedef struct {
    Contact *contacts;
    int count;
    int capacity;
} ContactManager;

// Function prototypes
ContactManager* create_contact_manager(void);
void destroy_contact_manager(ContactManager *manager);
int load_contacts_from_csv(ContactManager *manager, const char *filename);
int save_contacts_to_csv(ContactManager *manager, const char *filename);
int add_contact(ContactManager *manager, const char *name, const char *phone, const char *email);
int remove_contact(ContactManager *manager, const char *name);
void search_contacts(ContactManager *manager, const char *query);
void list_all_contacts(ContactManager *manager);
void print_usage(const char *program_name);
int resize_contact_array(ContactManager *manager);
void trim_whitespace(char *str);

#endif
