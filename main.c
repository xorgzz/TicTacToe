#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char board[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int xes[10] = {};
int oes[10] = {};
int turns = 0;

/*
1 ║2 ║3	
══╬══╬══
4 ║5 ║6	
══╬══╬══
7 ║8 ║9

\ /║/-\║\ /
 X ║| |║ X 
/ \║\_/║/ \
═══╬═══╬═══
4  ║5  ║6  
   ║   ║
   ║   ║
═══╬═══╬═══
7  ║8  ║9
   ║   ║
   ║   ║
*/



int not_taken(int chck){
	if(board[chck-1] != 'X' && board[chck-1] != 'O')
		return 1;

	return 0;
}

void prt(){
	for(int i = 1; i < 4; i++){
		for(int j = i*3-3; j < i*3; j++){
			printf("%c ", board[j]);
			if((j+1)%3 != 0)
				printf("|");
		}
		if(i != 3){
			printf("\n--+--+--");
		}
		printf("\n");
	}
}

void table_prt(){

	for(int i = 1; i < 4; i++){
		for(int j = i*3-3; j < i*3; j++){
			if(board[j] != 'X' && board[j] != 'O')
				printf("   ", board[j]);
			else if(board[j] == 'X')
				printf("\\ /");
			else if(board[j] == 'O')
				printf("/-\\");	
			if((j+1)%3 != 0)
				printf("|");
		}
		printf("\n");
		for(int j = i*3-3; j < i*3; j++){
			if(board[j] != 'X' && board[j] != 'O')
				printf(" %c ", board[j]);
			else if(board[j] == 'X')
				printf(" X ");
			else if(board[j] == 'O')
				printf("| |");	
			if((j+1)%3 != 0)
				printf("|");
		}
		printf("\n");
		for(int j = i*3-3; j < i*3; j++){
			if(board[j] != 'X' && board[j] != 'O')
				printf("   ", board[j]);
			else if(board[j] == 'X')
				printf("/ \\");
			else if(board[j] == 'O')
				printf("\\_/");	
			if((j+1)%3 != 0)
				printf("|");
		}
		printf("\n");
		if(i != 3)
			printf("---+---+---\n");
	}
}
	

int is_in(int searched, char player){
	if(player == 'X'){
		for(int i = 0; i < 10; i++){
			if(searched == xes[i]){
				return 1;
			}
		}
	}
	if(player == 'O'){
		for(int i = 0; i < 10; i++){
			if(searched == oes[i]){
				return 1;
			}
		}
	}
	return 0;
}


int los_num(){
	int los, counter = 0;
	char nums_left[10];
	srand(time(0));

	for(int i = 0; board[i] != '\0'; i++){
		if(board[i] != 'X' && board[i] != 'O'){
			nums_left[counter] = board[i];
			counter++;
		}
	}
	los = rand() % counter;
	los = nums_left[los] - '0';

	return los;
}

void usr_input(int xy, char player){
	if(board[xy-1] != 'X' && board[xy-1] != 'O'){
		board[xy-1] = player;
		if(player == 'X')
			xes[turns] = xy;
		else if(player == 'O')
			oes[turns] = xy;
		turns++;
	}
	else{
		printf("move not allowed\n\n");
	}
}

void bot_lvl_1(){
	int move = los_num();
	while(1){
		if(board[move - 1] != 'X' && board[move - 1] != 'O'){
			board[move - 1] = 'O';
			oes[turns] = move;
			turns++;
			break;
		}
		else{
			move = los_num();
		}
	}
}

void bot_lvl_2(int sub_lvl){
	int win[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
	int angles[4] = {1, 3, 7, 9};
	int los;
	if(sub_lvl == 1 && not_taken(5)){
		usr_input(5, 'O');
		return;
	}
	else if(sub_lvl == 1 && turns == 1){
		srand(time(0));
		los = rand()%4;
		usr_input(angles[los], 'O');
		return;
	}

	for(int i = 0; i < 8; i++){
		if(is_in(win[i][0], 'O') && is_in(win[i][1], 'O') && not_taken(win[i][2])){
			usr_input(win[i][2], 'O');
			return;
		}
		else if(is_in(win[i][0], 'O') && is_in(win[i][2], 'O') && not_taken(win[i][1])){
			usr_input(win[i][1], 'O');
			return;
		}
		else if(is_in(win[i][1], 'O') && is_in(win[i][2], 'O') && not_taken(win[i][0])){
			usr_input(win[i][0], 'O');
			return;
		}
	}
	if(sub_lvl == 1){
		for(int i = 0; i < 8; i++){
			if(is_in(win[i][0], 'X') && is_in(win[i][1], 'X') && not_taken(win[i][2])){
				usr_input(win[i][2], 'O');
				return;
			}
			else if(is_in(win[i][0], 'X') && is_in(win[i][2], 'X') && not_taken(win[i][1])){
				usr_input(win[i][1], 'O');
				return;
			}
			else if(is_in(win[i][1], 'X') && is_in(win[i][2], 'X') && not_taken(win[i][0])){
				usr_input(win[i][0], 'O');
				return;
			}
		}
	}

	bot_lvl_1();
	
}



int win_chck(char player){
	if(is_in(5, player)){
		if(is_in(1, player))
			if(is_in(9, player))
				return 1;

		if(is_in(3, player))
			if(is_in(7, player))
				return 1;

		if(is_in(2, player))
			if(is_in(8, player))
				return 1;

		if(is_in(4, player))
			if(is_in(6, player))
				return 1;
	}
	if(is_in(1, player)){
		if(is_in(2, player))
			if(is_in(3, player))
				return 1;

		if(is_in(4, player))
			if(is_in(7, player))
				return 1;
	}
	if(is_in(9, player)){
		if(is_in(6, player))
			if(is_in(3, player))
				return 1;

		if(is_in(8, player))
			if(is_in(7, player))
				return 1;
	}
	else{
		return 0;
	}
}

int end(){
	for(int i = 0; board[i] != '\0'; i++){
		if(board[i] != 'X' && board[i] != 'O')
			return 0;
	}
	return 1;
}


int main(int argc, char* argv[]){
	char comm, tmp[2];
	int xy, botORnot;
	char dut[5];
	if(argc < 2){
		botORnot = 1;
	}
	else{
		strcpy(dut, argv[1]);
		if(!strcmp(dut, "duo")){
			botORnot = 0;
		}
		else if(!strcmp(dut, "bot")){
			if(argc < 3){
				botORnot = 1;
			}
			else if(!strcmp(argv[2], "1")){
				botORnot = 1;
			}
			else if(!strcmp(argv[2], "2")){
				botORnot = 2;
			}
			else if(!strcmp(argv[2], "3")){
				botORnot = 3;
			}
			else{
				printf("\nno such level\n");
				return 0;
			}
		}
	}

	while(1){
		if(turns % 2 == 0){
			table_prt();
			printf("\nX~> ");
			comm = getchar();
			printf("\n");
			if(comm != 10)
				while(getchar() != 10);
		}
		else if(turns % 2 != 0 && botORnot == 0){
			table_prt();
			printf("\nO~> ");
			comm = getchar();
			printf("\n");
			if(comm != 10)
				while(getchar() != 10);
		}
		else if(botORnot == 1 && turns % 2 != 0){
			comm = '1';
		}
		int xy = comm - '0';

		if(comm != 10 && xy > 0 && xy < 10){
			if(turns % 2 == 0){
				usr_input(xy, 'X');

				if(win_chck('X')){
					table_prt();
					printf("\nX won\n");
					break;
				}
				if(end()){
					table_prt();
					printf("\nremis\n");
					break;
				}
			}
			else{
				if(botORnot == 0){
					usr_input(xy, 'O');
				}
				else if(botORnot == 1){
					bot_lvl_1();
				}
				else if(botORnot == 2){
					bot_lvl_2(0);
				}
				else if(botORnot == 3){
					bot_lvl_2(1);
				}
				if(win_chck('O')){
					table_prt();
					printf("\nO won\n");
					break;
				}
				if(end()){
					table_prt();
					printf("\ntie\n");
					break;
				}
			}
		}

	}
	return 0;
}
