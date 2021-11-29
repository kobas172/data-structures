#include <stdio.h>
#include <stdlib.h>

struct File {
    int ID;
    int fileSize;
};

int partition(struct File array[], int firstIndex, int length, const int toSort)
{
    struct File temporary;
    int pivot = firstIndex;
    int index = firstIndex - 1;
    if (toSort == 0)
    {
        pivot = array[length].fileSize;
    }
    else if (toSort == 1)
    {
        pivot = array[length].ID;
    }
    for (int i = firstIndex; i < length; i++)
    {
        if (toSort == 0)
        {
            if(array[i].fileSize <= pivot)
            {
                index++;
                temporary = array[index];
                array[index] = array[i];
                array[i] = temporary;
            }
        }
        else if (toSort == 1)
        {
            if(array[i].ID <= pivot)
            {
                index++;
                temporary = array[index];
                array[index] = array[i];
                array[i] = temporary;
            }
        }
    }
    temporary = array[index+1];
    array[index+1] = array[length];
    array[length] = temporary;

    return index+1;
}

void quickSort(struct File array[], int firstIndex, int length, const int toSort)
{
    if (firstIndex < length)
    {
        int pivot = partition(array, firstIndex, length, toSort);
        quickSort(array, firstIndex, pivot-1, toSort);
        quickSort(array, pivot+1, length, toSort);
    }
}

void printResult(struct File first[], struct File second[], int operations, int firstCounter, int secondCounter)
{
    printf("%d\n", operations);
    printf("1: ");
    for (int i = firstCounter-1; i >= 0; i--)
    {
        printf("%d ", first[i].ID);
    }
    printf("\n2: ");
    for (int i = secondCounter-1; i >= 0; i--)
    {
        printf("%d ", second[i].ID);
    }
}

void filesOnPendrives(struct File files[], int quantity, int capacity)
{
    int sum = 0, operations = 0, index = 0;
    struct File* firstPendrive = (struct File*)malloc(sizeof(struct File)*quantity);
    struct File* secondPendrive = (struct File*)malloc(sizeof(struct File)*quantity);
    int firstIndex = 0; int secondIndex = 0;
    int firstCounter = 0, secondCounter = 0;

    for(int i = 0; i < quantity; i++)
    {
        firstPendrive[i].ID = 0;
        secondPendrive[i].ID = 0;
    }

    for (int i = 0; i < quantity; i++)
    {
        sum += files[i].fileSize;
        if (sum <= capacity && index == 0)
        {
            operations++;
            firstPendrive[firstIndex].ID = files[i].ID;
            firstIndex++;
            firstCounter++;
        }
        else if (sum > capacity && index == 0)
        {
            index++;
            if (files[i].fileSize <= capacity)
            sum = 0;
            {
                sum += files[i].fileSize;
                if (sum <= capacity && index == 1)
                {
                    operations++;
                    secondPendrive[secondIndex].ID = files[i].ID;
                    secondIndex++;
                    secondCounter++;
                }
            }
        }
        else if (sum <= capacity && index == 1)
        {
            operations++;
            secondPendrive[secondIndex].ID = files[i].ID;
            secondIndex++;
            secondCounter++;
        }
        else if(sum > capacity && index == 1)
            index++;
    }
    quickSort(firstPendrive, 0, firstCounter - 1, 1);
    quickSort(secondPendrive, 0, secondCounter - 1, 1);
    printResult(firstPendrive, secondPendrive, operations, firstCounter, secondCounter);
    free(firstPendrive);
    free(secondPendrive);
}

int main()
{
    int quantity = 0, capacity = 0;
    scanf("%d %d", &quantity, &capacity);
    struct File* files = (struct File*)malloc(sizeof(struct File)*quantity);
    for (int i = 0; i < quantity; i++)
    {
        scanf("%d %d", &files[i].ID, &files[i].fileSize);
    }
    quickSort(files, 0, quantity - 1, 0);
    filesOnPendrives(files, quantity, capacity);
    free(files);
}
