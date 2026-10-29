#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>
#include <string.h>

// Maximum number of contacts that can be stored
#define MAX_CONTACTS 50

// Structure to store details of a single contact
typedef struct Contact_data
{
    // Stores contact name
    char Name[50];

    // Stores mobile number (10 digits + null character)
    char Mobile_number[11];

    // Stores email address
    char Mail_ID[50];

} Contacts;

// Structure to store complete address book data
typedef struct AddressBook_Data
{
    // Array of structures to store all contacts
    Contacts contact_details[MAX_CONTACTS];

    // Variable used to keep track of total contacts present
    int contact_count;

} AddressBook;

/* Function Declarations */

// Function to create and add a new contact
void create_contact(AddressBook *);

// Function to display all contacts
// sortCriteria decides sorting based on
// Name, Mobile Number or Email
void list_contacts(AddressBook *, int);

// Function to search a contact
// Search can be performed using Name, Mobile or Email
void search_contacts(AddressBook *);

// Function to modify existing contact details
void edit_contact(AddressBook *);

// Function to delete a contact from address book
void delete_contact(AddressBook *);

#endif