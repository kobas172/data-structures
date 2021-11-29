#include <iostream>
#include <string.h>
#include "list.h"
#define SIZE 20

int main() {

    List l1;
    char cmd[SIZE];
    int key;
    while (scanf("%s", &cmd) > 0)
    {
        if (strcmp(cmd, "ACTUAL") == 0)
            l1.printActual();
        else if (strcmp(cmd, "NEXT") == 0)
            l1.printNext();
        else if (strcmp(cmd, "PREV") == 0)
            l1.printPrevious();
        else if (strcmp(cmd, "ADD_BEG") == 0)
        {
            scanf("%d", &key);
            l1.addBeg(key);
        }
        else if (strcmp(cmd, "ADD_END") == 0)
        {
            scanf("%d", &key);
            l1.addEnd(key);
        }
        else if (strcmp(cmd, "ADD_ACT") == 0)
        {
            scanf("%d", &key);
            l1.addActual(key);
        }
        else if (strcmp(cmd, "DEL_BEG") == 0)
            l1.deleteBeg();
        else if (strcmp(cmd, "DEL_END") == 0)
            l1.deleteEnd();
        else if (strcmp(cmd, "DEL_ACT") == 0)
            l1.deleteActual();
        else if (strcmp(cmd, "DEL_VAL") == 0)
        {
            scanf("%d", &key);
            l1.deleteValue(key);
        }
        else if (strcmp(cmd, "PRINT_FORWARD") == 0)
            l1.printForward();
        else if (strcmp(cmd, "PRINT_BACKWARD") == 0)
            l1.printBackward();
    }
}
