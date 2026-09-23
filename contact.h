#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 200

enum
{
    SERIAL_WIDTH = 5,
    NAME_WIDTH = 15,
    PHONE_WIDTH = 12,
    EMAIL_WIDTH = 25
};

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void populateAddressBook(AddressBook* addressBook);
int validateEmail(const char *email);
int isEmailDuplicate(AddressBook *addressBook, const char *email, int excludeIndex);\
int validatePhone(const char *phone);
int isPhoneDuplicate(AddressBook *addressBook, const char *phone, int excludeIndex);

#endif
