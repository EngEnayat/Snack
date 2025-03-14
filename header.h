#ifndef HEADER_H
#define HEADER_H
#include <iostream>

void gotoxy(int x, int y);
char getKeyPress();
void clearScreen();
char getKey();
void getMaxWindowSize(int &rows, int &cols);
bool kbhit();
enum Direction { UP, DOWN, LEFT, RIGHT };
void function(Direction &direction);
void random_number();
extern Direction direction;
extern int x, y;
extern bool swUp, swDown, swRight, swLeft;
#endif
