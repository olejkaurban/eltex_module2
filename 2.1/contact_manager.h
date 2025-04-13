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

typedef struct {
    Contact* contacts;
    int count;
    int capacity;
    int max_id;
} ContactBook;

typedef enum {
    SUCCESS = 0,
    ERROR_MEMORY = 1,
    ERROR_NOT_FOUND = 2,
    ERROR_INVALID_INPUT = 3
} ErrorCode;

void init_contact(Contact* contact);
ErrorCode init_contact_book(ContactBook* book, int initial_capacity);
void free_contact_book(ContactBook* book);

ErrorCode add_contact(ContactBook* book, const Contact* contact);
ErrorCode delete_contact(ContactBook* book, int id);
ErrorCode edit_contact(ContactBook* book, int id, const Contact* updated_contact);
ErrorCode find_contact(ContactBook* book, char* surname, char* name, int** ids, int* match_count);
#endif