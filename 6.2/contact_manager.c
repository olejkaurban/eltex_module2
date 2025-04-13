#include "contact_manager.h"
#include <stdlib.h>
#include <string.h>

void init_contact(Contact* contact) {
    memset(contact, 0, sizeof(Contact));
}

void init_list(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->max_id = 0;
}

void free_list(DoublyLinkedList *list) {
    ContactNode* current_node = list->head;
    while (current_node != NULL) {
        ContactNode* temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    init_list(list);
}

ContactNode* create_node(Contact *contact) {
    ContactNode *new_node = (ContactNode *)malloc(sizeof(ContactNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->contact = *contact;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void insert_node( DoublyLinkedList *list, ContactNode *new_node) {
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        ContactNode *current_node = list->head;

        while (current_node != NULL && current_node->contact.id < new_node->contact.id) {
            current_node = current_node->next;        
        }

        if (current_node == list->head) {
            new_node->next = list->head;
            list->head->prev = new_node;
            list->head = new_node;
        } else if (current_node == NULL) {
            list->tail->next = new_node;
            new_node->prev = list->tail;
            list->tail = new_node;
        } else {
            new_node->next = current_node;
            new_node->prev = current_node->prev;
            if (current_node->prev) {
                current_node->prev->next = new_node;
            }
            current_node->prev = new_node;
        }
    }
    list->size++;
    if (new_node->contact.id > list->max_id) {
        list->max_id = new_node->contact.id;
    }
}

void delete_node(DoublyLinkedList* list, int id) {
    ContactNode* current_node = list->head;
    while (current_node != NULL && current_node->contact.id != id) {
        current_node = current_node->next;
    }

    if (current_node == NULL) {
        return;
    }

    if (current_node == list->head && current_node == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else if (current_node == list->head) {
        list->head = current_node->next;
        list->head->prev = NULL;
    } else if (current_node == list->tail) {
        list->tail = current_node->prev;
        list->tail->next = NULL;
    } else {
        current_node->prev->next = current_node->next;
        current_node->next->prev = current_node->prev;
    }

    free(current_node);
    list->size--;
}

ErrorCode add_contact(DoublyLinkedList *list, const Contact *contact) {
    Contact new_contact = *contact;
    new_contact.id = list->max_id + 1;

    ContactNode *new_node = create_node(&new_contact);
    if (new_node == NULL) {
        return ERROR_MEMORY;
    }

    insert_node(list, new_node);
    return SUCCESS;
}

ErrorCode delete_contact(DoublyLinkedList *list, int id) {
    ContactNode *current_node = list->head;
    while (current_node != NULL) {
        if  (current_node->contact.id == id) {
            delete_node(list, id);
            return SUCCESS;
        }
        current_node = current_node->next;
    }
    return ERROR_NOT_FOUND;
}

ErrorCode edit_contact(DoublyLinkedList *list, int id, const Contact* updated_contact) {
    ContactNode *current_node = list->head;
    while (current_node != NULL) {
        if (current_node->contact.id == id) {
            int old_id = current_node->contact.id;
            current_node->contact = *updated_contact;
            current_node->contact.id = old_id;
            return SUCCESS;
        }
        current_node = current_node->next;
    }
    return ERROR_NOT_FOUND;
}

ErrorCode find_contact(DoublyLinkedList *list, char* surname, char* name, int** ids, int* match_count) {
    *match_count = 0;
    *ids = NULL;
    ContactNode *current_node = list->head;

    if ((surname == NULL || surname[0] == '\0') && (name == NULL || name[0] == '\0')) {
        return ERROR_INVALID_INPUT;
    }

    while (current_node != NULL) {
        int surname_match = (surname == NULL || surname[0] == '\0') || (strstr(current_node->contact.surname, surname) != NULL);
        int name_match = (name == NULL || name[0] == '\0') || (strstr(current_node->contact.name, name) != NULL);

        if (surname_match && name_match) {
            int* new_ids = realloc(*ids, (*match_count + 1) * sizeof(int));
            if (new_ids == NULL) {
                free(*ids);
                return ERROR_MEMORY;
            }
            *ids = new_ids;
            (*ids)[(*match_count)++] = current_node->contact.id;
        }
        current_node = current_node->next;
    }
    return SUCCESS;
}