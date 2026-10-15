#include <stdio.h>
#include <stdlib.h>
#include "console.c"
#include "tape.h"
#include "rules.c"

struct Machine {
    struct Rule** rules;
    struct String* alphabet;
    int states;
};


struct Machine* create(); // +
struct Machine* load(); // -
struct Machine* generate(); // +
// int save(struct Machine* machine); //
int process(struct Machine* machine, struct Tape* head, int startPos, int startState, int finishState); // +-
void freeMachine(struct Machine* machine); // -

struct Machine* generate() {
    struct Machine* machine = malloc(sizeof(struct Machine));
    machine->rules = malloc(2 * sizeof(struct Rule*));
    machine->states = 0;

    machine->alphabet = malloc(sizeof(struct String));
    machine->alphabet->capacity = 12;
    machine->alphabet->length = 11;
    machine->alphabet->data = "#0123456789";
    // machine->alphabet->data = malloc(machine->alphabet->capacity * sizeof(char));

    int* values = getFormulaValues();

    int mulValue = values[0];
    int addValue = values[1];
    
    machine->states = generateRules(&machine->rules, *machine->alphabet, mulValue, addValue);

    return machine;
}

int process(struct Machine* machine, struct Tape* head, int startPos, int startState, int finishState) {
    // нужно на всякий случай ещё принимать то, откуда начинать
    int state = startState;
    struct Rule rule;
    int row, column;
    

    while (state != finishState) {
        row = state - 1;
        column = findStringSymbol(*machine->alphabet, head->item);

        if (row < 0 || column == -1) {
            printf("ERROR, INVALID ROWS AND COLUMNS. EXITING.");
            return -1;
        }

        rule = machine->rules[row][column];

        head->item = rule.item;
        state = rule.state;

        if (rule.move == -1) {
            if (head->left == NULL) {
                struct Tape* lHead = malloc(sizeof(struct Tape));
                head->left = lHead;
                lHead->right = head;
                lHead->left = NULL;
                lHead->item = A0;
            }
            head = head->left;
        } else if (rule.move == 1) {
            if (head->right == NULL) {
                struct Tape* rHead = malloc(sizeof(struct Tape));
                head->right = rHead;
                rHead->left = head;
                rHead->right = NULL;
                rHead->item = A0;
            }
            head = head->right;
        }
    }
}

void freeMachine(struct Machine* machine) {
    freeRules(machine->rules, machine->alphabet->length, machine->states);
    free(machine);
}


// void process(struct Tape* head, struct Rule** rules, struct String alphabet) {
//     // нужно на всякий случай ещё принимать то, откуда начинать
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
