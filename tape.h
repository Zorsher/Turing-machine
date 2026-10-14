// Tape как абстракция над Cell - ячейкой плёнки + функции: заполнение, печать, высвобождение памяти, сохранение, загрузка
// ЧТО ЭТО ЧЁ КОМЕНТЫ В СИ? КОГДА КРУЖОЧКИ?
struct Tape
{
    unsigned char item;
    struct Tape* left;
    struct Tape* right;

};