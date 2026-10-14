#include <stdio.h>
#include "console.h"
#include "tape.h"
#include "rules.h"

struct Machine {
    struct Rule** rules;
    struct String* alphabet;
    int states;
};


struct Machine* create(); // +
struct Machine* load(); // +-
int save(struct Machine* machine); //
int process(struct Machine* machine, int startPos, int startState); // +-
void free(struct Machine* machine); // -



void process(struct Tape* head, struct Rule** rules, struct String alphabet) {
    // нужно на всякий случай ещё принимать то, откуда начинать
    int state = 1;
    struct Rule rule;
    int row, column;

    while (state != 0) {
        row = state - 1;
        column = findStringSymbol(alphabet, head->item);

        if (row < 0 || column == -1) {
            printf("ERROR, INVALID ROWS AND COLUMNS. EXITING.");
            return;
        }

        rule = rules[row][column];

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