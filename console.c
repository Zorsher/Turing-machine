#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

int findStringSymbol(struct String string, unsigned char symbol) {
    int index = -1;

    if (symbol == '#' || symbol == A0) {
        return 0;
    }

    
    for (int i = 0; i < string.length; i++) {
        if (string.data[i] == symbol) {
            index = i;
            break;
        }
    }
    return index;
}

// возвращает индекс конца строки или -1
int cropString(struct String* string, struct String* output, int start, int end) {
    int delta = end - start;

    if (delta <= 0) {
        return -1;
    }

    output->capacity = delta + 1;
    output->length = delta;    
    output->data = malloc((output->capacity)*sizeof(char));

    for (int i = 0; i < delta; i++) {
        output->data[i] = string->data[start + i];
    }

    output->data[output->length] = '\0';

    return end;
}

// возвращает индекс конца строки или -1
int getStringUntil(struct String* string, struct String* output, int start, char symbol) {
    struct String tmp;
    tmp.data = &string->data[start];
    tmp.capacity = string->capacity-start;
    tmp.length = string->capacity-start;

    int index = findStringSymbol(tmp, symbol);

    // printf("MY INDEX IS: %d, i %d, s %d\n", index+start, index, start);
    
    if (index == -1) {
        // printf("ERROR, SYMBOL NOT FOUND\n");
        return -1;
    }

    // cropString(string, output, start, index);

    return cropString(string, output, start, index+start);
}

// до лучших времён
void freeString(struct String* string) {
    free(string->data);
    free(string);
}

int* getFormulaValues(){
    int result[2] = {-1, -1};
    int* resultP = result;
    
    struct String mulValue;
    struct String addValue;
    struct String string = getLine();


    int mulP = findStringSymbol(string,'*');
    int addP = findStringSymbol(string,'+');

    if (mulP == -1 || addP==-1){
        printf("ERROR, WRONG FORMULA.EXAMPLE: 23*n+346");
        return resultP;
    }

    cropString(&string, &mulValue, 0, mulP);
    cropString(&string, &addValue, addP+1, string.length);

    resultP[0]=atoi(mulValue.data);
    resultP[1]=atoi(addValue.data);

    free(string.data);

    return resultP;
}

struct String getAlphabet() {
    struct String string;

    string.capacity = 10;
    string.length = 1;
    string.data = malloc(string.capacity * sizeof(char));
    string.data[0] = A0;

    int step = 10;

    while (1)
    {
        printf("Enter a value: ");
        string.data[string.length] = getChar();

        // начальный символ алфавита a0
        if (string.data[string.length] == '#') {
            printf("Error! You put a reserve symbol '#'. Try again!\n");
            continue;
        }

        if (string.data[string.length] == '\0') {
            break;
        }

        string.length++;

        if (string.capacity == string.length) {
            string.capacity+=step;
            string.data = realloc(string.data, string.capacity);
        }  
    }

    return string;
}

// перестать спрашивать у пользователя символы по отдельности и юзать это?
struct String getAlphabetFromString(struct String string) {
    struct String alphabet;

    alphabet.capacity = 10;
    alphabet.length = 1;
    alphabet.data = malloc(alphabet.capacity * sizeof(char));
    alphabet.data[0] = A0;
    alphabet.data[1] = '\0';

    int step = 10;

    for (int i = 0; i < string.length; i++) {
        if (strchr(alphabet.data, string.data[i]) != NULL) {
            continue;
        }

        alphabet.data[alphabet.length] = string.data[i];

        alphabet.length++;

        if (alphabet.capacity == alphabet.length) {
            alphabet.capacity+=step;
            alphabet.data = realloc(alphabet.data, alphabet.capacity);
        }          
    }

    return alphabet;

}

void printAlphabet(struct String alphabet, char separator, char endLine) {
    for (int i = 0; i < alphabet.length; i++) {
        if (alphabet.data[i] == A0 || alphabet.data[i] == '#') {
            printf("a0%c", separator);
        } else {
            printf("%c%c", alphabet.data[i], separator);
        }
    }
    printf("%c", endLine);
}

struct String getLine() {
    struct String string;

    string.capacity = 10;
    string.length = 0;
    string.data = malloc(string.capacity * sizeof(char));

    int step = 10;
    int symbol;

    while (1)
    {
        symbol = getchar();

        if (symbol == '\n') {
            string.data[string.length] = '\0';
            break;
        }

        string.data[string.length] = symbol;

        string.length++;

        if (string.capacity == string.length) {
            string.capacity+=step;
            string.data = realloc(string.data, (string.capacity));
        }  
    }
    return string;
}

char getChar() {
    struct String string = getLine();
    char symbol = string.data[0];
    free(string.data);
    return symbol;
}

int getInt(char* print) {
    printf(print);
    struct String string = getLine();
    
    int result = atoi(string.data);

    free(string.data);

    return result;
}
