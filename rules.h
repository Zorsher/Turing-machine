struct Rule
{
    unsigned char item;
    int move;
    int state;
};

void printRules(struct Rule** rules, struct String alphabet, int eventsCount);