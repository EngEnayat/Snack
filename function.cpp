#include "header.h"
#include <iostream>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

#include <sys/ioctl.h>
#include <unistd.h>

int x = 6, y = 20;

void getMaxWindowSize(int &rows, int &cols) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        rows = w.ws_row;
        cols = w.ws_col;
    } else {
        rows = 24;
        cols = 80;
    }
}

char getKey()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}
bool kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}
void clearScreen() {
    system("clear"); 
}
void function(Direction &direction)
{
    static int x = 6;
    static int y = 20;
    static bool swUp = false, swDown = false, swRight = true, swLeft = false; 

    gotoxy(x, y);
    int maxX , maxY;
    getMaxWindowSize(maxX, maxY);
    if(x >= maxX || y>= maxY || x==0 || y==0)
    {
        maxX = (int) (maxX/4);
        maxY = (int) (maxY/2);
        gotoxy(maxX, maxY);
        std::cout << "The Game finished!" << std::endl;
        exit(0);
    }
    std::cout << "#";
    switch (direction)
    {
        case UP:
            if (!swDown) { 
                y--;
                swUp = true;
                swDown = swRight = swLeft = false;
            }
            else y++;
            break;
        case DOWN:
            if (!swUp) {
                swDown = true;
                swRight = swLeft = swUp = false;
                y++;
            }else y--;
            break;
        case RIGHT:
            if (!swLeft) {
                swRight = true;
                swLeft = swUp = swDown = false;
                x++;
            }else x--;
            break;
        case LEFT:
            if (!swRight) {
                swLeft = true;
                swRight = swUp = swDown = false;
                x--;
            }else x++;
            break;
    }
    gotoxy(x,y);
}