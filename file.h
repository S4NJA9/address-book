#ifndef FILE_H
#define FILE_H

// Include contact.h because AddressBook structure
// is used in the function declarations below
#include "contact.h"

// Function prototype to save all contacts into a file
// Receives AddressBook structure address and stores data permanently
void save_contactsinfile(AddressBook *addressbook);

// Function prototype to load contacts from file
// Reads previously saved contacts and stores them in AddressBook structure
void loadContactsFromFile(AddressBook *addressbook);

// End of header guard
#endif