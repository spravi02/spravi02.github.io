#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    printf("Hello Saisita2");
    int sum = 0;
    int x= 9 , y = 8;
    sum = x + y;
    printf(" sum: %d ", sum);

    for ( x =9; x>= 0; x-- )
    {
        if ( x == 6)
         continue;
        printf ("x: %d & ", x);
        
    }
    return 0;
}