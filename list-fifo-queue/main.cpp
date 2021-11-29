#include <iostream>
#include <string.h>
#include "ListBasedFIFOQueue.h"
#define SIZE 20

int main()
{
    List l;
    char cmd[SIZE];
    int key;

    while (scanf("%s", &cmd) > 0)
    {
        if (strcmp(cmd, "ADD_BEG") == 0)
        {
            scanf("%d", &key);
            l.addBeg(key);
        }
        else if (strcmp(cmd, "ADD_END") == 0)
        {
            scanf("%d", &key);
            l.addEnd(key);
        }
        else if (strcmp(cmd, "DEL_BEG") == 0)
            l.delBeg();
        else if (strcmp(cmd, "DEL_END") == 0)
            l.delEnd();
        else if (strcmp(cmd, "PRINT_FORWARD") == 0)
            l.printForward();
        else if (strcmp(cmd, "PRINT_BACKWARD") == 0)
            l.printBackward();
        else if (strcmp(cmd, "PUSH") == 0)
        {
            scanf("%d", &key);
            l.push(key);
        }
        else if (strcmp(cmd, "POP") == 0)
            l.pop();
        else if (strcmp(cmd, "PRINT_QUEUE") == 0)
            l.printQueue();
        else if (strcmp(cmd, "COUNT") == 0)
            l.count();
        else if (strcmp(cmd, "SIZE") == 0)
            l.getSize();
        else if (strcmp(cmd, "GARBAGE_SOFT") == 0)
            l.garbageSoft();
        else if (strcmp(cmd, "GARBAGE_HARD") == 0)
            l.garbageHard();
    }
}
