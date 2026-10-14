#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"
#include "console.c"
#include "rules.h"

int getFLine(FILE* file, struct String* buffer) {
    buffer->capacity = 10;
    buffer->length = 0;
    buffer->data = malloc(buffer->capacity * sizeof(char));
    buffer->data[0] = '\0';

    int symbol;

    while (1)
    {
        symbol = fgetc(file);

        if (symbol == '\n' || symbol == EOF) {
            // buffer->data[buffer->length] = '\0';
            break;
        }

        buffer->data[buffer->length] = symbol;
        buffer->length++;
        buffer->data[buffer->length] = '\0';

        if (buffer->capacity == buffer->length) {
            buffer->capacity+=10;
            buffer->data = realloc(buffer->data, buffer->capacity);
        }
    }

    if (symbol == EOF) {
        return -1;
    }

    return 0;
}

int main() {
    FILE* file = fopen("sheme.tm", "r");
    struct String* string = malloc(sizeof(struct String));
    int state, result, eventsCount;
    int row = -1;
    int tableP = 0;
    unsigned char symbol;

    struct String alphabet;
    struct String tmp;

    // должен ли я верить пидорасам юзерам? Наверное да
    struct Rule** rules;
    
    state = getFLine(file, string);
    printf("STROKA 1 %s, state %d\n", string->data, state);

    if (strcmp(string->data, "!turmachine!")) {
        printf("UNCORRECT FILE");
        freeString(string);
        return -1;
    }

    while (state != EOF) {
        state = getFLine(file, string);

        if (strstr(string->data, "EVENTS=")) {
            eventsCount = atoi(&(string->data)[7]);

            if (eventsCount == 0) {
                printf("ERROR, INVALID EVENTS COUNT. EXITING");
                return -1;
            }

            rules = malloc(eventsCount * sizeof(struct Rule*));
        }

        if (strstr(string->data, "ALPHABET=")) {
            tmp.data = &(string->data)[9];
            tmp.length = string->length-9;

            alphabet = getAlphabetFromString(tmp);

            if (alphabet.length == 1) {
                printf("ERROR, INVALID ALPHABET. EXITING");
                return -1;
            } 
        }

            if (strstr(string->data, "==END-TABLE==")) {
                row = -1;
            }
        
        if (row != -1) {
            printf("NASHEL STROKU %s %d\n", string->data, row);
            rules[row] = malloc(alphabet.length * sizeof(struct Rule));
            

            for (int i = 0; i < string->length; i++) {
                symbol = string->data[i];

                switch (tableP%4) {
                    case 0:
                    struct Rule rule;
                    rules[row][tableP/4] = rule;
                    
                    if (symbol == '#') {
                        symbol = A0;
                    }
                    
                    if (findStringSymbol(alphabet, symbol) == -1) {
                        // errorsCount?
                        printf("ERROR! RULE VALUE NOT IN ALPHABET! EXITING.\n");
                        return -1;
                    }

                    rules[row][tableP/4].item = symbol;
                    
                    tableP++;
                    break;
                    
                    case 1:
                    switch (symbol) {
                        case 'L':
                            rules[row][tableP/4].move = -1;
                            break;
                            
                        case 'S':
                            rules[row][tableP/4].move = 0;
                            break;
                            
                        case 'R':
                            rules[row][tableP/4].move = 1;
                            break;
                            
                        default:
                            printf("ERROR! UNCORRECT DIRECTION! EXITING\n");
                            return -1;
                        }
                        
                        tableP++;
                        break;
                        
                        case 2:
                            tmp.data[0] = '\0';
                            int res = getStringUntil(string, &tmp, i, ' ');

                            if (res == -1) {
                                res = getStringUntil(string, &tmp, i, '\0');
                            }

                            rules[row][tableP/4].state = atoi(tmp.data);
                            printf("RULE: %c, %d, %d\n", rules[row][tableP/4].item, rules[row][tableP/4].move, rules[row][tableP/4].state);

                            tableP++;
                            break;
                        case 3:
                            tableP++; // простите :(
                            break;
                    }                
                }

                
                row++;
            }

            if (strstr(string->data, "==START-TABLE==")) {
                row = 0;
            }

            
        }
        
        freeString(string); 
    }
    