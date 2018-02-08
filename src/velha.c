#include <stdio.h>
#include <stdlib.h>

#if defined(__MINGW32__) || defined(_MSC_VER)
	#define clear() system("cls")
#else
	#define clear() system("clear")
#endif

#define L 3
#define C 3

/*Prototypes, this will change with time*/
void showMenu();
void showName(int n);
void showBoard(int **board);
void showCredits();
int **createBoard();
int getCoord(int *x, int *y,int **board);
int validateCoord(int x, int y,int **board);
int getWinner(int **board);
void pvp();
void pvcpu();


/*Using main() for testing purposes*/
int main(){ 
	int menuOption = 1;

	
	/*
	while(menuOption){
		showMenu();
		scanf("%d", &menuOption);

		switch(menuOption){
			case 1:
				pvcpu();
			break;
			case 2:
				pvp();
			break;
			case 3:
				showCredits();
			break;
			case 0:
				return 0;
			break;
		}
	}
	*/
	pvp();

	return 0;
}
void showName(int n){
	if(n) printf("Player 1 turn:\n\n"); //n == True
	else printf("Player 2 turn:\n\n"); //n == False
}

void showBoard(int **board){
	unsigned int i, j;

	for(i = 0; i < L; i++){
		for(j = 0; j < C; j++){
			if(board[i][j] == 1) printf(" X | ");
			else if(board[i][j] == 2)	printf(" O |");
			else printf(" - |");
		}
		printf("\n------------\n");
	}
	puts("");
}

void showMenu(){
	clear();
	printf("TIC-TAC-TOE\n"
			"[1] - Player vs CPU\n"
			"[2] - Player vs Player\n"
			"[3] - Credits.\n"
			"> ");
}

int getCoord(int *x, int *y,int **board){
	int invalid = 1;

	while(invalid){
		fflush(stdin);
		printf("> ");
		scanf("%d %d", x, y);
		invalid = validateCoord(*x, *y, board);
		if(invalid) printf("Ivalid values.\n");
	}

	return 0;
}

int validateCoord(int x, int y,int **board){
	if((x >= 0 && x < 3) && (y >= 0 && y < 3) && board[x][y] == 0){
		return 0;
	}else return 1;
}

//This function is really messy right now, should improove into the future
int getWinner(int **board){
	int winner = 0;

	if((board[0][0] == board[1][1] && board[1][1] == board[2][2]) && board[0][0] > 0){  //cross 1
		if(board[0][0] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] > 0){//cross 2
		if(board [0][2] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] > 0){ //line 1
		if(board[0][0] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] > 0){ //line 2
		if(board [1][0] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] > 0){ //line 3
		if(board [2][0] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] > 0){ //pillar 1
		if(board[0][0] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] > 0){ //pillar 2
		if(board [0][1] == 1) winner = 1;
		else winner = 2;
	}
	else if(board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] > 0){ //pillar 3
		if(board [0][2] == 1) winner = 1;
		else winner = 2;
	}

	return winner;
}

int **createBoard(){
	int **board = NULL;
	unsigned int i, j;

	//Creates the board
	board = (int **) malloc(L*sizeof(int *));
	for(i = 0; i < C; ++i) board[i] = (int *) malloc(C*sizeof(int));
	for(i = 0; i < L; ++i){
		for(j = 0; j < C; ++j) board[i][j] = 0;
	}
	
	//Returns the address of the board in the heap
	return board;
}

void pvp(){
	int x = 0, y = 0, turns = 0, turn = 2, winner = 0, **board = NULL;

	board = createBoard();

	while(!winner){
		int invalid = 1;

		//Loop da tela
		while(invalid) {
			clear();
			showName(!(turn%2));
			showBoard(board);
			invalid = getCoord(&x, &y, board);
		}
	
		//Turn switch
		if(!(turn % 2)){
			board[x][y] = 1;
		}else{
			board[x][y] = 2;	
		} 

		winner = getWinner(board);
		turn++;
		turns++;
		if(turns == 9){
			winner = -1;
			break;
		}
	}

	//Final screen
	clear();
	showBoard(board);
	if(winner == 1)	printf("Player 1 Wins!!!\n");
	else if(winner == -1) printf("Velha, mizera!\n");
	else printf("Player 2 Wins!!!\n");


	free(board);
}

void pvcpu(){
	;
}

void showCredits(){
	;
}

