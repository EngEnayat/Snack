#include "header.h"
#include <iostream>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

#include <ctime> // for random numbers
#include <random>
#include <sys/ioctl.h>
#include <unistd.h>
int point =0;
int x = 6, y = 20;
int xWindow, yWindow;
int xRandom, yRandom;

void random_number()
{
    getMaxWindowSize(xWindow, yWindow);
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int> (time(nullptr)));
        seeded = true;
    }
    
    do {
        xRandom = 1 + (rand() % (xWindow - 2)); 
        yRandom = 1 + (rand() % (yWindow - 2));
    } while (xRandom == 0 || yRandom == 0); //
}


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

    if (x == xRandom && y == yRandom)
    {
        printf("\a");
        point++;
        int oldX = xRandom, oldY = yRandom;
        while (xRandom == oldX && yRandom == oldY) {
            random_number();
        }
    }

    if (xRandom > 0 && yRandom > 0) {
        gotoxy(xRandom, yRandom);
        std::cout << "@";
    }
    
    static bool swUp = false, swDown = false, swRight = true, swLeft = false; 
    gotoxy(x, y);
    int maxX , maxY;
    getMaxWindowSize(maxX, maxY);
    if(x >= maxX || y>= maxY || x==0 || y==0)
    {
        clearScreen();
        maxX = (int) (maxX/4);
        maxY = (int) (maxY/2);
        gotoxy(maxX, maxY);
        std::cout << "The Game finished!" << std::endl;
        gotoxy(++maxX, maxY);
        std::cout<< "your points: " << point << "\n\n\n"<<std::endl;
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
    gotoxy(0,0);
    std::cout << "Your Points: " << point;
    gotoxy(x,y);
}