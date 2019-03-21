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

void addInitialValue(int sudoku[9][9], int r, int c, const int value){
	sudoku[r][c] = value;
}

void fillinBoard(int sudoku[9][9], int row, int col){
	/* if attempting the extra credit this creates a randomize sudoku puzzle using recursion */ 
        //^^above will pass in 0,0 to START
	int randomN;
	for(int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			randomN= (rand() % 9)+1;
			// srand(time(0));
			if(getAllowedValues(sudoku, r, c, randomN)){
				if (randomN!=0)
					sudoku[r][c]=randomN;
			}
			//makeshift while loop: if position is not good go back to it & try again
			else{
				randomN=9;
				//printf("%d\n", randomN );
				while(!getAllowedValues(sudoku, r, c, randomN)){
					printf("%d\n valuee\n", randomN);
					--randomN;
				}
				if (randomN>0)
					sudoku[r][c]=randomN;
				if (sudoku[r][c]==0){
					for(int i=0; i<9; i++){
						if(getAllowedValues(sudoku, r, c, i))
							sudoku[r][c]=i;
						display(sudoku);
					}
				}		

			}
		}

    }

}
int checkPuzzle(int r, int c, int guess){
	int valid = 0;
	int solved[9][9] = {{1, 7, 3,   5, 2, 9,   8, 6, 4},
						{6, 9, 4,   1, 3, 8,   7, 5, 2},
						{2, 8, 5,   4, 7, 6,   3, 1, 9},

						{5, 6, 7,   2, 9, 4,   1, 3, 8},
						{4, 2, 8,   7, 1, 3,   5, 9, 6},
						{3, 1, 9,   8, 6, 5,   4, 2, 7},

						{9, 5, 1,   6, 4, 7,   2, 8, 3},
						{8, 4, 6,   3, 5, 2,   9, 7, 1},
						{7, 3, 2,   9, 8, 1,   6, 4, 5}};


	if (solved[r][c] == guess){
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
			if(checkPuzzle(r, c, guess)){
				sudoku[r][c] = guess;
			} else {
				printf("Invalid input: you cannot change this initial value.\n");
			}
		} else {
			printf("Game over - you win!\n");
		}
	}
}


bool getAllowedValues(int sudoku[9][9], int row, int col, int number){

	//returns numbers that are allowed in the chosen square
	//bool fal= false;
  	//bool x= true;

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
	printf("does it work\n");

	/* creates boolean board */
	for(int i=0; i< rows; i++){
		for(int j=0; j< columns; j++){
			start[i][j]= 1;
		}
	}

	//prints initial board
	printf("Welcome to Sudoku!\nHere is your game: \n");
	display(sudoku);
	reset(start, sudoku);

	// for (int i = 0; i < rows; i++){
	// 	for (int j = 0; j < columns; j++){
	// 		if(sudoku[i][j] != 0)
	// 			addInitialValue(sudoku, i, j, 1);
	// 	}
	// }


	while (keepPlaying == 0){
		printf("\nWhat would you like to do?\n(1) Add a guess\n"
			"(2) Get a hint\n(3) Display the current board\n(4) Reset "
			"the game\n(5) Exit\n");
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
				printf("\nEnter a row and column:\n");
				scanf("%d %d", &userRow, &userCol);
				printf("\nThese are your options: \n");
				int numb=0; //fix this
				getAllowedValues(sudoku, userRow, userCol, numb);
				break;
			case 3:
				printf("\nHere is your current board:\n");
				display(sudoku);
				break;
			case 4:
				printf("\nResetting the game...\n");
				createEmptyBoard(sudoku);
					for (int i = 0; i < rows; i++){
						for (int j = 0; j < columns; j++){
							if(sudoku[i][j] != 0)
								addInitialValue(sudoku, i, j, 1);
						}
					}
				display(sudoku);
				//returns same board
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
