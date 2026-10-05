#include <stdio.h>
#include <stdlib.h>
#include "console.c"


// Tape как абстракция над Cell - ячейкой плёнки + функции: заполнение, печать, высвобождение памяти, сохранение, загрузка
// ЧТО ЭТО ЧЁ КОМЕНТЫ В СИ? КОГДА КРУЖОЧКИ?
struct Tape
{
    char item;
    struct Tape* left;
    struct Tape* right;

};

void fillTape(struct Tape* head) {
    printf("Enter a tape word: ");
    struct String string = getLine();
    head->left = NULL;

    for (int i = 0; i < string.length; i++) {
        head->item = string.data[i];

        if (i + 1 != string.length) {
            struct Tape* next = malloc(sizeof(struct Tape));
            head->right = next;
            next->left = head;
            next->right = NULL;
            head = head->right;
        } 
    }
    free(string.data);
}

void printTape(struct Tape* head) {
    struct Tape* start = head;

    while (start->left != NULL) {
        start = start->left;
    }

    while (start != NULL) {
        printf("%c ", start->item);
        start = start->right;
    }
}

void freeTape(struct Tape* head) {
    struct Tape* tmp;
    while (1)
    {
        tmp = head->right;
        free(head);

        if (head->right == NULL) {
            break;
        }

        head = tmp;
    }
    
}