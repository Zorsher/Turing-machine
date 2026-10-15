#include <stdio.h>
#include <stdlib.h>
// #include "tape.c"
// #include "rules.c"
#include "machine.c"

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
    struct Machine* machine = generate();

    // printf("%c %d %d", machine->rules[0][0].item, machine->rules[0][0].move, machine->rules[0][0].state);

    printRules(machine->rules, *machine->alphabet, machine->states);

    // struct String alphabet = getAlphabet();
    // int eventsCount = getInt("Enter a events count: ");
    
    // struct Rule** rules = createRules(alphabet, eventsCount);
    // printRules(rules, alphabet, eventsCount);


    // struct Tape* head = malloc(sizeof(struct Tape));
    // fillTape(head);

    // // надо сделать проверку на идиота
    // int startPos = getInt("Enter a start position: ");

    // for (int i = 0; i < startPos; i++) {
    //     if (head->right == NULL) {
    //         break;
    //     }
    //     head = head->right;
    // }
    
    // process(head, rules, alphabet);
    // printTape(head);

    // freeRules(rules, alphabet.length, eventsCount);
    // free(alphabet.data);
    // freeTape(head);
}
