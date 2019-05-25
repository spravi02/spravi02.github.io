#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int func(int **ptr);

int main()
{
   int n[4] = {0,1,2,3};
   int arr[][3] = {7,8,2,5,3,6};
   int *ptr;
   ptr= &arr[0][0];

func(ptr);
}

int func(int **ptr2)
{
    /*for(int i=0; i<6; i++)
    {
        printf("")
    }*/
    //ptr=ptr+1; 
    printf(" %d ", ptr2[0][2]);

}
     