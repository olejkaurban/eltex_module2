#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#define MAX_STRING 50

typedef struct {
    char patronymic[MAX_STRING];
    char job_place[MAX_STRING];
    char job_title[MAX_STRING];
    char phone[MAX_STRING];
    char mail[MAX_STRING];
    char links[MAX_STRING];
} ContactInfo;

typedef struct {
    int id;
    char surname[MAX_STRING];
    char name[MAX_STRING];
    ContactInfo info;
} Contact;

typedef struct ContactNode {
    Contact contact;
    struct ContactNode *prev;
    struct ContactNode *next;
} ContactNode;

typedef struct {
    ContactNode *head;
    ContactNode *tail;
    int size;
    int max_id;
} DoublyLinkedList;

typedef enum {
    SUCCESS = 0,
    ERROR_MEMORY = 1,
    ERROR_NOT_FOUND = 2,
    ERROR_INVALID_INPUT = 3
} ErrorCode;

void init_contact(Contact* contact);
void init_list(DoublyLinkedList *list);
void free_list(DoublyLinkedList *list);
ContactNode* create_node(Contact *contact);
void insert_node(DoublyLinkedList *list, ContactNode *new_node);
void delete_node(DoublyLinkedList *list, int id);
ErrorCode add_contact(DoublyLinkedList *list, const Contact* contact);
ErrorCode delete_contact(DoublyLinkedList *list, int id);
ErrorCode edit_contact(DoublyLinkedList *list, int id, const Contact* updated_contact);
ErrorCode find_contact(DoublyLinkedList *list, char* surname, char* name, int** ids, int* match_count);

#endif