#include <stdio.h>
#include <stdlib.h>

struct Rule
{
    char item;
    int move;
    int state;
};

int getSymbolIndex(char alphabet[], int alphabetLen, char symbol) {
    int result = -1;
    for (int i = 0; i < alphabetLen; i++) {
        if (alphabet[i] == symbol) {
            result = i;
            break;
        }
    }

    return result;
}


int main() {
    char alphabet[3] = {'\0', '1', '2'};
    // char states[2] = {'0', '1'};

    char tape[1024] = "12212";
    struct Rule rules[][3] = {
    //        \0          1              2
        {{'1', 0, 0}, {'2', 1, 1}, {'1', 1, 1}} // q1
    };

    //   #      1
    //  1Нq0   1Пq1
    // struct Rule r = {'1', 0, 0};
    // struct Rule one = {'1', 1, 1};
    
    printf("%s\n", tape);

    struct Rule currentRule;

    int index = 0;
    int state = 1;

    // int i = 1;
    int j;

    while (state != 0)
    {
        j = getSymbolIndex(alphabet, sizeof(alphabet)/sizeof(alphabet[0]), tape[index]);

        //printf("ya poluchil %d %c %d\n", j, tape[index], sizeof(alphabet)/sizeof(alphabet[0]));

        if (j == -1) {
            break;
        }

        currentRule = rules[0][j];

        printf("%c {%d} -> %c (%d) (%d -> %d), q%d -> q%d\n", tape[index], tape[index], currentRule.item, currentRule.item, index, index+currentRule.move, state, currentRule.state);

        tape[index] = currentRule.item;
        index += currentRule.move;
        state = currentRule.state;

    }

    printf("%s\n", tape);
    

    return 0;
}

  