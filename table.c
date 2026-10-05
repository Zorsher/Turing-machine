#include <stdio.h>
#include <stdlib.h>
#include "console.c"
#include "tape.c"

// load, free, save?
struct Rule
{
    char item;
    int move;
    int state;
};

struct Rule createRule() {
    struct Rule rule;
    struct String string;
    printf("Enter you item: ");
    rule.item = getChar(); // надо будет сделать поддержку строк, вместо символов
    printf("Enter action (L, S, R): ");
    rule.move = getChar();
    printf("Enter state: ");
    string = getLine();
    rule.state = atoi(string.data);
    free(string.data);
    

    return rule;
}

struct Rule** createRules(struct String alphabet, int eventsCount) {
    struct Rule** rules = malloc(eventsCount * sizeof(struct Rule*));

    for (int i = 0; i < eventsCount; i++) {
        *(rules + i) = malloc(alphabet.length * sizeof(struct Rule));
        for (int j = 0; j < alphabet.length; j++) {
            // нужно добавить проверку на вводимые пользовательские данные
            *(*(rules + i) + j) = createRule();
        }
    }

    return rules;
}