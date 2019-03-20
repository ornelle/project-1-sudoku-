#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int rows = 9;
int columns = 9;

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

bool fillinBoard(int row, int col){
	/* if attempting the extra credit this creates a randomize sudoku puzzle using recursion */ 
        //^^above will pass in 0,0 to START
	
        //BASE CASE: controls recursions
        if(row>8)
            return true;
        //generates new int
        int randomNum = rand()% 10; // returns a random int between 0-9

        //go to next row if your column is full
        if(col>8)
            return fillinBoard(row+1, 0);
        //9 possible attempts
        for(int i=0; i<9; i++) {
            if (canDo(row, col, randomNum)) {
                //if board is empty it'll insert it in if no
                board[row][col] = randomNum;
                if (fillinBoard(row, col + 1))
                    //if returned true it goes back to base case!!!!
                    return true;
            }
            randomNum++;
            //checks other possible ints at that point on board
            if(randomNum>9)
                randomNum=1;
            /* ^goes back to next for loop and trys all the numbers that came prior to randomNum */

        }
        //BACK TRACKS: if all attempts at that point has not worked
        //what false are we returning didnt work at all?
        board[row][col]=0;
        return false;

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
	if (start[r][c] == 0){
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


bool getAllowedValues(int sudoku[9][9], int r, int c, int number){

	//returns numbers that are allowed in the chosen square
	bool fal= false;
  	bool x= true;
	//returns numbers that are allowed in the chosen square? 

	//checks row,
  	for(int i=0; i<9; i++){
    		if(sudoku[row][i]==number)
      	return fal;
  	}
  
  	//checks column, 
  	for(int i=0; i<9; i++){
    		if (sudoku[i][col]==number)
      		return fal;
  	}

  	//checks box
  	int startR = row -(row % 3);
  	int startC = col- (col % 3);
    	//actual logic for checking
  	for( int co= startC; co<startC+3; co++) {
    		for (int ro = startR; ro <startR + 3; ro++) {
      			if (sudoku[ro][co] == number) {
          			return fal;
          			}		
      			}
    	}
  	return x;
}

 void reset(int start[9][9], int sudoku[9][9]){

	createEmptyBoard(start);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			if(sudoku[i][j] != 0)
				addInitialValue(start, i, j, 1);
		}
	}
	display(sudoku);
}

int main(){
	int empty, choice;
	int userRow, userCol, userValue;
	
	srand(time(0)); //seed for random generator
	int start[9][9];
	int sudoku[9][9] = {{0, 7, 3,   0, 0, 0,   8, 0, 0},
						{0, 0, 4,   1, 3, 0,   0, 5, 0},
						{0, 8, 5,   0, 0, 6,   3, 1, 0},
						{5, 0, 0,   0, 9, 0,   0, 3, 0},
						{0, 0, 8,   0, 1, 0,   5, 0, 0},
						{0, 1, 0,   0, 6, 0,   0, 0, 7},
						{0, 5, 1,   6, 0, 0,   2, 8, 0},
						{0, 4, 0,   0, 5, 2,   9, 0, 0},
						{0, 0, 2,   0, 0, 0,   6, 4, 0}};

	printf("Welcome to Sudoku!\nHere is your game: \n");
	createEmptyBoard(start);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			if(sudoku[i][j] != 0)
				addInitialValue(start, i, j, 1);
		}
	}
	display(sudoku);


	while (empty == 0){
		printf("\nWhat would you like to do?\n(1) Add a guess\n"
			"(2) Get a hint\n(3) Display the current board\n(4) Reset "
			"the game\n(5) Exit\n");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				printf("\nEnter a row, column, and value:\n");
				scanf("%d %d %d", &userRow, &userCol, &userValue);
				addGuess(start, sudoku, userRow-1, userCol-1, userValue);
				display(sudoku);
				if (!isStillEmpty(sudoku)){
					empty++;
				}
				break;
			case 2:
				printf("\nEnter a row and column:\n");
				scanf("%d %d", &userRow, &userCol);
				printf("\nThese are your options: \n");
				getAllowedValues(sudoku, userRow, userCol);
				break;
			case 3:
				printf("\nHere is your current board:\n");
				display(sudoku);
				break;
			case 4:
				printf("\nResetting the game...\n");
				createEmptyBoard(start);
					for (int i = 0; i < rows; i++){
						for (int j = 0; j < columns; j++){
							if(sudoku[i][j] != 0)
								addInitialValue(start, i, j, 1);
						}
					}
				display(sudoku);
				//returns same board
				break;
			case 5:
				empty++;
				break;
			default:
				printf("Invalid input.\n");
		}
	}
	printf("See ya!\n");
}
