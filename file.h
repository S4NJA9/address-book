
#ifndef FILE_H
#define FILE_H

#include "contact.h"

// Save all contacts into contacts.csv
void save_contactsinfile(AddressBook *addressbook);

// Load previously saved contacts from contacts.csv
void loadContactsFromFile(AddressBook *addressbook);

#endif
