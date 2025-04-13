#include "menu.h"
#include <stdio.h>
 
int main() {
    DoublyLinkedList list;
    
    init_list(&list);
    menu(&list);
    free_list(&list);

    return 0;
}