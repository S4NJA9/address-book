
#include <stdio.h>
#include <string.h>
#include "valid.h"

// Function to validate contact name
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

    // Check every character
    while (name[i] != '\0')
    {
        // Allow only uppercase letters, lowercase letters and spaces
        if ((name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= 'a' && name[i] <= 'z') ||
            name[i] == ' ')
        {
            // Do not allow consecutive spaces
            if (name[i] == ' ' && name[i + 1] == ' ')
            {
                return 0;
            }

            i++;
        }
        else
        {
            return 0;
        }
    }

    // Name should not end with a space
    if (name[i - 1] == ' ')
    {
        return 0;
    }

    return 1;
}


// Function to validate mobile number
int validmobile(char mobile[])
{
    int i;

    // Check NULL pointer
    if (mobile == NULL)
    {
        return 0;
    }

    // Mobile number must contain exactly 10 digits
    if (strlen(mobile) != 10)
    {
        return 0;
    }

    // Indian mobile number should start with 6, 7, 8 or 9
    if (mobile[0] < '6' || mobile[0] > '9')
    {
        return 0;
    }

    // Check whether all characters are digits
    for (i = 0; i < 10; i++)
    {
        if (mobile[i] < '0' || mobile[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}


// Function to validate email address
int validemail(char email[])
{
    int i;
    int position = -1;
    int dot = -1;
    int len;

    // Check whether email is NULL or empty
    if (email == NULL || email[0] == '\0')
    {
        return 0;
    }

    len = strlen(email);

    // Check minimum length
    if (len < 6 || len >= 50)
    {
        return 0;
    }

    // Check for spaces and uppercase letters
    for (i = 0; i < len; i++)
    {
        if (email[i] == ' ')
        {
            return 0;
        }

        if (email[i] >= 'A' && email[i] <= 'Z')
        {
            return 0;
        }

        // Find @ position
        if (email[i] == '@')
        {
            // Only one @ symbol is allowed
            if (position != -1)
            {
                return 0;
            }

            position = i;
        }
    }

    // @ should not be at the beginning
    if (position <= 0)
    {
        return 0;
    }

    // Find the last dot
    for (i = position + 1; i < len; i++)
    {
        if (email[i] == '.')
        {
            dot = i;
        }
    }

    // Dot must exist after @
    if (dot == -1)
    {
        return 0;
    }

    // At least one character must exist between @ and dot
    if (dot - position <= 1)
    {
        return 0;
    }

    // Validate characters before @
    // Only lowercase letters and digits are allowed
    for (i = 0; i < position; i++)
    {
        if (!((email[i] >= 'a' && email[i] <= 'z') ||
              (email[i] >= '0' && email[i] <= '9')))
        {
            return 0;
        }
    }

    // Validate domain name
    // Only lowercase letters are allowed
    for (i = position + 1; i < dot; i++)
    {
        if (!(email[i] >= 'a' && email[i] <= 'z'))
        {
            return 0;
        }
    }

    // Email must end with .com
    if (len < 5 ||
        email[len - 4] != '.' ||
        email[len - 3] != 'c' ||
        email[len - 2] != 'o' ||
        email[len - 1] != 'm')
    {
        return 0;
    }

    return 1;
}
