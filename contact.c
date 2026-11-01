
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "valid.h"
#include "file.h"

// Function to display loading animation
void loading(void)
{
    int i, j, space;

    for (i = 0; i <= 100; i++)
    {
        printf("\rLoading[");

        for (j = 1; j <= i / 2; j++)
            printf("-");

        for (space = i / 2; space < 50; space++)
            printf(" ");

        printf("] %3d%%", i);

        fflush(stdout);
        usleep(50000);
    }

    printf("\n");
}


// Function to create a new contact
void create_contact(AddressBook *addressbook)
{
    char name[50];
    char mobile[11];
    char email[50];
    char choice;

    int i, found;

    // Check whether address book is full
    if (addressbook == NULL || addressbook->contact_count >= MAX_CONTACTS)
    {
        printf("Address Book Full\n");
        return;
    }

    do
    {
        // Get and validate name
        do
        {
            printf("Enter Name: ");
            scanf(" %49[^\n]", name);

            if (!validname(name))
                printf("Invalid Name.\n");

        } while (!validname(name));

        // Get and validate mobile number
        do
        {
            printf("Enter Mobile: ");
            scanf("%10s", mobile);

            if (!validmobile(mobile))
                printf("Invalid Mobile Number.\n");

        } while (!validmobile(mobile));

        // Check duplicate mobile number
        while (1)
        {
            found = 0;

            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mobile_number,
                           mobile) == 0)
                {
                    found = 1;
                    break;
                }
            }

            if (found == 0)
                break;

            printf("Mobile Number Already Exists.\n");
            printf("Enter Another Mobile Number: ");
            scanf("%10s", mobile);

            if (!validmobile(mobile))
                printf("Invalid Mobile Number.\n");
        }

        // Get and validate email
        do
        {
            printf("Enter Email: ");
            scanf("%49s", email);

            if (!validemail(email))
                printf("Invalid Email.\n");

        } while (!validemail(email));

        // Check duplicate email
        while (1)
        {
            found = 0;

            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mail_ID,
                           email) == 0)
                {
                    found = 1;
                    break;
                }
            }

            if (found == 0)
                break;

            printf("Email Already Exists.\n");
            printf("Enter Another Email: ");
            scanf("%49s", email);

            if (!validemail(email))
                printf("Invalid Email.\n");
        }

        // Store contact details
        strcpy(addressbook->contact_details[addressbook->contact_count].Name,
               name);

        strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number,
               mobile);

        strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID,
               email);

        // Increase contact count
        addressbook->contact_count++;

        // Check whether user wants to add another contact
        if (addressbook->contact_count >= MAX_CONTACTS)
        {
            printf("Address Book Full\n");
            break;
        }

        do
        {
            printf("\nDo you want to enter another contact? (Y/N): ");
            scanf(" %c", &choice);

        } while (choice != 'Y' && choice != 'y' &&
                 choice != 'N' && choice != 'n');

    } while (choice == 'Y' || choice == 'y');

    loading();

    printf("\nDone! Contact Added Successfully\n");

    // Save contacts into file
    save_contactsinfile(addressbook);
}


// Function to list and sort contacts
void list_contacts(AddressBook *addressbook, int sortCriteria)
{
    int i, j;
    Contacts temp;
    int result;

    if (addressbook == NULL || addressbook->contact_count == 0)
    {
        printf("No contacts found\n");
        return;
    }

    // Check sorting option
    if (sortCriteria < 1 || sortCriteria > 3)
    {
        printf("Invalid sort option (1-3)\n");
        return;
    }

    // Bubble Sort
    for (i = 0; i < addressbook->contact_count - 1; i++)
    {
        for (j = 0; j < addressbook->contact_count - i - 1; j++)
        {
            result = 0;

            // Sort by name
            if (sortCriteria == 1)
            {
                result = strcmp(addressbook->contact_details[j].Name,
                                addressbook->contact_details[j + 1].Name);
            }

            // Sort by mobile number
            else if (sortCriteria == 2)
            {
                result = strcmp(addressbook->contact_details[j].Mobile_number,
                                addressbook->contact_details[j + 1].Mobile_number);
            }

            // Sort by email
            else if (sortCriteria == 3)
            {
                result = strcmp(addressbook->contact_details[j].Mail_ID,
                                addressbook->contact_details[j + 1].Mail_ID);
            }

            // Swap contacts
            if (result > 0)
            {
                temp = addressbook->contact_details[j];

                addressbook->contact_details[j] =
                    addressbook->contact_details[j + 1];

                addressbook->contact_details[j + 1] = temp;
            }
        }
    }

    // Display table header
    printf("\n+------+----------------------+----------------+-----------------------------+\n");
    printf("| %-4s | %-20s | %-14s | %-27s |\n",
           "No.", "Name", "Mobile", "Email");
    printf("+------+----------------------+----------------+-----------------------------+\n");

    // Display contacts
    for (i = 0; i < addressbook->contact_count; i++)
    {
        printf("| %-4d | %-20s | %-14s | %-27s |\n",
               i + 1,
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID);
    }

    printf("+------+----------------------+----------------+-----------------------------+\n");
}


// Function to search contacts
void search_contacts(AddressBook *addressbook)
{
    int choice, i;
    int found = 0;

    char name[50];
    char mobile[11];
    char email[50];

    if (addressbook == NULL || addressbook->contact_count == 0)
    {
        printf("No contacts found\n");
        return;
    }

    printf("\nSearch By:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email\n");
    printf("4. Back\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
        return;

    switch (choice)
    {
        case 1:
            printf("Enter Name: ");
            scanf(" %49[^\n]", name);
            break;

        case 2:
            printf("Enter Number: ");
            scanf("%10s", mobile);
            break;

        case 3:
            printf("Enter Email: ");
            scanf("%49s", email);
            break;

        case 4:
            return;

        default:
            printf("Invalid Choice\n");
            return;
    }

    // Display table header
    printf("\n+------+----------------------+----------------+-----------------------------+\n");
    printf("| %-4s | %-20s | %-14s | %-27s |\n",
           "No.", "Name", "Mobile", "Email");
    printf("+------+----------------------+----------------+-----------------------------+\n");

    // Search all contacts
    for (i = 0; i < addressbook->contact_count; i++)
    {
        int match = 0;

        if (choice == 1 &&
            strstr(addressbook->contact_details[i].Name, name) != NULL)
        {
            match = 1;
        }
        else if (choice == 2 &&
                 strstr(addressbook->contact_details[i].Mobile_number, mobile) != NULL)
        {
            match = 1;
        }
        else if (choice == 3 &&
                 strstr(addressbook->contact_details[i].Mail_ID, email) != NULL)
        {
            match = 1;
        }

        if (match)
        {
            printf("| %-4d | %-20s | %-14s | %-27s |\n",
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            found = 1;
        }
    }

    printf("+------+----------------------+----------------+-----------------------------+\n");

    if (!found)
        printf("\nContact Not Found\n");
}


// Function to edit contacts
void edit_contact(AddressBook *addressbook)
{
    int choice, i;
    int found = -1;

    char name[50];
    char mobile[11];
    char email[50];

    if (addressbook == NULL || addressbook->contact_count == 0)
    {
        printf("No contacts found\n");
        return;
    }

    printf("\nEdit By:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
        return;

    // Edit using name
    if (choice == 1)
    {
        int match[MAX_CONTACTS];
        int match_count = 0;
        int option;

        printf("Enter Name: ");
        scanf(" %49[^\n]", name);

        // Find matching contacts
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Name, name) != NULL)
            {
                match[match_count] = i;
                match_count++;

                printf("%d. %s - %s - %s\n",
                       match_count,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
            }
        }

        if (match_count == 0)
        {
            printf("Contact Not Found\n");
            return;
        }

        if (match_count == 1)
        {
            found = match[0];
        }
        else
        {
            printf("\nMore than one contact found\n");
            printf("1. Mobile\n");
            printf("2. Email\n");
            printf("Enter Option: ");

            if (scanf("%d", &option) != 1)
                return;

            if (option == 1)
            {
                printf("Enter Mobile: ");
                scanf("%10s", mobile);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mobile_number,
                               mobile) == 0)
                    {
                        found = index;
                        break;
                    }
                }
            }
            else if (option == 2)
            {
                printf("Enter Email: ");
                scanf("%49s", email);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mail_ID,
                               email) == 0)
                    {
                        found = index;
                        break;
                    }
                }
            }
            else
            {
                printf("Invalid Option\n");
                return;
            }
        }
    }

    // Edit using mobile number
    else if (choice == 2)
    {
        printf("Enter Mobile: ");
        scanf("%10s", mobile);

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mobile_number,
                       mobile) == 0)
            {
                found = i;
                break;
            }
        }
    }

    // Edit using email
    else if (choice == 3)
    {
        printf("Enter Email: ");
        scanf("%49s", email);

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mail_ID,
                       email) == 0)
            {
                found = i;
                break;
            }
        }
    }
    else
    {
        printf("Invalid Choice\n");
        return;
    }

    if (found == -1)
    {
        printf("Contact Not Found\n");
        return;
    }

    // Update selected field
    if (choice == 1)
    {
        printf("Enter New Name: ");
        scanf(" %49[^\n]", name);

        if (!validname(name))
        {
            printf("Invalid Name\n");
            return;
        }

        strcpy(addressbook->contact_details[found].Name, name);
    }
    else if (choice == 2)
    {
        printf("Enter New Number: ");
        scanf("%10s", mobile);

        if (!validmobile(mobile))
        {
            printf("Invalid Mobile\n");
            return;
        }

        // Check duplicate mobile number
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (i != found &&
                strcmp(addressbook->contact_details[i].Mobile_number,
                       mobile) == 0)
            {
                printf("Mobile Number Already Exists\n");
                return;
            }
        }

        strcpy(addressbook->contact_details[found].Mobile_number, mobile);
    }
    else if (choice == 3)
    {
        printf("Enter New Email: ");
        scanf("%49s", email);

        if (!validemail(email))
        {
            printf("Invalid Email\n");
            return;
        }

        // Check duplicate email
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (i != found &&
                strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
            {
                printf("Email Already Exists\n");
                return;
            }
        }

        strcpy(addressbook->contact_details[found].Mail_ID, email);
    }

    loading();

    printf("\nContact Updated Successfully\n");

    // Save updated contact details
    save_contactsinfile(addressbook);
}


// Function to delete contacts
void delete_contact(AddressBook *addressbook)
{
    int choice, i;
    int found = -1;

    char name[50];
    char mobile[11];
    char email[50];

    if (addressbook == NULL || addressbook->contact_count == 0)
    {
        printf("No contacts found\n");
        return;
    }

    printf("\nDelete By:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email\n");
    printf("4. Back\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1)
        return;

    // Delete using name
    if (choice == 1)
    {
        int match[MAX_CONTACTS];
        int match_count = 0;
        int option;

        printf("Enter Name: ");
        scanf(" %49[^\n]", name);

        // Find matching contacts
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Name, name) != NULL)
            {
                match[match_count] = i;
                match_count++;

                printf("%d. %s - %s - %s\n",
                       match_count,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
            }
        }

        if (match_count == 0)
        {
            printf("Contact Not Found\n");
            return;
        }

        if (match_count == 1)
        {
            found = match[0];
        }
        else
        {
            printf("\nMore than one contact found\n");
            printf("1. Mobile\n");
            printf("2. Email\n");
            printf("Enter Option: ");

            if (scanf("%d", &option) != 1)
                return;

            if (option == 1)
            {
                printf("Enter Mobile: ");
                scanf("%10s", mobile);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mobile_number,
                               mobile) == 0)
                    {
                        found = index;
                        break;
                    }
                }
            }
            else if (option == 2)
            {
                printf("Enter Email: ");
                scanf("%49s", email);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mail_ID,
                               email) == 0)
                    {
                        found = index;
                        break;
                    }
                }
            }
            else
            {
                printf("Invalid Option\n");
                return;
            }
        }
    }

    // Delete using mobile number
    else if (choice == 2)
    {
        printf("Enter Mobile: ");
        scanf("%10s", mobile);

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mobile_number,
                       mobile) == 0)
            {
                found = i;
                break;
            }
        }
    }

    // Delete using email
    else if (choice == 3)
    {
        printf("Enter Email: ");
        scanf("%49s", email);

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mail_ID,
                       email) == 0)
            {
                found = i;
                break;
            }
        }
    }

    // Return to previous menu
    else if (choice == 4)
    {
        return;
    }
    else
    {
        printf("Invalid Choice\n");
        return;
    }

    if (found == -1)
    {
        printf("Contact Not Found\n");
        return;
    }

    // Shift remaining contacts one position left
    for (i = found; i < addressbook->contact_count - 1; i++)
    {
        addressbook->contact_details[i] =
            addressbook->contact_details[i + 1];
    }

    // Decrease contact count
    addressbook->contact_count--;

    loading();

    printf("\nContact Deleted Successfully\n");

    // Save updated contacts
    save_contactsinfile(addressbook);
}
