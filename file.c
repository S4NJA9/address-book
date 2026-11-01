
#include <stdio.h>
#include <string.h>
#include "file.h"

// Function to save all contacts into a file
void save_contactsinfile(AddressBook *addressbook)
{
    FILE *fp;

    // Check whether AddressBook is valid
    if (addressbook == NULL)
    {
        printf("Invalid address book\n");
        return;
    }

    // Check contact count
    if (addressbook->contact_count < 0 ||
        addressbook->contact_count > MAX_CONTACTS)
    {
        printf("Invalid contact count\n");
        return;
    }

    // Open file in write mode
    // Old data will be overwritten
    fp = fopen("contacts.csv", "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    // Save total number of contacts
    fprintf(fp, "#%d\n", addressbook->contact_count);

    // Save all contact details
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    // Close file
    fclose(fp);

    printf("\nContacts Saved Successfully\n");
}


// Function to load contacts from file
void loadContactsFromFile(AddressBook *addressbook)
{
    FILE *fp;
    int count;

    // Check whether AddressBook is valid
    if (addressbook == NULL)
    {
        return;
    }

    // Initialize contact count
    addressbook->contact_count = 0;

    // Open file in read mode
    fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        // File may not exist during the first execution
        printf("No saved contacts found\n");
        return;
    }

    // Read total number of contacts
    if (fscanf(fp, "#%d", &count) != 1)
    {
        printf("Invalid contact file\n");
        fclose(fp);
        return;
    }

    // Check whether count is within the allowed limit
    if (count < 0 || count > MAX_CONTACTS)
    {
        printf("Invalid contact count in file\n");
        fclose(fp);
        return;
    }

    // Read contacts one by one
    for (int i = 0; i < count; i++)
    {
        if (fscanf(fp,
                   " %49[^,],%10[^,],%49[^\n]",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID) != 3)
        {
            // Stop loading if file data is incomplete or invalid
            printf("Warning: Invalid contact data found\n");
            break;
        }

        // Update count only after successfully reading a contact
        addressbook->contact_count++;
    }

    // Close file
    fclose(fp);

    printf("%d Contacts Loaded Successfully\n",
           addressbook->contact_count);
}
