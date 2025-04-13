#include "contact_manager.h"
#include <stdlib.h>
#include <string.h>

void init_contact(Contact* contact) {
    memset(contact, 0, sizeof(Contact));
}

ErrorCode init_contact_book(ContactBook* book, int initial_capacity) {
    book->contacts = calloc(initial_capacity, sizeof(Contact));
    if (book->contacts == NULL) {
        return ERROR_MEMORY;
    }
    book->count = 0;
    book->capacity = initial_capacity;
    book->max_id = 0;
    return SUCCESS;
}

void free_contact_book(ContactBook* book) {
    free(book->contacts);
    book->contacts = NULL;
    book->count = 0;
    book->capacity = 0;
    book->max_id = 0;
}

ErrorCode add_contact(ContactBook* book, const Contact* contact) {
    if (book->count >= book->capacity) {
        int new_capacity = book->capacity * 2;
        Contact* old_contacts = book->contacts;
        Contact* new_contacts = realloc(book->contacts, new_capacity * sizeof(Contact));
        if (new_contacts == NULL) {
            book->contacts = old_contacts;
            return ERROR_MEMORY;
        }
        book->contacts = new_contacts;
        book->capacity = new_capacity;
    }

    book->contacts[book->count] = *contact;
    if (contact->id > book->max_id) {
        book->max_id = contact->id;
    }
    book->count++;
    return SUCCESS;
}

ErrorCode delete_contact(ContactBook* book, int id) {
    int index = -1;
    for (int i = 0; i < book->count; i++) {
        if (book->contacts[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return ERROR_NOT_FOUND;
    }

    memmove(&book->contacts[index], &book->contacts[index + 1], (book->count - index - 1) * sizeof(Contact));
    book->count--;
    return SUCCESS;
}

ErrorCode edit_contact(ContactBook* book, int id, const Contact* updated_contact) {
    int index = -1;
    for (int i = 0; i < book->count; i++) {
        if (book->contacts[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return ERROR_NOT_FOUND;
    }

    book->contacts[index] = *updated_contact;
    return SUCCESS;
}

ErrorCode find_contact(ContactBook* book, char* surname, char* name, int** ids, int* match_count) {
    *match_count = 0;
    *ids = NULL;
    if ((surname == NULL || surname[0] == '\0') && (name == NULL || name[0] == '\0')) {
        return ERROR_INVALID_INPUT;
    }

    for (int i = 0; i < book->count; i++) {
        int surname_match = (surname == NULL || surname[0] == '\0') || (strstr(book->contacts[i].surname, surname) != NULL);
        int name_match = (name == NULL || name[0] == '\0') || (strstr(book->contacts[i].name, name) != NULL);

        if (surname_match && name_match) {
            int* new_ids = realloc(*ids, (*match_count + 1) * sizeof(int));
            if (new_ids == NULL) {
                free(*ids);
                *ids = NULL;
                *match_count = 0;
                return ERROR_MEMORY;
            }
            *ids = new_ids;
            (*ids)[*match_count] = book->contacts[i].id;
            (*match_count)++;
        }
    }

    return SUCCESS;
}