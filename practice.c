#include <stdio.h>
int RemoveDuplicates(int *arr, int n);
int main()
{
    int arr[] = {1,2,2,3,4,5,6,6,8,9};
    int n= sizeof(arr)/sizeof(arr[0]);

    int m= RemoveDuplicates(arr,n);
    printf("\nthe number of unique elements: %d ", m);
}

int RemoveDuplicates(int *arr, int n)
{
    int lastUnique = 0; 
    int i=0;
    for(i=0; i<n; i++)
    {
        if(arr[i] != arr[lastUnique])
        {
            arr[lastUnique+1]=arr[i];
            lastUnique++;
        }
       /* else
        {
            arr[lastUnique+1]=arr[i+1];
            lastUnique++;
        }*/
        
    }
    //printf("%10d",arr[i]);
    return lastUnique+1;
}