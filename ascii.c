#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#define clear clearScreen()
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}
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
void PrintSnack(int,int, struct Snack *);
int main()
{
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
        clear;
        PrintSnack(x,y,snack);
    }
    PrintSnack(x,y,snack);
    getchar();
    struct Snack* temp;
    while (snack != NULL) {
        temp = snack;
        snack = snack->next;
        free(temp);
    }
    return 0;
}

void PrintSnack(int x,int y, struct Snack *snack)
{
    clear;
    gotoxy(x,y);
    struct Snack *p = snack;
    while(p !=NULL)
    {
        y++;
        gotoxy(x,  y);
        printf("\xE2\x96\xA0\n");
        p = p->next;
    }
} 