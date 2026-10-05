#include <stdio.h>
#include <stdlib.h>
#include "tape.c"

struct Rule
{
    struct String item;
    int move;
    int state;
};

struct Rule createRule(struct String alphabet, int eventsCount) {
    struct Rule rule;
    struct String string;
    
    while (1) {
        printf("Alphabet value: ");
        string = getLine();

        if (!strcmp("a0", string.data) || atoi(string.data) == -1) {
            rule.item.data = NULL;
            break;
        }
        
        if (strstr(alphabet.data, string.data) != NULL) {
            rule.item = string;
            break;
        }

        printf("ERROR: you put a wrong value (%s)\n", string.data);
    }

    while (1)
    {
        printf("Enter action (L, S, R): ");
        char action = getChar();

        
        if (action == 'L') {
            rule.move = -1;
            break;
        } else if (action == 'S') {
            rule.move = 0;
            break;
        } else if (action == 'R') {
            rule.move = 1;
            break;
        }
        
        printf("ERROR: you put a wrong action (%s)\n", string.data);
    }

    while (1)
    {
        printf("Enter state: q");
        string = getLine();
        rule.state = atoi(string.data);

        if (rule.state <= eventsCount) {
            break;
        }

        printf("ERROR: you put a wrong event number (%s)", string);        
    }

    printf("\n");
    free(string.data);
    

    return rule;
}

// а NULL? + 1
struct Rule** createRules(struct String alphabet, int eventsCount) {
    struct Rule** rules = malloc(eventsCount * sizeof(struct Rule*));

    for (int i = 0; i < eventsCount; i++) {
        *(rules + i) = malloc(alphabet.length * sizeof(struct Rule));
        for (int j = 0; j < alphabet.length; j++) {
            // нужно добавить проверку на вводимые пользовательские данные
            printf("State q%d, Character ", i+1);

            if (alphabet.data[j] == -1) {
                printf("a0\n");
            } else {
                printf("%c\n", alphabet.data[j]);
            }

            *(*(rules + i) + j) = createRule(alphabet, eventsCount);

            // printf("put: %s; Move: %i; q:%i\n", (*(*(rules + i) + j)).item.data, (*(*(rules + i) + j)).move, (*(*(rules + i) + j)).state);
        }
    }

    return rules;
}

struct Rule findRule(struct Rule** rules, int row, char column) {
    // struct Rule rule;

    // for (int i = 0; i < row; i++) {
    //     for (int j = 0; j < column; j++) {
    //         rule = rules[i][j];
    //     }
    // }

    return rules[row][column];
}

void freeRules(struct Rule** rules, int alphabetLength, int eventsCount) {
    for (int i = 0; i < eventsCount; i++) {
        for (int j = 0; j < alphabetLength; j++) {
            free((rules[i][j]).item.data);
        }
        free(rules[i]);
    }
    free(rules);
}

void printRules(struct Rule** rules, struct String alphabet, int eventsCount) {
    char symbols[] = {'L', 'S', 'R'};

    printf("\t");
    printAlphabet(alphabet, '\t', '\n');

    for (int i = 0; i < eventsCount; i++) {
        printf("q%d", i);
        for (int j = 0; j < alphabet.length; j++) {
            struct Rule rule = rules[i][j];

            printf("\t%s%cq%d", rule.item.data, symbols[rule.move+1], rule.state);
        }
        printf("\n");
    }
}

void process(struct Tape* head, struct Rule** rules, struct String alphabet) {
    int state = 1;
    struct Rule rule;

    while (state != 0)
    {
        printf("row: %d, column %d (%c)\n", state, findAlphabetSymbol(alphabet, head->item), head->item);
        getchar();
        rule = findRule(rules, state-1, findAlphabetSymbol(alphabet, head->item));

        printf("ITEM: %s, Move: %d, STATE: %d", rule.item.data, rule.move, rule.state);

        getchar();


        head->item = rule.item.data[0];
        state = rule.state;

        if (rule.move == -1) {
            if (head->left == NULL) {
                struct Tape* lHead = malloc(sizeof(struct Tape));
                head->left = lHead;
                lHead->right = head;
                lHead->left = NULL;
                lHead->item = -1;
            }
            head = head->left;
        } else if (rule.move == 1) {
            if (head->right == NULL) {
                struct Tape* rHead = malloc(sizeof(struct Tape));
                head->right = rHead;
                rHead->left = head;
                rHead->right = NULL;
                rHead->item = -1;
            }
            head = head->right;
        }

    }
    

}

int main() {
    struct String alphabet = getAlphabet();
    // printAlphabet(alphabet, ' ', '\n');
    int eventsCount = getInt("Enter a events count: ");
    
    struct Rule** rules = createRules(alphabet, eventsCount);
    printRules(rules, alphabet, eventsCount);


    struct Tape* head = malloc(sizeof(struct Tape));
    fillTape(head);
    printTape(head);

    // надо сделать проверку на идиота
    int startPos = getInt("Enter a start position: ");

    for (int i = 0; i < startPos; i++) {
        if (head->right == NULL) {
            break;
        }
        head = head->right;
    }
    
    process(head, rules, alphabet);

    printTape(head);

    freeRules(rules, alphabet.length, eventsCount);
    free(alphabet.data);
    freeTape(head);
    
}

