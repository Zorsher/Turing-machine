#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

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
