#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    //create the file pointer in write mode
    FILE *file = fopen("contacts.csv", "w");

    //print the data in fine(contacts.csv)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved to contacts.csv\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    //create the file pointer in read mode
    FILE *fp = fopen("contacts.csv", "r");

    fscanf(fp, "%d\n",&addressBook->contactCount);
    //read the data in file(contacts.csv)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
}
