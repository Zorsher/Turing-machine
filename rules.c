#include "rules.h"
#include "tmfile.c"

struct Rule createRule(struct String alphabet, int eventsCount) {
    struct Rule rule;
    struct String string;
    char symbol;
    
    while (1) {
        printf("Enter alphabet symbol: ");

        symbol = getChar();

        // начальный символ алфавита a0
        if (symbol == '#') {
            rule.item = A0;
            break;
        }
        
        if (findStringSymbol(alphabet, symbol) != -1) {
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

// возвращает количество состояний
int generateRules(struct Rule*** rules, struct String alphabet, int mulValue, int addValue){
    int lastState = 1; 
    int result, state;
    unsigned char putItem, symbol;
    int i;

    
    for (i = 0; i < lastState+1; i++) {
        // printf("WORKING WITH STATE %d\n", i);
        (*rules)[i] = malloc(alphabet.length * sizeof(struct Rule));
        for (int j = 0; j < alphabet.length; j++) {
            symbol = alphabet.data[j];

            // A0
            if (symbol != '#') {
                if (i == 0) {
                    result = mulValue*(symbol - '0') + addValue;
                } else {
                    result = mulValue*(symbol - '0') + i-1;
                }
                putItem = result % 10 + '0';
                state = (result/10)+1;
            } else {
                if (i == 0) {
                    result = addValue;
                } else {
                    result = i-1;
                }

                if (result == 0) {
                    putItem = A0;
                    state = -1;
                } else {
                    putItem = result % 10 + '0';
                    state = result / 10 + 1;
                }
            }

            if (state > lastState) {
                lastState = state;
                struct Rule** temp = realloc(*rules, (lastState + 1) * sizeof(struct Rule*));
                *rules = temp;
            }

            (*rules)[i][j].item = putItem;
            (*rules)[i][j].move = -1;
            (*rules)[i][j].state = state;
        }  
    }

    // printf("\n");
    // printRules(rules, alphabet, i);

    // printf("STATES %d", i);

    return i;
}

// int loadRules(char* filename, struct Rule** rules) {
//     FILE* file = fopen(filename, "r");
//     struct String* string = malloc(sizeof(struct String));
//     int state, result, eventsCount;
//     int row = -1;
//     int tableP = 0;
//     unsigned char symbol;

//     struct String alphabet;
//     struct String tmp;
    
//     state = getFLine(file, string);
//     printf("STROKA 1 %s, state %d\n", string->data, state);

//     if (strcmp(string->data, "!turmachine!")) {
//         printf("UNCORRECT FILE");
//         freeString(string);
//         return -1;
//     }

//     while (state != EOF) {
//         state = getFLine(file, string);

//         if (strstr(string->data, "EVENTS=")) {
//             eventsCount = atoi(&(string->data)[7]);

//             if (eventsCount == 0) {
//                 printf("ERROR, INVALID EVENTS COUNT. EXITING");
//                 return -1;
//             }

//             rules = malloc(eventsCount * sizeof(struct Rule*));
//         }

//         if (strstr(string->data, "ALPHABET=")) {
//             tmp.data = &(string->data)[9];
//             tmp.length = string->length-9;

//             alphabet = getAlphabetFromString(tmp);

//             if (alphabet.length == 1) {
//                 printf("ERROR, INVALID ALPHABET. EXITING");
//                 return -1;
//             } 
//         }

//             if (strstr(string->data, "==END-TABLE==")) {
//                 row = -1;
//             }
        
//         if (row != -1) {
//             printf("NASHEL STROKU %s %d\n", string->data, row);
//             rules[row] = malloc(alphabet.length * sizeof(struct Rule));
            

//             for (int i = 0; i < string->length; i++) {
//                 symbol = string->data[i];

//                 switch (tableP%4) {
//                     case 0:
//                     struct Rule rule;
//                     rules[row][tableP/4] = rule;
                    
//                     if (symbol == '#') {
//                         symbol = A0;
//                     }
                    
//                     if (findStringSymbol(alphabet, symbol) == -1) {
//                         // errorsCount?
//                         printf("ERROR! RULE VALUE NOT IN ALPHABET! EXITING.\n");
//                         return -1;
//                     }

//                     rules[row][tableP/4].item = symbol;
                    
//                     tableP++;
//                     break;
                    
//                     case 1:
//                     switch (symbol) {
//                         case 'L':
//                             rules[row][tableP/4].move = -1;
//                             break;
                            
//                         case 'S':
//                             rules[row][tableP/4].move = 0;
//                             break;
                            
//                         case 'R':
//                             rules[row][tableP/4].move = 1;
//                             break;
                            
//                         default:
//                             printf("ERROR! UNCORRECT DIRECTION! EXITING\n");
//                             return -1;
//                         }
                        
//                         tableP++;
//                         break;
                        
//                         case 2:
//                             tmp.data[0] = '\0';
//                             int res = getStringUntil(string, &tmp, i, ' ');

//                             if (res == -1) {
//                                 res = getStringUntil(string, &tmp, i, '\0');
//                             }

//                             rules[row][tableP/4].state = atoi(tmp.data);
//                             printf("RULE: %c, %d, %d\n", rules[row][tableP/4].item, rules[row][tableP/4].move, rules[row][tableP/4].state);
//                             // printf("current i %d, after until %d\n",i,res);
//                             i=i+(res-i-1);
//                             // printf("after changes i %d\n",i);

//                             tableP++;
//                             break;
//                         case 3:
//                             tableP++; 
//                             break;
//                     }                
//                 }

                
//                 row++;
//             }

//             if (strstr(string->data, "==START-TABLE==")) {
//                 row = 0;
//             }
//         }
        
//     freeString(string);
//     return 0;
// }

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
            char *item;
            
            if (rule.item == A0) {
                item = "a0";
            } else {
                item = &rule.item;

            }

            printf("\t%s%cq%d", item, symbols[rule.move+1], rule.state);
        }
        printf("\n");
    }
}
