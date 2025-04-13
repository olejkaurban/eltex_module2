#include <stdio.h>
#include "menu.h"
#include "calculator.h"

void menu() {
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

        switch (choice) {
            case 1: { // Сложение

            }
            case 2: { // Вычитание

            }
            case 3: { // Умножение

            }
            case 4: { // Деление

            }
            case 0: // Выход
                break;

            default:
                printf("Некорректный выбор.\n");
        }


    } while (choice != 0);
} 

void input_args(int count, int* args) {
    printf("Введите количество аргументов: ", &count);
    
}

void print_menu() {
    printf("\tМеню:");
    printf("1. Сложение");
    printf("2. Вычитание");
    printf("3. Умножение");
    printf("4. Деление");
    printf("0. Выход");
    printf("Ваш выбор: ");
}

void print_error(ErrorCode error) {
    switch (error) {
        case ERROR_ZERO:
            printf("Ошибка: деление на ноль.\n");
            break;
        case SUCCESS:
        default:
            break;
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}