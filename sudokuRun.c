#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int rows = 9;
int columns = 9;
bool getAllowedValues(int sudoku[9][9], int row, int col, int number);

void display(int sudoku[9][9]){
	for (int i = 0; i < rows; i++){
		if (i%3 == 0){
			printf("*============*===========*===========*\n");
		}
		for (int j = 0; j < columns; j++){
				printf(" |%2d", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("*============*===========*===========*\n");
}

void createEmptyBoard(int sudoku[9][9]){
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			sudoku[i][j] = 0;
		}
	}
}

int getValue(int sudoku[9][9], int r, int c){
	int value = sudoku[r][c];
	return value;
}

int addInitialValue(int sudoku[9][9], int r, int c, const int value){
	sudoku[r][c] = value;
	return true;
}

int fillinBoard(int sudoku[9][9], int row, int col){
	if(col>=9){
		col=0;
		++row;
	}
	if(row>=9){
		//display(sudoku);
		return true;
	}
	int randomN= (rand() % 9)+1;
	for(int i =0;i<9;i++){
		 randomN=randomN+1;
		if(randomN>9){
			randomN=1;
		}
		if(getAllowedValues(sudoku, row, col, randomN)&&addInitialValue(sudoku,row,col,randomN)&&fillinBoard(sudoku,row,col+1)){
			return true;
		}
		sudoku[row][col]=0;
	}
	return false;
}

int checkPuzzle(int sudoku[9][9], int r, int c, int guess){
	int valid = 0;
	if (sudoku[r][c] == guess){
		valid++;
		return valid;
	} else {
		printf("Incorrect value. Try again.\n");
	}
	return valid;
}

int isStillEmpty(int sudoku[9][9]){
	int empty = 0;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			if (sudoku[i][j] == 0){
				empty++;
				return empty;
			}
		}
	}
	return empty;
}

void addGuess(int start[9][9], int sudoku[9][9], int r, int c, int guess){
	if (sudoku[r][c] == 0){
		if(isStillEmpty(sudoku)){
			if(checkPuzzle(sudoku, r, c, guess)){
				sudoku[r][c] = guess;
			} 
		} else {
			printf("You win!\n");
		}
	}
}

bool getAllowedValues(int sudoku[9][9], int row, int col, int number){

	//checks row,
  	for(int i=0; i<9; i++){
    	if(sudoku[row][i]==number)
      		return false;
  	}
  
  	//checks column, 
  	for(int i=0; i<9; i++){
    	if (sudoku[i][col]==number)
      		return false;
  	}

  	//checks box
  	int startR = row -(row % 3);
  	int startC = col- (col % 3);
    	//actual logic for checking
  	for( int co= startC; co<startC+3; co++) {
    	for (int ro = startR; ro <startR + 3; ro++) {
      		if (sudoku[ro][co] == number) {
          		return false;
          		}		
      		}
    	}
  	return true;
}

 void reset(int start[9][9], int sudoku[9][9]){
 	//use pointers
 	int count=0;
	//createEmptyBoard(sudoku);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			count++;
			if (count%5!=0)
				sudoku[i][j]=0;
			if(sudoku[i][j] != 0)
				addInitialValue(start, i, j, 1);
		}
	}
	display(sudoku);
}

int main(){
	int keepPlaying=0;
	int choice;
	int userRow, userCol, userValue;
	int start[9][9];
	srand(time(0)); //seed for random generator
	int sudoku[9][9];

	createEmptyBoard(sudoku);
	fillinBoard(sudoku, 0, 0);

	/* creates boolean board */
	for(int i=0; i< rows; i++){
		for(int j=0; j< columns; j++){
			start[i][j]= 1;
		}
	}

	//prints initial board
	printf("Welcome to Sudoku!\nHere is your game: \n");
	//display(sudoku); tested if the validility of the sudoku
	reset(start, sudoku);

	while (keepPlaying == 0){
		printf("\nWhat would you like to do?\n(1) Add a guess\n"
			"(2) Display the current board\n(3) Reset "
			"the game\n(4) Start another game\n(5) Exit\n");
		scanf("%d", &choice);
		printf("choice is %d\n", choice);

		switch(choice){
			case 1:
				printf("\nEnter a row, column, and value:\n");
				scanf("%d %d %d", &userRow, &userCol, &userValue);
				addGuess(start, sudoku, userRow-1, userCol-1, userValue);
				display(sudoku);
				if (!isStillEmpty(sudoku)){
					keepPlaying++;
				}
				break;
			case 2:
				printf("\nHere is your current board:\n");
				display(sudoku);
				break;
			case 3:
				printf("\nResetting the game...\n");
				reset(start, sudoku);
				//returns same board
				break;
			case 4:
				createEmptyBoard(sudoku);
				fillinBoard(sudoku, 0, 0);
				for(int i=0; i< rows; i++){
					for(int j=0; j< columns; j++){
						start[i][j]= 1;
					}
				}
				reset(start, sudoku);
				break;
			case 5:
				keepPlaying++;
				break;

			default:
				printf("Invalid input.\n");
		}
	}
	printf("See ya!\n");
}