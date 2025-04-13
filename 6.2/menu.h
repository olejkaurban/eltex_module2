#ifndef MENU_H
#define MENU_H

#include "contact_manager.h"

void input_string(const char* message, char* field, int size, const char* default_value);
void input_contact(Contact* contact, int id);

void edit_contact_menu(DoublyLinkedList* list, int id);
void menu(DoublyLinkedList* list);
void print_menu() ;
void print_contact(const Contact* contact);
void print_error(ErrorCode error);
void find_ids(DoublyLinkedList* list, int** ids, int* match_count);
void select_id(int* selected_id, int* ids, int match_count);
void clear_input_buffer();

#endif