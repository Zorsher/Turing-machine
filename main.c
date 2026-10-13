#include <stdio.h>
#include <stdlib.h>
#include "tape.c"

struct Rule
{
    unsigned char item;
    int move;
    int state;
};

struct Rule createRule(struct String alphabet, int eventsCount) {
    struct Rule rule;
    struct String string;
    char symbol;
    
    while (1) {
        printf("Enter alphabet symbol: ");

        symbol = getChar();

        // состояние a0
        if (symbol == '#') {
            rule.item = A0;
            break;
        }
            
        if (strchr(alphabet.data, symbol) != NULL) {
            rule.item = symbol;
            break;
        }

        printf("ERROR: you put a wrong value (%c)\n", symbol);
    }

    while (1)
    {
        printf("Enter action (L, S, R): ");
        symbol = getChar();

        if (symbol == 'L') {
            rule.move = -1;
            break;
        } else if (symbol == 'S') {
            rule.move = 0;
            break;
        } else if (symbol == 'R') {
            rule.move = 1;
            break;
        }
        
        printf("ERROR: you put a wrong action (%c)\n", symbol);
    }

    while (1)
    {
        printf("Enter state: q");
        string = getLine();
        rule.state = atoi(string.data);

        if (rule.state <= eventsCount) {
            break;
        }

        printf("ERROR: you put a wrong event number (%s)", string.data);        
    }

    printf("\n");
    free(string.data);
    
    return rule;
}

// а NULL? + 1
struct Rule** createRules(struct String alphabet, int eventsCount) {
    struct Rule** rules = malloc(eventsCount * sizeof(struct Rule*));

    for (int i = 0; i < eventsCount; i++) {
        // *(rules + i) = malloc(alphabet.length * sizeof(struct Rule));
        rules[i] = malloc(alphabet.length * sizeof(struct Rule));
        for (int j = 0; j < alphabet.length; j++) {
            // нужно добавить проверку на вводимые пользовательские данные
	        printf("State q%d ",i+1);
            if (alphabet.data[j] == A0) {
                printf("symbol a0\n");
            } else {
                printf("symbol %c\n", alphabet.data[j]);
            }
            // *(*(rules + i) + j) = createRule(alphabet, eventsCount);
            rules[i][j] = createRule(alphabet, eventsCount);
            // printf("put: %s; Move: %i; q:%i\n", (*(*(rules + i) + j)).item.data, (*(*(rules + i) + j)).move, (*(*(rules + i) + j)).state);
        }
    }

    return rules;
}

void freeRules(struct Rule** rules, int alphabetLength, int eventsCount) {
    for (int i = 0; i < eventsCount; i++) {
        for (int j = 0; j < alphabetLength; j++) {
            // free((rules[i][j]).item.data);
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

            printf("\t%c%cq%d", rule.item, symbols[rule.move+1], rule.state);
        }
        printf("\n");
    }
}

void process(struct Tape* head, struct Rule** rules, struct String alphabet) {
    int state = 1;
    struct Rule rule;

    while (state != 0) {
        rule = rules[state-1][findAlphabetSymbol(alphabet, head->item)];

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

int main() {
    struct String alphabet = getAlphabet();
    int eventsCount = getInt("Enter a events count: ");
    
    struct Rule** rules = createRules(alphabet, eventsCount);
    printRules(rules, alphabet, eventsCount);


    struct Tape* head = malloc(sizeof(struct Tape));
    fillTape(head);

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
