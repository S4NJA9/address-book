#include <string.h> // Functions for string operations
#include "valid.h"  // Validation functions for name, mobile and email
#include <unistd.h> // Used for usleep() in loading animation
#include "file.h"   // Functions for file handling
#include <stdlib.h> // Contains exit() function

// Function Definitions

void loading(void)
{
    for (int i = 0; i <= 100; i++)
    {
        printf("\rLoading[");
        for (int j = 1; j <= i / 2; j++)
            printf("-");
        for (int space = i / 2; space <= 50; space++)
            printf(" ");
        printf("] %3d%%", i);

        fflush(stdout);
        usleep(50000);
    }

    printf("\n");
}

void create_contact(AddressBook *addressbook)
{
    // Variables used to store contact details entered by the user
    char name[50], mobile[11], email[30], choice;
    int i, found;

    // Repeat until user chooses not to add more contacts
    do
    {
        // Get and validate contact name
        do
        {
            printf("Enter Name: ");
            scanf(" %[^\n]", name);

            if (!validname(name))
            {
                printf("Invalid Name.\n");
            }

        } while (!validname(name));

        // Get and validate mobile number
        do
        {
            printf("Enter Mobile: ");
            scanf("%s", mobile);

            if (!validmobile(mobile))
            {
                printf("Invalid Mobile Number.\n");
            }

        } while (!validmobile(mobile));

        // Check whether the entered mobile number already exists
        while (1)
        {
            found = 0;

            // Compare entered mobile number with all existing contacts
            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0)
                {
                    found = 1;
                    break;
                }
            }

            // Exit loop if mobile number is unique
            if (found == 0)
                break;

            printf("Mobile Number Already Exists.\n");

            // Ask user to enter another mobile number
            do
            {
                printf("Enter Another Mobile Number: ");
                scanf("%s", mobile);

                if (!validmobile(mobile))
                {
                    printf("Invalid Mobile Number.\n");
                }

            } while (!validmobile(mobile));
        }

        // Get and validate email address
        do
        {
            printf("Enter Email: ");
            scanf("%s", email);

            if (!validemail(email))
            {
                printf("Invalid Email.\n");
            }

        } while (!validemail(email));

        // Check whether the entered email already exists
        while (1)
        {
            found = 0;

            // Compare entered email with all existing contacts
            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
                {
                    found = 1;
                    break;
                }
            }

            // Exit loop if email is unique
            if (found == 0)
                break;

            printf("Email Already Exists.\n");

            // Ask user to enter another email address
            do
            {
                printf("Enter Another Email: ");
                scanf("%s", email);

                if (!validemail(email))
                {
                    printf("Invalid Email.\n");
                }

            } while (!validemail(email));
        }

        // Check whether address book storage is full
        if (addressbook->contact_count >= MAX_CONTACTS)
        {
            printf("Address Book Full\n");
            return;
        }

        // Store validated contact details into address book
        strcpy(addressbook->contact_details[addressbook->contact_count].Name, name);
        strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number, mobile);
        strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID, email);

        // Increase contact count after successful insertion
        addressbook->contact_count++;

        // Ask user whether to add another contact
        do
        {
            printf("\nDo you want to enter another contact? (Y/N): ");
            scanf(" %c", &choice);

        } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

    } while (choice == 'Y' || choice == 'y');

    // Display loading animation
    loading();

    // Display success message
    printf("\nDone! 👍 Contact Added Successfully\n\n");

    // Save newly added contacts into file
    save_contactsinfile(addressbook);
}

void list_contacts(AddressBook *addressbook, int sortCriteria)
{
    int i, j;
    Contacts temp; // Temporary variable used during swapping

    // Check whether any contact exists in the address book
    if (addressbook->contact_count == 0)
    {
        printf("No contacts found\n");
        return;
    }

    // Validate sorting option selected by the user
    if (sortCriteria >= 1 && sortCriteria <= 3)
    {
        // Sort contacts using Bubble Sort
        for (i = 0; i < addressbook->contact_count - 1; i++)
        {
            for (j = 0; j < addressbook->contact_count - i - 1; j++)
            {
                int result = 0;

                // Compare contacts based on Name
                if (sortCriteria == 1)
                {
                    result = strcmp(addressbook->contact_details[j].Name,
                                    addressbook->contact_details[j + 1].Name);
                }

                // Compare contacts based on Mobile Number
                else if (sortCriteria == 2)
                {
                    result = strcmp(addressbook->contact_details[j].Mobile_number,
                                    addressbook->contact_details[j + 1].Mobile_number);
                }

                // Compare contacts based on Email ID
                else if (sortCriteria == 3)
                {
                    result = strcmp(addressbook->contact_details[j].Mail_ID,
                                    addressbook->contact_details[j + 1].Mail_ID);
                }

                // Swap contacts if they are not in correct order
                if (result > 0)
                {
                    temp = addressbook->contact_details[j];
                    addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                    addressbook->contact_details[j + 1] = temp;
                }
            }
        }

        // Display table header
        printf("\n+------+----------------------+----------------+-----------------------------+\n");
        printf("| %-4s | %-20s | %-14s | %-27s |\n",
               "No.", "Name", "Mobile", "Email");
        printf("+------+----------------------+----------------+-----------------------------+\n");

        // Display all contacts in tabular format
        for (i = 0; i < addressbook->contact_count; i++)
        {
            printf("| %-4d | %-20s | %-14s | %-27s |\n",
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
        }

        // Display table footer
        printf("+------+----------------------+----------------+-----------------------------+\n");
    }
    else
    {
        // Execute when invalid sorting option is selected
        printf("Invalid sort option (1-3)\n");
    }
}

void search_contacts(AddressBook *addressbook)
{
    int choice, i;

    // Variables used to store search input
    char name[50];
    char mobile[11];
    char email[30];

    // Flag variable to check whether contact is found or not
    int found = 0;

    // Get search option from user
    printf("Enter choice\n");
    scanf("%d", &choice);

    // Execute search based on selected option
    switch (choice)
    {
    case 1:

        // Search contact by Name
        printf("Enter Name : ");
        scanf(" %[^\n]", name);

        // Display table header
        printf("\n+------+----------------------+----------------+-----------------------------+\n");
        printf("| %-4s | %-20s | %-14s | %-27s |\n",
               "No.", "Name", "Mobile", "Email");
        printf("+------+----------------------+----------------+-----------------------------+\n");

        found = 0;

        // Search all contacts using partial name matching
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Name, name) != NULL)
            {
                printf("| %-4d | %-20s | %-14s | %-27s |\n",
                       i + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);

                found = 1;
            }
        }

        // Display table footer
        printf("+------+----------------------+----------------+-----------------------------+\n");

        // Execute when no matching name is found
        if (!found)
        {
            printf("\nName Not Found\n");
        }

        break;

    case 2:

        // Search contact by Mobile Number
        printf("Enter Number : ");
        scanf(" %[^\n]", mobile);

        // Display table header
        printf("\n+------+----------------------+----------------+-----------------------------+\n");
        printf("| %-4s | %-20s | %-14s | %-27s |\n",
               "No.", "Name", "Mobile", "Email");
        printf("+------+----------------------+----------------+-----------------------------+\n");

        found = 0;

        // Search all contacts using partial mobile number matching
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Mobile_number, mobile) != NULL)
            {
                printf("| %-4d | %-20s | %-14s | %-27s |\n",
                       i + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);

                found = 1;
            }
        }

        // Display table footer
        printf("+------+----------------------+----------------+-----------------------------+\n");

        // Execute when no matching number is found
        if (!found)
        {
            printf("\nNumber Not Found\n");
        }

        break;

    case 3:

        // Search contact by Email ID
        printf("Enter Email : ");
        scanf(" %[^\n]", email);

        // Display table header
        printf("\n+------+----------------------+----------------+-----------------------------+\n");
        printf("| %-4s | %-20s | %-14s | %-27s |\n",
               "No.", "Name", "Mobile", "Email");
        printf("+------+----------------------+----------------+-----------------------------+\n");

        found = 0;

        // Search all contacts using partial email matching
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Mail_ID, email) != NULL)
            {
                printf("| %-4d | %-20s | %-14s | %-27s |\n",
                       i + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);

                found = 1;
            }
        }

        // Display table footer
        printf("+------+----------------------+----------------+-----------------------------+\n");

        // Execute when no matching email is found
        if (!found)
        {
            printf("\nEmail Not Found\n");
        }

        break;

    case 4:

        // Return to previous menu
        return;

    default:

        // Execute when user enters invalid option
        printf("Invalid Choice\n");
    }

    // Display message when no matching contact exists
    if (found == 0 && choice != 4)
    {
        printf("Contact Not Found\n");
    }
}

void edit_contact(AddressBook *addressbook)
{
    int choice, i;

    // Variables used to store user input
    char name[50];
    char mobile[11];
    char email[30];

    // Stores index of matched contact
    int found = -1;

    // Get edit option from user
    printf("Enter choice\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

        int match_count = 0;
        int option;
        int match[100];
        char search[50];

        // Search contact using Name
        printf("Enter Name : ");
        scanf(" %[^\n]", name);

        

            printf("\n+------+----------------------+----------------+-----------------------------+\n");
            printf("| %-4s | %-20s | %-14s | %-27s |\n", "No.", "Name", "Mobile", "Email");
            printf("+------+----------------------+----------------+-----------------------------+\n");

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Name, name) != NULL)
            {
                match[match_count] = i;
                printf("| %-4d | %-20s | %-14s | %-27s |\n",
                    match_count + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
                
                match_count++;
            }
        }
         // Display table footer
        printf("+------+----------------------+----------------+-----------------------------+\n");

        if (match_count == 0)
        {
            printf("Contact is not found\n");
            return;
        }
        if(match_count == 1){
            found = match[0];
        }
        else{
            // More than one contact has same name
            printf("\nMore than one contact found\n");
            printf("1.Mobile\n");
            printf("2.Email\n");
            printf("\nEnter Option : ");
            scanf("%d", &option);

            // Identify contact using Mobile Number
            if (option == 1)
            {
                printf("Enter Mobile : ");
                scanf("%s", mobile);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mobile_number, mobile) == 0)
                    {
                        found = index;
                        break;
                    }
                }
            }

            // Identify contact using Email ID
            else if (option == 2)
            {
                printf("Enter Email : ");
                scanf("%s", email);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mail_ID, email) == 0)
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

        

        // Execute when contact is not found
        if (found == -1)
        {
            printf("Contact Not Found\n");
            return;
        }

        // Get new name from user
        printf("Enter New Name : ");
        scanf(" %[^\n]", name);

        // Validate entered name
        if (!validname(name))
        {
            printf("Invalid Name\n");
            return;
        }

        // Display loading animation
        loading();

        // Update contact name
        strcpy(addressbook->contact_details[found].Name, name);

        printf("\nContact Updated 👍 Successfully\n");

        // Save updated details into file
        save_contactsinfile(addressbook);
        break;

    case 2:

        // Search contact using Mobile Number
        printf("Enter Mobile : ");
        scanf("%s", mobile);

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0)
            {
                found = i;
                break;
            }
        }

        // Execute when contact is not found
        if (found == -1)
        {
            printf("Contact Not Found\n");
            return;
        }

        // Get new mobile number
        printf("Enter New Number : ");
        scanf("%s", mobile);

        // Validate mobile number
        if (!validmobile(mobile))
        {
            printf("Invalid Mobile\n");
            return;
        }

        // Display loading animation
        loading();

        // Update mobile number
        strcpy(addressbook->contact_details[found].Mobile_number, mobile);

        printf("\nContact Updated 👍 Successfully\n");

        // Save updated details into file
        save_contactsinfile(addressbook);
        break;

    case 3:

        // Search contact using Email ID
        printf("Enter Email : ");
        scanf("%s", email);

        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
            {
                found = i;
                break;
            }
        }

        // Execute when contact is not found
        if (found == -1)
        {
            printf("Contact Not Found\n");
            return;
        }

        // Get new email address
        printf("Enter New Email : ");
        scanf("%s", email);

        // Validate email address
        if (!validemail(email))
        {
            printf("Invalid Email\n");
            return;
        }

        // Display loading animation
        loading();

        // Update email address
        strcpy(addressbook->contact_details[found].Mail_ID, email);

        printf("\nContact Updated 👍 Successfully\n");

        // Save updated details into file
        save_contactsinfile(addressbook);
        break;

    default:

        // Execute when user enters invalid option
        printf("Invalid Choice\n");
    }
}

void save_and_exit(AddressBook *addressbook)
{
    // Save current contact details into file
    save_contactsinfile(addressbook);
    // Exit the program successfully
    exit(EXIT_SUCCESS);
}

void delete_contact(AddressBook *addressbook)
{
    int choice, i;

    // Variables used to store user input
    char name[50];
    char mobile[11];
    char email[50];

    // Get delete option from user
    printf("Enter Choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        // Array used to store matching contact indexes
        int match[100];

        // Stores number of matching contacts
        int match_count = 0;

        // Stores index of selected contact
        int found = -1;

        // Used when multiple contacts have same name
        int option;

        // Get name to search
        printf("Enter Name : ");
        scanf(" %[^\n]", name);

        // Display matching contacts
        printf("--------------------------------------------------------------------\n");
        printf("%-20s %-20s %-25s\n", "Name", "Phone", "Email");
        printf("--------------------------------------------------------------------\n");

        // Search contacts using partial name matching
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strstr(addressbook->contact_details[i].Name, name) != NULL)
            {
                printf("%-20s %-20s %-25s\n",
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);

                // Store matching contact index
                match[match_count] = i;
                match_count++;
            }
        }

        // Execute when no contact is found
        if (match_count == 0)
        {
            printf("Contact Not Found\n");
            return;
        }

        // If only one contact matches, select it directly
        if (match_count == 1)
        {
            found = match[0];
        }
        else
        {
            // More than one contact has same name
            printf("\nMore than one contact found\n");
            printf("1.Mobile\n");
            printf("2.Email\n");
            printf("Enter Option : ");
            scanf("%d", &option);

            // Identify contact using Mobile Number
            if (option == 1)
            {
                printf("Enter Mobile : ");
                scanf("%s", mobile);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mobile_number, mobile) == 0)
                    {
                        found = index;
                        break;
                    }
                }
            }

            // Identify contact using Email ID
            else if (option == 2)
            {
                printf("Enter Email : ");
                scanf("%s", email);

                for (i = 0; i < match_count; i++)
                {
                    int index = match[i];

                    if (strcmp(addressbook->contact_details[index].Mail_ID, email) == 0)
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

        // Execute when selected contact is not found
        if (found == -1)
        {
            printf("Contact Not Found\n");
            return;
        }

        // Shift all contacts one position left
        // This removes the selected contact from the array
        for (i = found; i < addressbook->contact_count - 1; i++)
        {
            addressbook->contact_details[i] =
                addressbook->contact_details[i + 1];
        }

        // Reduce total contact count
        addressbook->contact_count--;

        // Display loading animation
        loading();

        printf("\nContact Deleted 👍 Successfully\n");

        // Save updated contacts into file
        save_contactsinfile(addressbook);
        break;
    }

    case 2:
    {
        // Delete contact using Mobile Number
        int found = -1;

        printf("Enter Mobile : ");
        scanf("%s", mobile);

        // Search mobile number
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0)
            {
                found = i;
                break;
            }
        }

        // Execute when contact is not found
        if (found == -1)
        {
            printf("Contact Not Found\n");
            return;
        }

        // Shift remaining contacts left
        for (i = found; i < addressbook->contact_count - 1; i++)
        {
            addressbook->contact_details[i] =
                addressbook->contact_details[i + 1];
        }

        // Decrease contact count
        addressbook->contact_count--;

        loading();

        printf("\nContact Deleted 👍 Successfully\n");

        // Save updated contacts into file
        save_contactsinfile(addressbook);
        break;
    }

    case 3:
    {
        // Delete contact using Email ID
        int found = -1;

        printf("Enter Email : ");
        scanf("%s", email);

        // Search email
        for (i = 0; i < addressbook->contact_count; i++)
        {
            if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
            {
                found = i;
                break;
            }
        }

        // Execute when contact is not found
        if (found == -1)
        {
            printf("Contact Not Found\n");
            return;
        }

        // Shift remaining contacts left
        for (i = found; i < addressbook->contact_count - 1; i++)
        {
            addressbook->contact_details[i] =
                addressbook->contact_details[i + 1];
        }

        // Decrease contact count
        addressbook->contact_count--;

        // Display loading animation
        loading();

        printf("\nContact Deleted 👍 Successfully\n");

        // Save updated contacts into file
        save_contactsinfile(addressbook);
        break;
    }

    case 4:

        // Return to previous menu
        return;

    default:

        // Execute when user enters invalid option
        printf("Invalid Choice\n");
    }
}