#include <stdio.h>
#include <stdlib.h>
#include <math.h>

	int cell_count = 1;
	int k;
	int board_size;
	int board_matrix[100][100];
void trivialCase (int,int);
//Function to implement Trivial case 
void trivialCase (int trominoX,int trominoY){
	for (int i = trominoX; i< trominoX +2; i++){
			for (int j = trominoY; j< trominoY +2; j++){
				if (board_matrix[i][j] == 0) board_matrix[i][j] = cell_count;
			}
		}
}

void printTromino();
void trominoTile(int,int,int,int,int,int);
//Recursive function to fill all quadrants of the Tromino Board
void trominoTile(int posX, int posY, int board_size, int quad_size,int trominoX,int trominoY){
	
	int constSize=board_size;
	if(quad_size == 2){
		trivialCase(trominoX,trominoY);
		cell_count++;
		return;
	}
	int quad_arr[8];
	int sizeX=trominoX+ quad_size/2;
	int sizeY=trominoY+ quad_size/2;
	//Checking if Hole is in the First quadrant
	if(posX < (trominoX + quad_size/2) && posY < (trominoY + quad_size/2) ){
		
		quad_arr[0]= posX; quad_arr[1]=posY ;
		quad_arr[2]=(trominoX + quad_size/2)-1; quad_arr[3]=(trominoY + quad_size/2);
		quad_arr[4]=(trominoX + quad_size/2); quad_arr[5]=(trominoY + quad_size/2)-1;
		quad_arr[6]=(trominoX + quad_size/2); quad_arr[7]=(trominoY + quad_size/2);
	
		board_matrix[quad_arr[2]][quad_arr[3]] = cell_count;
		board_matrix[quad_arr[4]][quad_arr[5]] = cell_count;
		board_matrix[quad_arr[6]][quad_arr[7]] = cell_count;
		cell_count++;
	}
		//Checking if Hole is in the Two quadrant
	else if(posX < (trominoX + quad_size/2) && posY >= (trominoY + quad_size/2) ){
		quad_arr[0] =(trominoX + quad_size/2)-1; 	quad_arr[1]=(trominoY + quad_size/2)-1;
	    quad_arr[2]=posX;	quad_arr[3]=posY;
		quad_arr[4]=(trominoX + quad_size/2);	quad_arr[5]=(trominoY + quad_size/2)-1; 
		quad_arr[6]=(trominoX + quad_size/2);	quad_arr[7]=(trominoY + quad_size/2);
		
		board_matrix[quad_arr[0]][quad_arr[1]] = cell_count;
		board_matrix[quad_arr[4]][quad_arr[5]] = cell_count;
		board_matrix[quad_arr[6]][quad_arr[7]] = cell_count;
		cell_count++;
	}
		//Checking if Hole is in the Third quadrant
	else if(posX >= (trominoX + quad_size/2) && posY < (trominoY + quad_size/2) ){
						
		quad_arr[0] =(trominoX + quad_size/2)-1; 	quad_arr[1]=(trominoY + quad_size/2)-1;
	    quad_arr[2]=(trominoX + quad_size/2)-1;	quad_arr[3]=(trominoY + quad_size/2);
		quad_arr[4]=posX;	quad_arr[5]=posY; 
		quad_arr[6]=(trominoX + quad_size/2);	quad_arr[7]=(trominoY + quad_size/2);
		
		board_matrix[quad_arr[0]][quad_arr[1]] = cell_count;
		board_matrix[quad_arr[2]][quad_arr[3]] = cell_count;
		board_matrix[quad_arr[6]][quad_arr[7]] = cell_count;
		cell_count++;
	}
		//Checking if Hole is in the Fourth quadrant
	else if(posX >= (trominoX + quad_size/2) && posY >= (trominoY + quad_size/2) ){

		quad_arr[0] =(trominoX + quad_size/2)-1; 	quad_arr[1]=(trominoY + quad_size/2)-1;
	    quad_arr[2]=(trominoX + quad_size/2)-1;	quad_arr[3]=(trominoY + quad_size/2);
		quad_arr[4]=(trominoX + quad_size/2);	quad_arr[5]=(trominoY + quad_size/2)-1; 
		quad_arr[6]=posX;	quad_arr[7]=posY;
		
		board_matrix[quad_arr[0]][quad_arr[1]] = cell_count;
		board_matrix[quad_arr[2]][quad_arr[3]] = cell_count;
		board_matrix[quad_arr[4]][quad_arr[5]] = cell_count;
		cell_count++;
	}
	//Fill Quadrant 1
	trominoTile(quad_arr[0], quad_arr[1], board_size, quad_size/2,trominoX,trominoY);
	//Fill Quadrant 2
	trominoTile(quad_arr[2], quad_arr[3], board_size, quad_size/2,trominoX,sizeY);
	//Fill Quadrant 3
	trominoTile(quad_arr[4], quad_arr[5], board_size, quad_size/2,sizeX,trominoY);
	//Fill Quadrant 4
	trominoTile(quad_arr[6], quad_arr[7], board_size, quad_size/2,sizeX,sizeY);
	
}
//Function to final print Tromino matrix
void printTromino(){
	
	for(int i=0;i<board_size;i++){
		for(int j=0;j<board_size;j++){
			if(board_matrix[i][j]==-1000){
			printf("Hole\t");
			}
			else
				printf("%d\t", board_matrix[i][j]);
		}
		printf("\n");
	}
}


int main (int argc, char* argv[]){
	k = atoi(argv[1]);//Get board Dimensions
	board_size = pow(2,k); 
	int posX = atoi(argv[2]); //Get Row number starting from 0
	int posY = atoi(argv[3]); //Get Column number starting from 0
	for (int i = 0; i<board_size; i++){
		for (int j = 0; j<board_size; j++){
			board_matrix[i][j] = 0;
		}
	}
	board_matrix[posX][posY] = -1000; //Make position of Hole distinct to print later
	trominoTile(posX,posY,board_size,board_size,0,0);
	printTromino(); 
	return 0;
}