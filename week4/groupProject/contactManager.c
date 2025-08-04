#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256
#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_EMAIL 50

// Contact structure
typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;

// Display all contacts
void display_contacts(Contact *contacts, int count) {
    if (count == 0) {
        printf("\n[INFO] No contacts to display.\n");
        return;
    }

    printf("\n--- All Contacts (%d) ---\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. Name: %s | Phone: %s | Email: %s\n",
               i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

// Save contacts to a file
void save_contacts(const char *filename, Contact *contacts, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error saving contacts");
        return;
    }

    fprintf(file, "Name,Phone,Email\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(file);
    printf("[INFO] Contacts saved to '%s'\n", filename);
}

// Load contacts from file
int load_contacts(const char *filename, Contact **contacts) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("[INFO] File not found. Starting with empty contact list.\n");
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;

    fgets(line, MAX_LINE, file); // skip header

    while (fgets(line, MAX_LINE, file)) {
        Contact temp;
        if (sscanf(line, "%49[^,],%19[^,],%49[^\n]",
                   temp.name, temp.phone, temp.email) != 3) {
            continue; // skip malformed lines
        }

        Contact *resized = realloc(*contacts, (count + 1) * sizeof(Contact));
        if (!resized) {
            perror("Memory allocation failed");
            fclose(file);
            return count;
        }
        *contacts = resized;
        (*contacts)[count++] = temp;
    }

    fclose(file);
    return count;
}

// Add a new contact
void add_contact(Contact **contacts, int *count) {
    Contact new;

    printf("Enter name: ");
    scanf(" %[^\n]", new.name);
    printf("Enter phone: ");
    scanf(" %[^\n]", new.phone);
    printf("Enter email: ");
    scanf(" %[^\n]", new.email);

    Contact *resized = realloc(*contacts, (*count + 1) * sizeof(Contact));
    if (!resized) {
        perror("Memory allocation failed");
        return;
    }
    *contacts = resized;
    (*contacts)[*count] = new;
    (*count)++;

    printf("[INFO] Contact added successfully!\n");
}

// Update a contact
void update_contact(Contact *contacts, int count) {
    if (count == 0) {
        printf("[INFO] No contacts available to update.\n");
        return;
    }

    display_contacts(contacts, count);
    int index;
    printf("Enter contact number to update: ");
    scanf("%d", &index);

    if (index < 1 || index > count) {
        printf("[ERROR] Invalid contact number.\n");
        return;
    }

    index--;
    printf("Enter new name: ");
    scanf(" %[^\n]", contacts[index].name);
    printf("Enter new phone: ");
    scanf(" %[^\n]", contacts[index].phone);
    printf("Enter new email: ");
    scanf(" %[^\n]", contacts[index].email);

    printf("[INFO] Contact updated.\n");
}

// Delete a contact
void delete_contact(Contact **contacts, int *count) {
    if (*count == 0) {
        printf("[INFO] No contacts to delete.\n");
        return;
    }

    display_contacts(*contacts, *count);
    int index;
    printf("Enter contact number to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > *count) {
        printf("[ERROR] Invalid contact number.\n");
        return;
    }

    index--;
    for (int i = index; i < *count - 1; i++) {
        (*contacts)[i] = (*contacts)[i + 1];
    }

    (*count)--;
    Contact *resized = realloc(*contacts, (*count) * sizeof(Contact));
    if (resized || *count == 0) { // allow NULL if count is 0
        *contacts = resized;
    }

    printf("[INFO] Contact deleted.\n");
}

// Compare function for qsort
int compare_contacts(const void *a, const void *b) {
    const Contact *c1 = (const Contact *)a;
    const Contact *c2 = (const Contact *)b;
    return strcasecmp(c1->name, c2->name);
}

// Sort contacts alphabetically
void sort_contacts(Contact *contacts, int count) {
    if (count < 2) {
        printf("[INFO] Not enough contacts to sort.\n");
        return;
    }

    qsort(contacts, count, sizeof(Contact), compare_contacts);
    printf("[INFO] Contacts sorted alphabetically by name.\n");
}

// Search contacts by name
void search_contact(Contact *contacts, int count) {
    if (count == 0) {
        printf("[INFO] No contacts to search.\n");
        return;
    }

    char keyword[MAX_NAME];
    printf("Enter name to search: ");
    scanf(" %[^\n]", keyword);

    printf("\n--- Search Results ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasestr(contacts[i].name, keyword)) {
            printf("%d. Name: %s | Phone: %s | Email: %s\n",
                   i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
            found++;
        }
    }

    if (found == 0) {
        printf("[INFO] No contacts found with name containing '%s'.\n", keyword);
    }
}

// Main program
int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : "contacts.csv";
    Contact *contacts = NULL;
    int count = load_contacts(filename, &contacts);
    int choice;

    do {
        printf("\n==== Contact Manager ====\n");
        printf("1. Display contacts\n");
        printf("2. Add contact\n");
        printf("3. Update contact\n");
        printf("4. Delete contact\n");
        printf("5. Sort contacts alphabetically\n");
        printf("6. Search contact by name\n");
        printf("7. Save and Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: display_contacts(contacts, count); break;
            case 2: add_contact(&contacts, &count); break;
            case 3: update_contact(contacts, count); break;
            case 4: delete_contact(&contacts, &count); break;
            case 5: sort_contacts(contacts, count); break;
            case 6: search_contact(contacts, count); break;
            case 7: save_contacts(filename, contacts, count); break;
            default: printf("[ERROR] Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    free(contacts);
    return 0;
}
