#include <stdio.h>

#define N 9
#define UNASSIGNED 0

int usedInRow(int sudoku[N][N],int row, int num){
    for (int i=0;i<N;i++){
        if(sudoku[row][i]==num)
            return 1;
    }
            return 0;
}

int usedInCol(int sudoku[N][N], int col, int num){
    for(int i=0;i<N;i++){
        if(sudoku[i][col]==num)
            return 1;
    }
            return 0;
}

int usedInBox(int sudoku[N][N], int boxStartRow, int boxStartCol, int num){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(sudoku[i+boxStartRow][j+boxStartCol]==num)
                return 1;
        }
    }
                return 0;
}

int isSafe(int sudoku[N][N], int row, int col, int num){
    return !usedInRow(sudoku, row, num)
    && !usedInCol(sudoku, col, num)
    && !usedInBox(sudoku, row - (row%3), col-(col%3), num);
}

int solveSudoku(int sudoku[N][N]){
    int row, col;
    for(row=0;row<N;row++){
        for(col=0;col<N;col++){
            if(sudoku[row][col]==UNASSIGNED){
                for(int num=1;num<=9;num++){
                    if(isSafe(sudoku, row, col, num)){
                        sudoku[row][col]=num;

                            if (solveSudoku(sudoku))
                            return 1;

                            else
                            sudoku[row][col]=UNASSIGNED;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

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
void main(){
	int sudoku[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&sudoku[i][j]);
        }
    }
    if(solveSudoku(sudoku))
    printSudoku(sudoku);
}