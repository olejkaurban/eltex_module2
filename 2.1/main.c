#include "menu.h"
#include <stdio.h>
 
int main() {
    ContactBook book;
    if (init_contact_book(&book, 10) != SUCCESS) {
        printf("Не удалось инициализировать телефонную книгу.\n");
        return 1;
    }

    menu(&book);
    free_contact_book(&book);
    return 0;
}