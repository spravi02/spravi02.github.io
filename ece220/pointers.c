#include <stdio.h>

int main()
{
    int m =300;
    float x = 300.89;
    char let= 's';
    //declare pointers for each variable:
    int *mPtr= &m; 
    float *xPtr = &x;
    char *letPtr = &let;

    printf(" value of each variable (regular): \n ");
    printf(" m: %d, x: %f, let: %c \n", m, x, let);
    printf("\n");
    
    printf(" the address of each variable (regular)\n");
    printf(" m: %p, x: %p, let: %p, \n ", mPtr, xPtr, letPtr);
    printf("\n");
    
    printf(" the values of each var using the *' operators: \n");
    printf(" m: %d, x: %f, let: %c, \n", *mPtr, *xPtr, *letPtr);
    printf("\n");
    
    printf(" the addresses of each value using the '&' and '*' operators:\n");
    printf(" m: %p, x: %p, let: %p,\n", &(*mPtr), &(*xPtr), &(*letPtr));
    printf("\n");
    
    printf(" the values of each var using the '&' and '*' operators:\n");
    printf(" m: %d, x: %f, let: %c,\n", *(&m), *(&x), *(&let));


}