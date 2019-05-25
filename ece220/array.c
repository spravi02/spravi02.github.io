int main()
{
    int a[]= {6, 5, 6, 6, 7, 7, 4, 3};
    int a2[8], a3[8]; 
    int count =0, flag=0, val; 

    for(int i=0; i< 8; i++)
    {
        //copy into another array
        a2[i]= a[i];
    }

    for(int i=0; i< 8; i++)
    {
        //k= i+1; 
        //if (k > 7)
          //  k= 0;
        for(int j=0; j< 8; j++)
        {
            if (j == i)
            continue; 
            if(a[i] == a2[j])
            val = a[i]; 
            {
                for(int k=0; k< 8; k++)
                {
                    if(a3[k] == a[i]){
                         flag =1;
                    }
                    if(flag == 1)
                        break;
                    else 
                        a3[k] = val;
                        break; 
                }
                
                
            }
        }
    }
    return 0; 
}