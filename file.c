#include <stdio.h>
#include <string.h>
#include "file.h"

// Function to save all contacts into a file
void save_contactsinfile(AddressBook *addressbook)
{
    FILE *fp;

    // Open file in write mode
    // If file already exists, old data will be overwritten
    if ((fp = fopen("contacts.csv", "w")) == NULL)
    {
        // Execute when file opening fails
        fprintf(stderr, "Error opening file");
        return;
    }

    // Save total number of contacts at the beginning of file
    fprintf(fp, "#%d\n", addressbook->contact_count);

    // Store all contact details into file
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    // Close file after saving data
    fclose(fp);

    printf("\nContacts Saved Successfully\n");
}

// Function to load contacts from file into AddressBook structure
void loadContactsFromFile(AddressBook *addressbook)
{
    FILE *fp;

    // Open file in read mode
    if ((fp = fopen("contacts.csv", "r")) == NULL)
    {
        // Execute when file does not exist
        fprintf(stderr, "File does not exist yet\n");
        return;
    }

    // Read total number of contacts stored in file
    if (fscanf(fp, "#%d\n", &addressbook->contact_count) != 1)
    {
        // If count cannot be read, initialize contact count to zero
        addressbook->contact_count = 0;

        fclose(fp);
        return;
    }

    // Read all contacts one by one from file
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (fscanf(fp,
                   " %[^,],%[^,],%[^\n]\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID) != 3)
        {
            // If file data is corrupted or incomplete,
            // load only valid contacts read so far
            addressbook->contact_count = i;
            break;
        }
    }

    // Close file after reading
    fclose(fp);
}