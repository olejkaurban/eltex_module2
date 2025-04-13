#ifndef MENU_H
#define MENU_H

#include "contact_manager.h"


void input_string(const char* message, char* field, int size, const char* default_value);
void input_contact(Contact* contact, int id);
void find_ids(ContactBook* book, int** ids, int* match_count);
void edit_contact_menu(ContactBook* book, int id);
void menu(ContactBook* book);
void print_menu();
void print_error(ErrorCode error);
void print_contact(const Contact* contact);
void select_id(int* selected_id, int* ids, int match_count);
void clear_input_buffer();

#endif