#define A0 220

struct String {
    unsigned char* data;
    int length;
    int capacity;
};

struct String getLine();
struct String getAlphabet();
struct String getLine();
int cropString(struct String* string, struct String* output, int start, int end);

char getChar();
int getInt(char* print);

int findStringSymbol(struct String string, unsigned char symbol);
void printAlphabet(struct String alphabet, char separator, char endLine);
void freeString(struct String* string);


// сделать понятный срез строки. cropString?