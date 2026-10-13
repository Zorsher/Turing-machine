#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A0 220

struct String {
    unsigned char* data;
    int length;
    int capacity;
};


struct String getLine();
char getChar();

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
            string.data = realloc(string.data, (string.capacity));
        }  
    }

    return string;
}

int findAlphabetSymbol(struct String alphabet, unsigned char symbol) {
    int index = -1;
    
    for (int i = 0; i < alphabet.length; i++) {
        if (alphabet.data[i] == symbol) {
            index = i;
            break;
        }
    }

    return index;
}

void printAlphabet(struct String alphabet, char separator, char endLine) {
    for (int i = 0; i < alphabet.length; i++) {
        if (alphabet.data[i] == A0) {
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
