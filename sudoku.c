#include <stdio.h>

/*N is used for the size of the Sudoku grid, which would be N*N, UNASSIGNED represents empty numbers 
that we are trying to solve for.*/
#define N 9
#define UNASSIGNED 0

/*Returns a value, 1 or 0, which indicates whether
or not the assigned num has already appeared within the specified row.*/
int usedInRow(int sudoku[N][N],int row, int num){
    for (int i=0;i<N;i++){
        if(sudoku[row][i]==num)
            return 1;
    }
            return 0;
}

/*Returns a value, 1 or 0, which indicates whether
or not the assigned num has already appeared within the specified column.*/
int usedInCol(int sudoku[N][N], int col, int num){
    for(int i=0;i<N;i++){
        if(sudoku[i][col]==num)
            return 1;
    }
            return 0;
}

/*Returns a value, 1 or 0, which indicates whether
or not the assigned 'num' has already appeared within the specified 3*3 box.*/
int usedInBox(int sudoku[N][N], int boxStartRow, int boxStartCol, int num){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(sudoku[i+boxStartRow][j+boxStartCol]==num)
                return 1;
        }
    }
                return 0;
}

/*Checks if all conditions for a valid 'num' to be assigned are met.*/
int isSafe(int sudoku[N][N], int row, int col, int num){
    /*All 3 functions should return 0, indicating that the 'num' has not appeared already in the row, column and 3*3 box.*/
    return !usedInRow(sudoku, row, num)
    && !usedInCol(sudoku, col, num)
    && !usedInBox(sudoku, row-(row%3), col-(col%3), num);
}

/*We take the unsolved sudoku grid and assign values to all empty cells indicated by UNASSIGNED, we also need to find the 
location of the empty cells, and then evaluate the validity of the assigned number. 
If the assigned number is not valid, return 0 and try again, thus triggering backtracking.*/
int solveSudoku(int sudoku[N][N]){
    int row, col;
    /*Find the location of empty cells.*/
    for(row=0;row<N;row++){
        for(col=0;col<N;col++){
            if(sudoku[row][col]==UNASSIGNED){
                /*Assign values to empty cells, from 1-9.*/
                for(int num=1;num<=9;num++){
                    /*Check if the number is legal to be assigned.*/
                    if(isSafe(sudoku, row, col, num)){
                        /*Assign values to empty cells.*/
                        sudoku[row][col]=num;
                            /*Return 1, if we have successfully solved for 'num'.*/
                            if (solveSudoku(sudoku))
                            return 1;

                            /*If failure, reset the value of 'num' back to UNASSIGNED to try again.*/
                            else
                            sudoku[row][col]=UNASSIGNED;
                    }
                }
                /*Backtrack.*/
                return 0;
            }
        }
    }
    return 1;
}

/*Function to print the Sudoku board.*/
void printSudoku(int sudoku[N][N]){
    printf("\t-------------------------\n");
    for (int i=0;i<N;i++){
        printf("\t");
        for(int j=0;j<N;j++){
            if(j==0)
            printf("| ");
            printf("%d ", sudoku[i][j]);
            
            if((j+1)%3==0 )
            printf("| ");
        }
    	if((i+1)%3==0 )
        printf("\n\t-------------------------");    
    	printf("\n");
    }
}

/*Driver code to input Sudoku values, as well as print out the solved Sudoku board.*/
void main(){
	int sudoku[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&sudoku[i][j]);
        }
    }
    if(solveSudoku(sudoku))
    printSudoku(sudoku);
    else
    printf("No solution");
}
