#include "menu.h"
#include "contact_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void input_string(const char* message, char* field, int size, const char* default_value) {
    if (message != NULL) {
        printf("%s", message);
        fflush(stdout);
    }
    
    fgets(field, size, stdin);
    field[strcspn(field, "\n")] = '\0';

    if (field[0] == '\0' && default_value != NULL) {
        strncpy(field, default_value, size - 1);
        field[size - 1] = '\0';
    }
}

void input_contact(Contact* contact, int id) {
    contact->id = id;

    printf("Введите информацию для контакта:\n");
    do {
        input_string("Введите Фамилию: ", contact->surname, sizeof(contact->surname), "");
    } while (contact->surname[0] == '\0');
    do {
        input_string("Введите Имя: ", contact->name, sizeof(contact->name), "");
    } while (contact->name[0] == '\0') ;

    char answer[3];
    input_string("Хотите ввести дополнительную информацию? (Д/Н): ", answer, sizeof(answer), "Н");
    clear_input_buffer();
    if (strcmp(answer, "Д") == 0 || strcmp(answer, "д") == 0) {
        
        printf("\nДля пропуска поля нажмите Enter.\n");
        input_string("Введите Отчество: ", contact->info.patronymic, sizeof(contact->info.patronymic), "");
        input_string("Введите Место работы: ", contact->info.job_place, sizeof(contact->info.job_place), "");
        input_string("Введите Должность: ", contact->info.job_title, sizeof(contact->info.job_title), "");
        input_string("Введите Телефон: ", contact->info.phone, sizeof(contact->info.phone), "");
        input_string("Введите Почту: ", contact->info.mail, sizeof(contact->info.mail), "");
        input_string("Введите Ссылки: ", contact->info.links, sizeof(contact->info.links), "");
    }
}

void find_ids(ContactBook* book, int** ids, int* match_count) {
    char surname[MAX_STRING], name[MAX_STRING];
    input_string("Введите фамилию: ", surname, sizeof(surname), "");
    input_string("Введите имя: ", name, sizeof(name), "");
    ErrorCode error = find_contact(book, surname, name, ids, match_count);
    if (error != SUCCESS) {
        print_error(error);
    }
}

void edit_contact_menu(ContactBook* book, int id) {
    int index = -1;
    for (int i = 0; i < book->count; i++) {
        if (book->contacts[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Контакт с ID %d не найден.\n", id);
        return;
    }

    printf("Текущие данные контакта:\n");
    print_contact(&book->contacts[index]);

    Contact updated_contact = book->contacts[index];
    int choice;
    do {
        printf("\nВыберите поле для редактирования:\n");
        printf("1. Фамилия\n");
        printf("2. Имя\n");
        printf("3. Отчество\n");
        printf("4. Место работы\n");
        printf("5. Должность\n");
        printf("6. Телефон\n");
        printf("7. Почта\n");
        printf("8. Ссылки\n");
        printf("0. Сохранить и выйти\n");
        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                input_string("Введите новую фамилию: ", updated_contact.surname, sizeof(updated_contact.surname), updated_contact.surname);
                break;
            case 2:
                input_string("Введите новое имя: ", updated_contact.name, sizeof(updated_contact.name), updated_contact.name);
                break;
            case 3:
                input_string("Введите новое отчество: ", updated_contact.info.patronymic, sizeof(updated_contact.info.patronymic), updated_contact.info.patronymic);
                break;
            case 4:
                input_string("Введите новое место работы: ", updated_contact.info.job_place, sizeof(updated_contact.info.job_place), updated_contact.info.job_place);
                break;
            case 5:
                input_string("Введите новую должность: ", updated_contact.info.job_title, sizeof(updated_contact.info.job_title), updated_contact.info.job_title);
                break;
            case 6:
                input_string("Введите новый телефон: ", updated_contact.info.phone, sizeof(updated_contact.info.phone), updated_contact.info.phone);
                break;
            case 7:
                input_string("Введите новую почту: ", updated_contact.info.mail, sizeof(updated_contact.info.mail), updated_contact.info.mail);
                break;
            case 8:
                input_string("Введите новые ссылки: ", updated_contact.info.links, sizeof(updated_contact.info.links), updated_contact.info.links);
                break;
            case 0:
                break;
            default:
                printf("Некорректный выбор.\n");
        }
    } while (choice != 0);

    ErrorCode error = edit_contact(book, id, &updated_contact);
    if (error == SUCCESS) {
        printf("Контакт с ID %d отредактирован.\n", id);
    } else {
        print_error(error);
    }
}

void menu(ContactBook* book) {
    int choice;
    do {
        print_menu();

        int result = scanf("%d", &choice);
        if (result == EOF) {
            printf("Программа завершена.\n");
            break;
        }
        if (result != 1) {
            printf("Некорректный ввод.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {//Показать контакты
                if (book->count == 0) {
                    printf("Список контактов пуст.\n");
                } else {
                    printf("Все контакты:\n");
                    for (int i = 0; i < book->count; i++) { 
                        print_contact(&book->contacts[i]);
                    }
                }
                break;
            }

            case 2: {//Найти контакт
                int* ids = NULL;
                int match_count = 0;

                find_ids(book, &ids, &match_count);

                if (match_count == 0) {
                    printf("Контакт не найден.\n");
                } else {
                    for (int i = 0; i < match_count; i++) {
                        for (int j = 0; j < book->count; j++) {
                            if (book->contacts[j].id == ids[i]) {
                                print_contact(&book->contacts[j]);
                            }
                        }
                    }
                }
                free(ids);
                break;
            }

            case 3: {//Добавить контакт
                Contact new_contact;
                init_contact(&new_contact);
                input_contact(&new_contact,book->max_id + 1);
                ErrorCode error = add_contact(book, &new_contact);
                if (error == SUCCESS) {
                    printf("Контакт добавлен.\n");
                } else {
                    print_error(error);
                }
                break;
            }

            case 4: {//Удалить контакт
                int* ids = NULL;
                int match_count = 0;
                ErrorCode error;

                find_ids(book, &ids, &match_count);

                if (match_count == 0) {
                    printf("Контакт не найден.\n");
                } else if (match_count == 1) {
                    error = delete_contact(book, ids[0]);
                    if (error == SUCCESS) {
                        printf("Контакт удалён.\n");
                    } else {
                        print_error(error);
                    }
                } else {
                    printf("Найдено несколько совпадений:\n");
                    for (int i = 0; i < match_count; i++) {
                        for (int j = 0; j < book->count; j++) {
                            if (book->contacts[j].id == ids[i]) {
                                print_contact(&book->contacts[j]);
                            }
                        }
                    }
                    int selected_id;
                    select_id(&selected_id, ids, match_count);
                    if (selected_id == 0 || selected_id == -1) {
                        printf("Действие отменено.");
                    } else {
                        error = delete_contact(book, selected_id);
                        if (error == SUCCESS) {
                            printf("Контакт удалён.\n");
                        } else {
                            print_error(error);
                        }
                    }
                }
                free(ids);
                break;
            }

            case 5: {//Редактировать контакт
                int* ids = NULL;
                int match_count = 0;

                find_ids(book, &ids, &match_count);

                if (match_count == 0) {
                    printf("Контакт не найден.\n");
                } else if (match_count == 1) {
                    edit_contact_menu(book, ids[0]);
                } else {
                    printf("Найдено несколько совпадений:\n");
                    for (int i = 0; i < match_count; i++) {
                        for (int j = 0; j < book->count; j++) {
                            if (book->contacts[j].id == ids[i]) {
                                print_contact(&book->contacts[j]);
                            }
                        }
                    }
                    int selected_id;
                    select_id(&selected_id, ids, match_count);
                    if (selected_id == 0) {
                        printf("Действие отменено.");
                    } else {
                        edit_contact_menu(book, selected_id);
                    }
                }
                free(ids);
                break;
            }

            case 0: // Выход
                break;

            default:
                printf("Некорректный выбор.\n");
        }
    } while (choice != 0);
}

void print_menu() {
    printf("\n      Меню:\n");
    printf("1. Показать все контакты\n");
    printf("2. Найти контакт\n");
    printf("3. Добавить контакт\n");
    printf("4. Удалить контакт\n");
    printf("5. Редактировать контакт\n");
    printf("0. Выход\n");
    printf("Ваш выбор: ");
}

void print_contact(const Contact* contact) {
    printf("\nКонтакт %d\n", contact->id);
    printf("Фамилия: %s\n", contact->surname);
    printf("Имя: %s\n", contact->name);
    printf("Отчество: %s\n", contact->info.patronymic);
    printf("Место работы: %s\n", contact->info.job_place);
    printf("Должность: %s\n", contact->info.job_title);
    printf("Телефон: %s\n", contact->info.phone);
    printf("Почта: %s\n", contact->info.mail);
    printf("Ссылки: %s\n", contact->info.links);
}

void print_error(ErrorCode error) {
    switch (error) {
        case ERROR_MEMORY:
            printf("Ошибка: недостаточно памяти.\n");
            break;
        case ERROR_NOT_FOUND:
            printf("Ошибка: контакт не найден.\n");
            break;
        case ERROR_INVALID_INPUT:
            printf("Ошибка: некорректный ввод.\n");
            break;
        case SUCCESS:
        default:
            break;
    }
}

void select_id(int* selected_id, int* ids, int match_count) {
    int result;
    int valid_id;
    do {
        printf("Введите ID контакта (0 для отмены): ");
        result = scanf("%d", selected_id);

        if (result == EOF) {
            *selected_id = -1;
            return;
        }

        if (result != 1) {
            printf("Некорректный ввод. Попробуйте снова.\n");
            while (getchar() != '\n');
            continue;
        }

        if (*selected_id == 0) {
            return;
        }

        valid_id = 0;
        for (int i = 0; i < match_count; i++) {
            if (ids[i] == *selected_id) {
                valid_id = 1;
                break;
            }
        }

        if (!valid_id) {
            printf("Введен некорректный ID. Попробуйте снова.\n");
        }
    } while (result != 1 || !valid_id);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}