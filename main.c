#include <stdio.h>
#include <stdlib.h>
// #include "tape.c"
// #include "rules.c"
#include "machine.c"


void fillTape(struct Tape* head) {
    printf("Enter a tape word: ");
    struct String string = getLine();
    head->left = NULL;
    head->right = NULL;

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

struct Tape* getHead(struct Tape* tape) {
    while (tape->left != NULL) {
        tape = tape->left;
    }
    return tape;
}

void printTape(struct Tape* head) {
    struct Tape* start = getHead(head);

    while (start != NULL) {
        if (start->item == '#' || start->item == A0) {

        } else {
            printf("%c", start->item);

        }

        start = start->right;
    }
}

void freeTape(struct Tape* head) {
    struct Tape* tmp;
    head = getHead(head);

    while (1)
    {
        tmp = head->right;
        
        if (head->right == NULL) {
            free(head);
            break;
        }

        free(head);

        head = tmp;
    } 
}




// void process(struct Tape* head, struct Rule** rules, struct String alphabet) {
//     int state = 1;
//     struct Rule rule;
//     int row, column;

//     while (state != 0) {
//         row = state - 1;
//         column = findStringSymbol(alphabet, head->item);

//         if (row < 0 || column == -1) {
//             printf("ERROR, INVALID ROWS AND COLUMNS. EXITING.");
//             return;
//         }

//         rule = rules[row][column];

//         head->item = rule.item;
//         state = rule.state;

//         if (rule.move == -1) {
//             if (head->left == NULL) {
//                 struct Tape* lHead = malloc(sizeof(struct Tape));
//                 head->left = lHead;
//                 lHead->right = head;
//                 lHead->left = NULL;
//                 lHead->item = A0;
//             }
//             head = head->left;
//         } else if (rule.move == 1) {
//             if (head->right == NULL) {
//                 struct Tape* rHead = malloc(sizeof(struct Tape));
//                 head->right = rHead;
//                 rHead->left = head;
//                 rHead->right = NULL;
//                 rHead->item = A0;
//             }
//             head = head->right;
//         }
//     }
// }


int main() {
    struct Tape* head = malloc(sizeof(struct Tape));
    fillTape(head);
    // int startPos = getInt("Enter a start position: ");

    printf("Enter a formula (a*n+b): ");

    struct Machine* machine = generate();
    printRules(machine->rules, *machine->alphabet, machine->states);


    struct Tape* current = head;

    while (current->right != NULL) {
        current = current->right;
    }

    process(machine, current, 0, 0, -1);
    printTape(head);

    // printf("DLINA %d\n", machine->alphabet->length);
    // process(machine, head, machine->alphabet->length, 0, -1);
    // printTape(head);

    // printf("%c %d %d", machine->rules[0][0].item, machine->rules[0][0].move, machine->rules[0][0].state);




    // struct String alphabet = getAlphabet();
    // int eventsCount = getInt("Enter a events count: ");
    
    // struct Rule** rules = createRules(alphabet, eventsCount);
    // printRules(rules, alphabet, eventsCount);



    // // надо сделать проверку на идиота

    // for (int i = 0; i < startPos; i++) {
    //     if (head->right == NULL) {
    //         break;
    //     }
    //     head = head->right;
    // }
    
    // process(head, rules, alphabet);

    // freeRules(rules, alphabet.length, eventsCount);
    // free(alphabet.data);
    // freeTape(head);
}
