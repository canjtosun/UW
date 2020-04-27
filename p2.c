#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define num_threads 27


typedef struct
{
    int row;
    int column;
    int (*board)[9];
	
} parameters;

int threadArray[num_threads] = {0};
int sudokuChecker[10] = {0};

void *checkCol(void *arg)
{
	//mem. alloc for arg and assign column
	parameters* data = (parameters*) arg;
	int col =  data->column;
	
	//10 element false/0 assign to an array
	int validarray[10] = {0};
	
	//go thru columns 0 to 8
	for(int i=0; i<9; ++i)
	{
		//assign the value at specific col and row
		int val = data->board[i][col];
		
		//if the value is 1, it is repeating. so invalid.
		if(validarray[val] != 0)
			pthread_exit(NULL);
		else
			validarray[val]= 1;	
	}
	
	//assign 18 thru 26 in threadArray
	threadArray[18+col] = 1;
	pthread_exit(NULL);
}

void *checkRow(void *arg)
{
	//mem. alloc for arg and assign row
	parameters* data = (parameters*) arg;
	int row =  data->row;
	
	//10 element false/0 assign to an array
	int validarray[10] = {0};
	
	//go thru rows 0 to 8
	for(int i=0; i<9; ++i)
	{
		//assign the value at specific col and row
		int val = data->board[row][i];
		
		//if the value is 1, it is repeating. so invalid.
		if(validarray[val] != 0)
			pthread_exit(NULL);
		else
			validarray[val]= 1;	
	}
	
	//assign 9 thru 17 in thread Array
	threadArray[9+row] =1;
	pthread_exit(NULL);
}

void *checkGrid(void *arg)
{
	//mem. alloc for arg and assign row and col 2D
	parameters* data = (parameters*) arg;
	int row = data->row;
	int col = data->column;
	
	//10 element false/0 assign to an array
	int validarray[10] = {0};
	
	//go thru 2d array 3x3 grids	
	for(int i=row; i<row+3; i++)
	{
		for(int j=col; j<col+3; j++)
		{
			//assign the value at specific col and row
			int val = data->board[i][j];
			
			//if the value is 1, it is repeating. so invalid.
			if(validarray[val] != 0)
				pthread_exit(NULL);
			else
				validarray[val]= 1;	
		}	
	}
	
	//assign 0 thru 8 in thread Array
	threadArray[row + col/3] = 1;
	pthread_exit(NULL);	
}


int main(void)
{
    //====== The Sudoku puzzle to be validated =======
    int sudoku[9][9] =
    {
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
     };
	 	 
	 //27 thread total
	 pthread_t threads[num_threads];
	 int index = 0;
	 	 
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			//grid thread create
			//memory allocation, assign row column  and sudoku board
			//create the thread
			if(i%3 == 0 && j%3 == 0)
			{				
				parameters *gridData = (parameters *) malloc(sizeof(parameters));
                gridData->row = i;
                gridData->column = j;
                gridData->board = sudoku;
                pthread_create(&threads[index++], NULL, checkGrid, gridData);
			}
			 
			// column thread create
			//memory allocation, assign row column  and sudoku board
			//create the thread
			if(i == 0)
			{
				parameters *columnData = (parameters *) malloc(sizeof(parameters));
                columnData->row = i;
                columnData->column = j;
                columnData->board = sudoku;
                pthread_create(&threads[index++], NULL, checkCol, columnData);	
			}
			 
			// row thread create
			//memory allocation, assign row column  and sudoku board
			//create the thread
			if(j == 0)
			{
				parameters *rowData = (parameters *) malloc(sizeof(parameters));
                rowData->row = i;
                rowData->column = j;
                rowData->board = sudoku;
                pthread_create(&threads[index++], NULL, checkRow, rowData);		
			}		 
		}	 
	}
	 
	//after created all threads, make them join at the same time
	for(int i=0; i<num_threads; i++)
	{
		pthread_join(threads[i],NULL);
	}
	/*
	sudoku check output
	check each grid, row, and column
	grids	->	0|1|2
				-----
				3|4|5
				-----
				6|7|8
							
	rows and column starts from 0
	*/

	for(int i=0; i<num_threads; i++)
	{
		//grid threads
		while(i<num_threads/3) // 0 thru 8(first 9 threads)
		{
			if(threadArray[i] == 0)
				printf("Checking %d. grid thread. Sudoku invalid\n",i);
			else
				printf("Checking %d. grid thread. Sudoku valid\n",i);
			i++;
		}
		//row threads 
		while(i<num_threads-9)// 9 thru 17(middle 9 threads)
		{
			if(threadArray[i] == 0) 
				printf("Checking %d. row thread. Sudoku invalid\n",i-9);
			else
				printf("Checking %d. row thread. Sudoku valid\n",i-9);
			i++;
		}
		// column threads 
		while(i<num_threads) // 18 thru 26(last 9 threads)
		{
			if(threadArray[i] == 0)
				printf("Checking %d. col thread. Sudoku invalid\n",i%18);
			else
				printf("Checking %d. col thread. Sudoku valid\n",i%18);
			i++;
		}
	}
	
	return 0;	 
}
