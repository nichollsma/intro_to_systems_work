#include <stdio.h>

void printRectangleWhile(int width, int height)
{
    int heightCount = 1;
    int colCount = 0;

    if (width < 1)
    {
        printf("");
    }
    else if (height < 1)
    {
        printf("");
    }
    else
    {
        while(heightCount <= height)
        {
            if((heightCount == 1) || (heightCount == height))
            {
                while(colCount < width)
                {
                    printf("+");
                    colCount++;
                }
                printf("\n");
                heightCount++;
                colCount = 0;
            }
                
            else if(heightCount < height)
            {
                printf("+");
                colCount++;
                while(colCount < width - 1)
                {
                    printf("-");
                    colCount ++;
                }
                printf("+\n");
                heightCount++;
                colCount = 0;
            }
        }
    }
}

void printTriangleFor(int height)
{
    int edgeSpaces;
    int colCount;

    if(height <= 0)
    {
        printf("");
    }
    else
    {
        for(int row = 1; row < height; row++)
        {
            edgeSpaces = (height - row) - 1;
            colCount = 0;
            for(int j = colCount; j <= edgeSpaces; j++)
            {
                printf(" ");
                colCount++;
            }
            printf("+");
            colCount++;

            for(int k = colCount; k < (height - 1); k++)
            {
                printf("-");
                colCount++;
            }
            
            if(colCount == (height - 1))
            {
                printf("+");
            }
            printf("\n");
        }
        for(int i = 0; i < height; i++)
        {
            printf("+");
        }
        printf("\n");
    }
}
