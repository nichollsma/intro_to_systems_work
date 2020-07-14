#include <stdio.h>
int getMask(int, int, int);
int getSubInt(int, int, int);
void printDashHex(int);

int getMask(int start, int end, int bit)
{
    if ((start > end) || (start < 0) || (start > 31) || (end < 0) || (end > 31))
    {
        return 0;
    }
    else if ((bit != 0) && (bit != 1))
    {
        return 0;
    }
    int x = 0; 
    int n = start;
    for(int i = 0; i <= (end - start); i++) 
    {
        x = (x << 1) | 1;
    }
    x = x << n;
    if (bit == 0)
    {
        x = ~x;
    }
    return x;
}

int getSubInt(int start, int end, int read)
{
   if ((start > end) || (start < 0) || (start > 31) || (end < 0) || (end > 31))
   {
       return 0;
   }
   int x = read;
   x = x >> start;
   int mask = getMask(0, end - start, 1);
   x = x & mask;
   return x;
}

void printDashHex(int hexVal)
{
    int n;
    int x;
    for(int i = 0; i < 8; i++)
    {
        x = hexVal;
        n = 28 - (i * 4);
        x = (x >> n) & 0x0000000F;
        if(i == 7)
        {
            printf("%X\n",x);
        }
        else
        {
            printf("%X%c",x, '-');
        }
    }
}
