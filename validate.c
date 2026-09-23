#include <ctype.h>
#include <string.h>
#include "contact.h"

int validateEmail(const char *email)
{
    int len = strlen(email);
    
    // 1. Minimum length check (e.g., "a@b.com" -> 7 characters)
    if (len < 7)
        return 0;

    // 2. Must end with ".com"
    if (strcmp(email + len - 4, ".com") != 0)
        return 0;

    // 3. Find '@' symbol
    char *at = strchr(email, '@');
    if (at == NULL)
        return 0;

    // Must have characters before '@' (cannot start with '@')
    if (at == email)
        return 0;

    // Must NOT contain another '@'
    if (strchr(at + 1, '@') != NULL)
        return 0;

    // 4. Must have characters between '@' and ".com"
    // (e.g., "a@.com" -> at + 1 would be pointing to ".com")
    if (at >= (email + len - 4))
        return 0;

    // 5. Allowed characters check: lowercase letters, digits, '.', '_'
    for (int i = 0; i < len; i++)
    {
        char ch = email[i];
        if (ch == ' ') // No whitespace allowed
            return 0;
            
        if (!islower(ch) && !isdigit(ch) && ch != '@' && ch != '.' && ch != '_')
            return 0;
    }

    return 1; // Valid
}
int isEmailDuplicate(AddressBook *addressBook, const char *email, int excludeIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == excludeIndex)
            continue; // Skip the contact itself when editing

        if (strcasecmp(addressBook->contacts[i].email, email) == 0)
        {
            return 1; // Duplicate found
        }
    }
    return 0; // Unique
}
// Validates that phone number is exactly 10 digits and only contains 0-9
int validatePhone(const char *phone)
{
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(phone[i]))
            return 0;
    }

    return 1;
}

// Checks if the phone number already exists in another contact
int isPhoneDuplicate(AddressBook *addressBook, const char *phone, int excludeIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == excludeIndex)
            continue; // Skip itself when editing

        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 1; // Duplicate found
        }
    }
    return 0; // Unique
}
