#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


sp_tuples * load_tuples(char* input_file)
{
    //open + read the file and save in the struct
    int rowNum, colNum; 
    //char trash; 
    FILE *fp = fopen(input_file, "r");      //opens the file named "input file": use r+ to read and write
    sp_tuples* tPtr= malloc(sizeof(sp_tuples));   //dynamically allocate memory for the matrix
    int suc1= fscanf(fp, "%d %d %c", &rowNum, &colNum);   //put the # of rows and cols in the right places
    tPtr->m= rowNum;
    tPtr->n= colNum; 

    //dynamically allocate memory for the first node:
    sp_tuples_node *tCP = malloc(sizeof(sp_tuples_node));         //allocate for the 1st node  
    sp_tuples_node *tNext;                                       //points to the next node
    int r1,r2, c2, c1, suc2,suc3;
    sp_tuples_node *temp;  
    double v;
    int nV=0; 
    tPtr->tuples_head = tCP;                        //initialize the struct pointers

    while(suc2==3)                                 //if suc != 3, then the file will be done reading the values
    {
        suc2= fscanf(fp, "%d %d %f", &r1, &c1, &v);  //place the other values into rightful locations
        if(suc2 !=3)
        {
            tCP->next= NULL;                       //once all of the values have been read, next point
            break;                                 //to null and break out of the loop(done)
        }
        tCP -> row = r1;                       //set each of the values into corresponding spot
        tCP -> col = c1;
        tCP -> value = v;
        nV++; 
        if(v==0)
            set_tuples(tPtr, r1, c1, v);
        tNext= malloc(sizeof(sp_tuples_node));     // now allocate memory for the next node to be read in
        tCP->next = tNext;
        suc3= fscanf(fp, "%d %d %f", &r2, &c2, &v);                         //update next pointer
        tNext->row = r2;                                                                                
        tNext-> col= c2;                            //probably do not need because I'm settign the values ^
        tNext->value= v; 
        nV++; 
        if(v==0)
            set_tuples(tPtr, r2, c2, v);
        if(r1> r2 || c1 > c2)
        {
            temp = tCP;
            tCP = tNext;                            //if rows and cols not ordered, swap pointers to put in right order
            tNext= temp; 
        }
        tCP= tNext;                                //update the current pointer to point to the next pointer
        tNext= malloc(sizeof(sp_tuples_node));     // now allocate memory for the next node to be read in
        tCP->next = tNext;                          // do again                               
                                                   //done reading for this line         
    }
    //if(tPtr->tuples_head-> value == 0)
    tPtr->nz= nV;                                  //set the total # of values from input file
    fclose(fp);
    return tPtr;
}


double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  //assume the value is 0 and change that only if the entry is found in the linked list
  double value =0;
  
  sp_tuples_node * tCP = mat_t->tuples_head;
  while(tCP !=NULL)
    {
      //if the given cell is found update value
      if(row == tCP->row && col== tCP->col)
	{
	  value = tCP->value;
	  return value;
	}
      tCP = tCP ->next;
    }
  
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    sp_tuples *matC= malloc(sizeof(sp_tuples));
    matC->m= matA->m;
    matC->n= matA->n;
    matC->nz= 0;
    sp_tuples_node *matC_node=malloc(sizeof(sp_tuples_node));
    sp_tuples_node *nextCNode;
    sp_tuples_node *a_nextNode= matA->tuples_head->next; 
    sp_tuples_node *a_currNode= matA->tuples_head;
    sp_tuples_node *b_nextNode= matB->tuples_head->next; 
    sp_tuples_node *b_currNode= matB->tuples_head;    
    int cRow= matC_node->row;
    int cCol= matC_node->col;
    double cCurrVal= matC_node->value=0;

    int aRow= matA-> tuples_head->row; 
    int aCol= matA->tuples_head->col;
    double aCurrVal = matA->tuples_head->value;  

    int bRow= matB-> tuples_head->row; 
    int bCol= matB->tuples_head->col;
    double bCurrVal = matB->tuples_head->value;  

    while(  a_nextNode != NULL)
    {
        cRow= aRow;
        cCol= aCol; 
        cCurrVal= aCurrVal;
        nextCNode= malloc(sizeof(sp_tuples_node));
        matC_node->next= nextCNode; 
        matC_node= nextCNode;
        a_currNode= a_nextNode; 
        a_nextNode=  matA->tuples_head->next; 
    }

    while(  nextCNode != NULL)
    {
        cRow= cRow;
        cCol= cCol; 
        cCurrVal= cCurrVal + bCurrVal;
        //sp_tuples_node *nextCNode= malloc(sizeof(sp_tuples_node));
        matC_node->next= nextCNode; 
        matC_node= nextCNode;
        b_nextNode=  matB->tuples_head->next; 
        b_currNode= b_nextNode; 
    }

	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    sp_tuples_node *tCP= mat_t-> tuples_head;
    sp_tuples_node *tNext= mat_t-> tuples_head->next;
    free(tNext);
    free(tCP);
    free(mat_t);
    return;
}  





