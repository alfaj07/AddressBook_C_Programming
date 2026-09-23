#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

static void printBorderSegment(int width)
{
    printf("+");
    for (int i = 0; i < width + 2; i++)
    {
        printf("-");
    }
}


static void printTableBorder(void)
{
    printBorderSegment(SERIAL_WIDTH);
    printBorderSegment(NAME_WIDTH);
    printBorderSegment(PHONE_WIDTH);
    printBorderSegment(EMAIL_WIDTH);
    printf("+\n");
}

static void printTableHeader(void)
{
    printTableBorder();
    printf("| %-*s | %-*s | %-*s | %-*s |\n",
           SERIAL_WIDTH, "S.No",
           NAME_WIDTH, "Name",
           PHONE_WIDTH, "Phone",
           EMAIL_WIDTH, "Email");
    printTableBorder();
}

static void printTableRow(int serialNumber, const Contact *contact)
{
    printf("| %-*d | %-*.*s | %-*.*s | %-*.*s |\n",
           SERIAL_WIDTH, serialNumber,
           NAME_WIDTH, NAME_WIDTH, contact->name,
           PHONE_WIDTH, PHONE_WIDTH, contact->phone,
           EMAIL_WIDTH, EMAIL_WIDTH, contact->email);
}


void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    char continueChoice;
    do
    {
        printf("   1. Sort by Name\n");
        printf("   2. Sort by Phone Number\n");
        printf("   3. Sort by Email\n");
        printf("   4. Exit\n");
    
        int sortChoice;
        printf("Enter your choice for shorting : ");
        scanf("%d", &sortChoice);
        switch(sortChoice)
        {
            case 1:
                for(int i = 0; i<addressBook->contactCount-1;i++)
                {
                    for(int j=0;j<addressBook->contactCount-i-1;j++)
                    {
                        if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                        {
                            Contact temp = addressBook->contacts[j];
                            addressBook->contacts[j]=addressBook->contacts[j+1];
                            addressBook->contacts[j+1]=temp;
                        }
                    }
                }
                break;
            case 2:
                for(int i = 0; i<addressBook->contactCount-1;i++)
                {
                    for(int j=0;j<addressBook->contactCount-i-1;j++)
                    {
                        if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                        {
                            Contact temp = addressBook->contacts[j];
                            addressBook->contacts[j]=addressBook->contacts[j+1];
                            addressBook->contacts[j+1]=temp;
                        }
                    }
                }
                break;
            case 3:
                for(int i = 0; i<addressBook->contactCount-1;i++)
                {
                    for(int j=0;j<addressBook->contactCount-i-1;j++)
                    {
                        if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                        {
                            Contact temp = addressBook->contacts[j];
                            addressBook->contacts[j]=addressBook->contacts[j+1];
                            addressBook->contacts[j+1]=temp;
                        }
                    }
                }
                break;
            case 4:
                return;
            default:
                printf("\n\t\t\tInvalid choice.\n");
        }
        if(addressBook->contactCount == 0)
            {
                printf("No contacts found.\n");
            }
        else
            {
                printf(" \n\t\t\tContacts List \n\n");
                printTableHeader();
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    printTableRow(i + 1, &addressBook->contacts[i]);
                }
                printTableBorder();
            }
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &continueChoice);
    } while (continueChoice == 'y' || continueChoice == 'Y');

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char continueChoice;
    do
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
        char phone[20];
        do
        {
            printf("Enter the Phone No: ");
            scanf(" %[^\n]", phone);

            if (!validatePhone(phone))
            {
                printf("\n\t[Error] Invalid phone number! (Must be exactly 10 digits, numbers only)\n");
            }
            else if (isPhoneDuplicate(addressBook, phone, -1))
            {
                printf("\n\t[Error] This phone number is already registered to another contact!\n");
            }
            else
            {
                strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
                break;
            }
        } while (1);

        char email[50];
        do
        {
            printf("Enter the Email Id: ");
            scanf(" %[^\n]", email);

            if (!validateEmail(email))
            {
                printf("\n\t[Error] Invalid email format! (Format: user@domain.com, lowercase, no spaces)\n");
            }
            else if (isEmailDuplicate(addressBook, email, -1))
            {
                printf("\n\t[Error] This email is already registered to another contact!\n");
            }
            else
            {
                strcpy(addressBook->contacts[addressBook->contactCount].email, email);
                break;
            }
        } while (1);
        addressBook->contactCount++;
        printf("\n\t\tContact Create successfully.\n\n");
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &continueChoice);
    } while (continueChoice == 'y' || continueChoice == 'Y');
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char continueChoice;
    do
    {
        printf("   1. search by Name\n");
        printf("   2. search by Phone Number\n");
        printf("   3. search by Email\n");
        printf("   4. Exit\n");
    
        int Choice;
        printf("Enter your choice for searching : ");
        scanf("%d", &Choice);
        char name[50],phone[15],email[50];
        switch(Choice)
        {
            case 1:
                printf("Enter the name :");
                scanf(" %[^\n]", name);
                {
                    int found=0;
                    int lastIndex = -1;     //declare outside, survives after loop
                    for (size_t i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                        {
                            if(!found)
                            {
                                printTableHeader();// print header only once, only on first match
                            }
                            printTableRow((int)i + 1, &addressBook->contacts[i]);
                            found = 1;
                            lastIndex = (int)i;      // remember the index of the match
                        }
                    }
                    if(found){
                        printTableBorder();
                        return lastIndex;
                    }
                    else
                    {
                        printf("\n\t\tNo contact found with name \"%s\".\n", name);
                        return -2;
                    }
                }
                break;
            case 2:
                printf("Enter the phone Number :");
                scanf(" %[^\n]", phone);
                {
                    int found=0;
                    int lastIndex = -1;     //declare outside, survives after loop
                    for (size_t i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcasecmp(addressBook->contacts[i].phone, phone) == 0)
                        {
                            if(!found)
                            {
                                printTableHeader();// print header only once, only on first match
                            }
                            printTableRow((int)i + 1, &addressBook->contacts[i]);
                            found = 1;
                            lastIndex = (int)i;      // remember the index of the match
                        }
                    }
                    if(found){
                        printTableBorder();
                        return lastIndex;
                    }
                    else
                    {
                        printf("\n\t\tNo contact found with name \"%s\".\n", name);
                        return -2;
                    }

                }
                break;
            case 3:
                printf("Enter the Email Id :");
                scanf(" %[^\n]", email);
                {
                    int found=0;
                    int lastIndex = -1;     //declare outside, survives after loop
                    for (size_t i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcasecmp(addressBook->contacts[i].email, email) == 0)
                        {
                            if(!found)
                            {
                                printTableHeader();// print header only once, only on first match
                            }
                            printTableRow((int)i + 1, &addressBook->contacts[i]);
                            found = 1;
                            lastIndex = (int)i;      // remember the index of the match
                        }
                    }
                    if(found){
                        printTableBorder();
                        return lastIndex;
                    }
                    else{
                        printf("\n\t\tNo contact found with name \"%s\".\n", name);
                        return -2;
                    }
                }
                break;
            case 4:
                return -1;
            default:
                printf("\n\t\t\tInvalid choice.\n");
        }
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &continueChoice);
    } while (continueChoice == 'y' || continueChoice == 'Y');
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char continueChoice;
    do
    {
        printf("   1. Edit  Name\n");
        printf("   2. Edit  Phone Number\n");
        printf("   3. Edit  Email\n");
        printf("   4. Exit\n");
    
        int Choice;
        printf("Enter your choice for Editing : ");
        scanf("%d", &Choice);
        if(Choice==4)
            return;
        else if(Choice < 1 || Choice > 4)
            printf("\n\t\t\tInvalid choice.\n");
        else
        {
            int index= searchContact(addressBook);
            if(index==-1)
                printf("\nExit from search contact\n");
            else if(index==-2)
                printf("\nContact not found\n");
            else
            {
                switch( Choice)
                {
                    case 1:
                        printf("Enter the Edit Name : ");
                        scanf(" %[^\n]",addressBook->contacts[index].name);
                        printf("\n\t\tContact Name Edit successfully.\n\n");
                        break;
                    case 2:
                    {
                        char newPhone[20];
                        do
                        {
                            printf("Enter the Edit Phone No: ");
                            scanf(" %[^\n]", newPhone);

                            if (!validatePhone(newPhone))
                            {
                                printf("\n\t[Error] Invalid phone number! (Must be exactly 10 digits)\n");
                            }
                            else if (isPhoneDuplicate(addressBook, newPhone, index))
                            {
                                printf("\n\t[Error] This phone number already exists in another contact!\n");
                            }
                            else
                            {
                                strcpy(addressBook->contacts[index].phone, newPhone);
                                printf("\n\t\tContact Phone No Edited successfully.\n\n");
                                break;
                            }
                        } while (1);
                        break;
                    }
                    case 3:
                    {
                        char newEmail[50];
                        do
                        {
                            printf("Enter the Edit Email id: ");
                            scanf(" %[^\n]", newEmail);

                            if (!validateEmail(newEmail))
                            {
                                printf("\n\t[Error] Invalid email format! (Format: user@domain.com)\n");
                            }
                            else if (isEmailDuplicate(addressBook, newEmail, index))
                            {
                                printf("\n\t[Error] This email already exists in another contact!\n");
                            }
                            else
                            {
                                strcpy(addressBook->contacts[index].email, newEmail);
                                printf("\n\t\tContact Email id Edited successfully.\n\n");
                                break;
                            }
                        } while (1);
                        break;
                    }

                }
            }
        }
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &continueChoice);
    } while (continueChoice == 'y' || continueChoice == 'Y');
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char continueChoice;
    do
    {
        int index=searchContact(addressBook);

        if(index==-1)
            printf("\nExit from search contact\n");
        else if(index==-2)
            printf("\nContact not found\n");
        else
        {
            for(int i=index;i<addressBook->contactCount;i++)
                addressBook->contacts[i]=addressBook->contacts[i+1];
            addressBook->contactCount--;
            printf("\n\t\tContact deleted successfully.\n\n");
        }
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &continueChoice);
    } while (continueChoice == 'y' || continueChoice == 'Y');
}
