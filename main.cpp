#include "header.h"
#include <iostream>
#include <thread>
#include <chrono>

Direction direction = RIGHT;
bool swUp = false;
bool swDown = false;
bool swRight = true;
bool swLeft = false;

int main()
{
    while (true)
    {
        clearScreen();

        if (kbhit())
        {
            char c = getKey();
            if (c == '\033')
            {
                getchar();
                char arrow = getKey();
                
                if (arrow == 'A' && !swDown) direction = LEFT;
                else if (arrow == 'B' && !swUp) direction = RIGHT;
                else if (arrow == 'C' && !swLeft) direction = DOWN;
                else if (arrow == 'D') direction = UP;
            }

        }

        function(direction);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
    }
    return 0;
}

