
#ifndef CONTACT_H
#define CONTACT_H

// Maximum number of contacts
#define MAX_CONTACTS 50

// Structure to store a single contact
typedef struct Contact_data
{
    char Name[50];
    char Mobile_number[11];
    char Mail_ID[50];

} Contacts;

// Structure to store the complete address book
typedef struct AddressBook_Data
{
    Contacts contact_details[MAX_CONTACTS];
    int contact_count;

} AddressBook;

// Function declarations

// Add a new contact
void create_contact(AddressBook *);

// Display all contacts
void list_contacts(AddressBook *, int);

// Search for a contact
void search_contacts(AddressBook *);

// Edit an existing contact
void edit_contact(AddressBook *);

// Delete a contact
void delete_contact(AddressBook *);

#endif
