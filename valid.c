#include <string.h>
#include "valid.h"

// Function to validate the contact name
int validname(char name[])
{
    int i = 0;

    // Check whether name is NULL or empty
    if (name == NULL || name[0] == '\0')
    {
        return 0;
    }

    // Name should not start with a space
    if (name[0] == ' ')
    {
        return 0;
    }

    // Check every character of the name
    while (name[i] != '\0')
    {
        // Allow only uppercase letters, lowercase letters and spaces
        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            // Invalid character found
            return 0;
        }
    }

    // Name is valid
    return 1;
}

// Function to validate mobile number
int validmobile(char mobile[])
{
    int i;

    // Mobile number must contain exactly 10 digits
    if (strlen(mobile) != 10)
    {
        return 0;
    }

    // Indian mobile numbers should start with 6,7,8 or 9
    if (mobile[0] < '6' || mobile[0] > '9')
    {
        return 0;
    }

    // Check whether all characters are digits
    for (i = 0; mobile[i] != '\0'; i++)
    {
        if (mobile[i] >= '0' && mobile[i] <= '9')
        {
            continue;
        }
        else
        {
            // Invalid character found
            return 0;
        }
    }

    // Mobile number is valid
    return 1;
}

// Function to validate email address
int validemail(char email[])
{
    int i;
    int position = -1; // Stores position of '@'
    int dot = -1;      // Stores position of last '.'
    int len;           // for lenght

    // Check whether email is empty
    if (email == NULL || email[0] == '\0')
        return 0;

    // First character should not be uppercase
    if (email[0] >= 'A' && email[0] <= 'Z')
        return 0;

    // Check for spaces and uppercase letters
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == ' ')
            return 0;

        if (email[i] >= 'A' && email[i] <= 'Z')
            return 0;
    }

    // Find position of '@'
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            position = i;
            break;
        }
    }

    // '@' should not be at first position
    if (position <= 0)
        return 0;

    // Validate characters before '@'
    // Only lowercase letters and digits are allowed
    for (i = 0; i < position; i++)
    {
        if (!((email[i] >= 'a' && email[i] <= 'z') ||(email[i] >= '0' && email[i] <= '9')))
        {
            return 0;
        }
    }

    // Find the last dot (.)
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '.')
            dot = i;
    }

    // Dot must exist
    if (dot == -1)
        return 0;

    // Dot must appear after '@'
    if (dot < position)
        return 0;

    // At least one character should exist between '@' and '.'
    if (dot - position <= 1)
        return 0;

    // Validate domain name between '@' and '.'
    // Only lowercase letters are allowed
    for (i = position + 1; i < dot; i++)
    {
        if (!(email[i] >= 'a' && email[i] <= 'z'))
            return 0;
    }

    // Calculate length of email
    len = strlen(email);

    // Minimum length required for ".com"
    if (len < 5)
        return 0;

    // Email must end with ".com"
    if (email[len - 4] != '.' || email[len - 3] != 'c' || email[len - 2] != 'o' || email[len - 1] != 'm')
    {
        return 0;
    }

    // Email is valid
    return 1;
}