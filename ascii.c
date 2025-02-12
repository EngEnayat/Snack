#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#define clear clearScreen()
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}

enum Direction {
    UP = 1,    // You can assign custom values, like 1 for UP
    DOWN = 2,  // 2 for DOWN
    LEFT = 3,  // 3 for LEFT
    RIGHT = 4  // 4 for RIGHT
};


char getKeyPress() {
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

struct Snack
{
    int body;
    struct Snack *next;
};

void clearScreen() {
    system("clear"); 
}
void PrintSnack(int*,int*, struct Snack *, enum Direction);
int main()
{
    enum Direction direction;
    struct Snack* snack = (struct Snack*)malloc(sizeof(struct Snack));
    if(snack == NULL)
    {
        printf("Failed Allocating Memory!");
        exit(0);
    }
    snack=NULL;

    printf("enter a key: ");
    getKeyPress();
    clear;
    // printf("%c", snack->body);
    int x=5, y=30;
    char stop = '1';
    
    for(int i=0; stop != '\n';i++)
    {
        struct Snack *n = (struct Snack*)malloc(sizeof(struct Snack));
        n->body = i;
        n->next = snack;
        snack = n;
        stop = getKeyPress();
        if(stop == '\033')
        {
            stop = getKeyPress();
            if(stop == '[')
            {
                stop = getKeyPress();
                if(stop == 'A') direction = UP;
                else if(stop == 'B') direction = DOWN;
                else if(stop == 'C') direction = RIGHT;
                else if(stop == 'D') direction = LEFT;
            }
        }

        // clear;
        PrintSnack(&x,&y,snack, direction);
    }
    PrintSnack(&x,&y,snack, direction);
    getchar();
    struct Snack* temp;
    while (snack != NULL) {
        temp = snack;
        snack = snack->next;
        free(temp);
    }
    return 0;
}

void PrintSnack(int* a,int* b, struct Snack *snack, enum Direction dir)
{
    // clear;
    int x =*a, y = *b;
    gotoxy(x,y);
    struct Snack *p = snack;
    if(dir == 1 || dir == 2 || dir == 3 || dir == 4)
    {
        if(dir == 1)
        {
            x--;
            y--;
        }
        else if(dir == 2)
        {
            x++;
            y--;
        }
    }
    y++;
    gotoxy(x,  y);
    printf("\xE2\x96\xA0\n");
    p = p->next;
    *a = x, *b = y;
} 