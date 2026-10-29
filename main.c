/*
Project Name : Address Book
Name         : Sanjay Hibare
Date         : 17/06/2026

Description  : Address Book is a digital version of a telephone directory.
               In a traditional telephone directory, searching, editing,
               and managing contacts is difficult and time-consuming.
               To overcome these limitations, we developed this project.

               This project allows the user to add, search, edit, delete,
               display, and save contact details efficiently.

               Functions Used :

               1. void create_contact(AddressBook *)
                  -> This function is used to create a new contact.
                     The user enters Name, Mobile Number, and Email ID.
                     After validating all details, the contact is stored
                     successfully in the Address Book.

               2. void list_contacts(AddressBook *)
                  -> This function displays all stored contacts.
                     Contacts can be viewed and sorted by Name,
                     Mobile Number, or Email ID.

               3. void search_contacts(AddressBook *)
                  -> This function is used to search for a contact.
                     The user can search using:
                     - Name
                     - Mobile Number
                     - Email ID

               4. void edit_contact(AddressBook *)
                  -> This function is used to modify existing contact
                     details. First, a contact is searched. Once found,
                     the user can edit:
                     - Name
                     - Mobile Number
                     - Email ID
                     - All Fields

               5. void delete_contact(AddressBook *)
                  -> This function is used to remove a contact from the
                     Address Book. First, the contact is searched and
                     then deleted using Name, Mobile Number, or Email ID.

               6. void save_contactsinfile(AddressBook *)
                  -> This function saves all contact information into
                     a file so that the data remains available even
                     after the program is closed.

               7. void loadContactsFromFile(AddressBook *)
                  -> This function loads previously saved contacts from
                     the file when the program starts.
*/

#include <stdio.h>     // Contains input/output functions like printf() and scanf()
#include "contact.h"   // Contains contact-related function declarations
#include "file.h"      // Contains file handling function declarations
#include <unistd.h>    // Contains system functions like usleep()

int main()
{
    int option;  // Stores user's menu choice

    // Create AddressBook structure variable
    AddressBook addressbook;

    // Initially no contacts are present
    addressbook.contact_count = 0;

    // Load all previously saved contacts from file
    loadContactsFromFile(&addressbook);

    // Infinite loop to keep showing menu until user exits
    while (1)
    {
        // Display main menu
        printf("\n------------------------------------------------Address book menu------------------------------------------------\n\n");

        printf("\n1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display/list contact\n6.Save\n7.Exit\n");

        printf("\n------------------------");
        printf("\nEnter the option");
        printf("\n------------------------\n");

        // Read user choice
        scanf("%d", &option);

        // Execute selected option
        switch (option)
        {
        case 1:
        {
            // Add a new contact
            create_contact(&addressbook);
            break;
        }

        case 2:
        {
            // Display search menu
            printf("\nSearch Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n\n");

            // Search contact using selected option
            search_contacts(&addressbook);
            break;
        }

        case 3:
        {
            // Display edit menu
            printf("\nEdit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n\n");

            // Edit existing contact
            edit_contact(&addressbook);
            break;
        }

        case 4:
        {
            // Display delete menu
            printf("\nDelete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n\n");

            // Delete selected contact
            delete_contact(&addressbook);
            break;
        }

        case 5:
        {
            // Display all stored contacts
            printf("\nList Contacts:");

            list_contacts(&addressbook, 1);
            break;
        }

        case 6:
        {
            // Save all contacts into file
            printf("\nSave contact :");

            save_contactsinfile(&addressbook);
            break;
        }

        case 7:
        {
            // Save contacts before exiting
            save_contactsinfile(&addressbook);
            void loading(void);
            loading();
            printf("Exiting...!\n");

            // Terminate program
            return 0;
        }

        default:
        {
            // Execute when user enters invalid option
            printf("\nInvalid option \n");
            break;
        }
        }
    }

    return 0; // Indicates successful program execution
}