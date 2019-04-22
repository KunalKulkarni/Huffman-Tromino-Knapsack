#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int size; int capacity;
int weight[10];
int profit[10];
int selectedItems[10];
void calcKnapsack();

int main(int argc,char ** argv){
	
	char buff[100];
	char buff1[100];
	char *token;
	FILE *fptr = fopen( argv[1], "r");
	if(fptr!=NULL){
	//Input from user taken into num of items(size),capacity, and profit, weight arrays are populated.
		fscanf(fptr,"%d\n",&size);
		fscanf(fptr,"%d\n",&capacity);
		fscanf(fptr,"%s\n",buff);
		profit[0]=atoi(strtok(buff,","));
		for(int i=1;i<size;i++){
			
			profit[i]=atoi(strtok(NULL,","));
		}
		fscanf(fptr,"%s\n",buff1);
		weight[0]=atoi(strtok(buff1,","));
		for(int i=1;i<size;i++){
			
			weight[i]=atoi(strtok(NULL,","));
		}
	}
	calcKnapsack();
}

void calcKnapsack(){
	int i, w;
	int CurrentWeight =0;
	int B[size+1][capacity+1];
	for(i = 0; i<= size; i++){
		for (w= 0; w<= capacity; w++){
			//Elements in column 0 and row 0 are made 0.
			if (i ==0 || w == 0){
				B[i][w] = 0;
			} else if (weight[i-1] <= w ){
				//Maximum out of B[i-1,w] and (B[i-1,w-wi]+bi) is taken
				if ((profit[i-1] + B[i-1][w-weight[i-1]]) > B[i-1][w])
					B[i][w] = profit[i-1] + B[i-1][w-weight[i-1]];
				else
					B[i][w] = B[i-1][w];
			} else {
				//if wi>w
				B[i][w] = B[i-1][w];
			}
		}
	}
	
	printf("Profit---%d\n",B[size][capacity]);
	int size1 = size ;
	int w1 = capacity;
	//In the table generated check until value of weight is different in the row
	//If the value is different add the item to the selected items list
	//Check for all entries of the last row of the table
	while (B[size1][w1] != 0){
		if (B[size1][w1] == B[size1-1][w1]) size1--;
		else {
			selectedItems[size1-1] = 1;
			w1 = w1 - weight[size1-1];
			size1--;
		}
	}
	//Calculate weight using the items taken into the selected items list.
	for(int i=0;i<size;i++){
		if(selectedItems[i]==1){
			CurrentWeight=CurrentWeight+weight[i];
		}
	}
	printf("Weight---%d\n",CurrentWeight);
	printf("Items Taken:\n");
	for(int i=1;i<=size;i++){
		if(selectedItems[i-1]==1){
			printf("Item %d\t",i);
		}
	} 
	printf("\n");
	
}

























