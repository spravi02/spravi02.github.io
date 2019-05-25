#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame -> rows= rows;
    mygame -> cols= cols;
    mygame -> score= 0;
    
    for (int i=0; i < rows; i++)
    {
        for (int j=0; j < cols; j++)
        {
            int *ptr= get_cell(mygame, i, j);
            *ptr = -1; 
        }
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
// update the game struct wth new_rows (the value (rows) = new_rows)
    (*_cur_game_ptr) -> rows= new_rows;
    (*_cur_game_ptr) -> cols= new_cols;
    (*_cur_game_ptr) -> score= 0;
//fill the cells with -1
    for (int i=0; i< new_rows; i++)
    {
        for (int j=0; j< new_cols; j++)
        {
        int *new_ptr = get_cell(*_cur_game_ptr, i, j);
        *new_ptr= -1;
        }
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    int * ptr=0;
    int nROW= (*cur_game).rows;   //total number of rows in the cur_game game 
    int nCOL= (*cur_game).cols;   //total number of cols in the cur_game game 

    if (row+1 < 1 || row +1 > nROW)   //row + 1 because in matrix, row starts at 0
    return NULL;
    if (col+1 < 1 || col +1 > nCOL)   //col + 1 because in matrix, col starts at 0
    return NULL; 
//if row and col sent in are valid then find the ptr of the array from the current cell 
    else 
    ptr = (*cur_game).cells + (row * nCOL)+ col;    // multiply the row # by total # of cols and + the col #
    return ptr; 
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
int nROWS= ((*cur_game).rows) ;
int nCOLS= ((*cur_game).cols) ;
int *rPtr, *rTarget, *next; 
int count, flag = 0;
// if can't slide up return 0

//slide up (no merge)
// for each col chec row one by one:
for(int c=0; c< nCOLS; c++)
{
    for(int r=nROWS; r>= 0; r--)  //because we will check row above current, current starts at bottom 
    {
        rPtr = get_cell(cur_game, r, c);
        rTarget = rPtr; 
        if(*rPtr != -1)
        {
            while(*next == -1)
            {
                rTarget--;
                rPtr--;
                count++;
            }
            rPtr= rPtr + count;    
            while(rTarget< rPtr)
            {
                *rTarget = *rPtr;
                *rPtr = -1; 
                flag=1;
            }
        }
    }
}
// merge if the tiles have the same number
for(int c=0; c< nCOLS; c++)
{
    for(int r=nROWS; r >= 0; r--)    //because we are doing rPtr-1 we have to start from the bottom most row
    {
        rPtr= get_cell(cur_game, r,c);
        if (*next = *rPtr)     //if the row above it is equal to the current row  
        {
            *next= *next+ *rPtr;    //add the values together
            *rPtr = -1;                     //set the value in the current r pointer to empty
            rPtr= next;                   // the r pointer will shift up 1 (basically did another move)
            flag=1;    
        }
    }
}
//slide up again after merge (we need this incase there are gaps after merge):
for(int c=0; c< nCOLS; c++)
{
    for(int r=nROWS; r>= 0; r--)  //because we will check row above current, current starts at bottom 
    {
        rPtr = get_cell(cur_game, r, c);
        next = get_cell(cur_game,r-1, c);
        rTarget = rPtr; 
        if(*rPtr != -1)
        {
            while(*next == -1)
            {
                rTarget--;
                rPtr--;
                count++;
            }
            rPtr= rPtr + count;    
            while(rTarget< rPtr)
            {
                *rTarget = *rPtr;
                *rPtr = -1;
                flag=1; 
            }
        }
    }
}
    return flag;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
int nROWS= ((*cur_game).rows);
int nCOLS= ((*cur_game).cols);
int *rPtr, *rTarget, *next; 
int count = 0, flag = 0;
// if can't slide down return 0

//slide down (no merge)
// for each col chec row one by one:
for(int c=0; c< nCOLS; c++)
{
    for(int r=0; r<= nROWS; r++)  //because we will check row below current, current starts at top 
    {
        rPtr = get_cell(cur_game, r, c);
        next = get_cell(cur_game, r+1, c);
        rTarget = rPtr; 
        if(*rPtr != -1)
        {
            while(*next == -1)
            {
                rTarget++;
                rPtr++;
                count++;
            }
            rPtr= rPtr - count;    
            while(rTarget> rPtr)
            {
                *rTarget = *rPtr;
                *rPtr = -1; 
                flag=1;
            }
        }
    }
}
// merge if the tiles have the same number
for(int c=0; c< nCOLS; c++)
{
    for(int r=0; r <nROWS; r++)    //because we are doing rPtr+1 we have to start from the top most row
    {
        rPtr= get_cell(cur_game, r,c);
        if (*next = *rPtr)     //if the row below it is equal to the current row  
        {
            *next= *next+ *rPtr;    //add the values together
            *rPtr = -1;                     //set the value in the current r pointer to empty
            rPtr= next;                   // the r pointer will shift down 1 (basically did another slide down)
            flag=1;    
        }
    }
}
//slide down again after merge (we need this incase there are gaps after merge):
for(int c=0; c< nCOLS; c++)
{
    for(int r=0; r<nROWS; r++)  //because we will check row below current, current starts at top 
    {
        rPtr = get_cell(cur_game, r, c);
        next = get_cell(cur_game, r+1, c);
        rTarget = rPtr; 
        if(*rPtr != -1)
        {
            while(*next == -1)
            {
                rTarget++;
                rPtr++;
                count++;
            }
            rPtr= rPtr - count;    
            while(rTarget> rPtr)
            {
                *rTarget = *rPtr;
                *rPtr = -1;
                flag=1; 
            }
        }
    }
}
    return flag;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

/*copy and paste the slide up function except, we need to change: 
 * 1. the for loops so that the row comes first and col comes 2nd
 * 2. change rPtr to cPtr
 * 3. in col for loop: start c @ nCOLS (>=0 and c--)
 * 4. anything in the body with r (rTarget or rPtr) to cPtr. Stays: cPtr-1 not cPtr+1
*/
    return 1;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

/*copy and paste the slide down function except, we need to change: 
 * 1. the for loops so that the row comes first and col comes 2nd
 * 2. change rPtr to cPtr
 * 3. in col for loop: start c @ 0 (<nCOLS and c++)
 * 4. anything in the body with r (rTarget or rPtr) to cPtr. Stays: cPtr+1 not cPtr-1  (*next)
*/
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int nROWS= (*cur_game).rows;
    int nCOLS= (*cur_game).cols;
    int *current, *next;
    int flag =0; 
//check the entire board to see if there's any cell thats empty and that should be able to slide 
    for(int r=0; r <nROWS; r++)
    {
        for (int c=0; c <nCOLS; c++)
        {
            current = get_cell(cur_game, r, c);
            if (*current == -1)
                flag = 1; 
        }
    }

//check if any cells match in any of the columns so that we can slide either up or down
    for(int r=0; r <nROWS; r++)
    {
        for(int c=0; c <nCOLS; c++)
        {
            current = get_cell(cur_game, r, c);
            next = get_cell(cur_game, r, c+1);     //add +1 to c so that the next tile is the one below it
            if (*current == *next)
            flag =1; 
        }
    }

//check if any cells match in any of the rows so that we can slide either right or left
 for(int r=0; r <nROWS; r++)
    {
        for(int c=0; c <nCOLS; c++)
        {
            current = get_cell(cur_game, r, c);
            next = get_cell(cur_game, r+1, c);     //add +1 to r so that the next tile is the one to the right of it
            if (*current == *next)
            flag =1; 
        }
    }
    return flag;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}