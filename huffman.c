#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char characters[20];
int frequency[20];
int size;
int huffCode[25];

typedef struct Node {			//minheapnode
	char label;		//data
	int freq;
	struct Node *left, *right;
} Node;

typedef struct Heap {		//minheap
	int length;		//size
	int maxLength;	//capacity
	struct Node **arr;
}Heap;

void heapify(Heap* heap, int pos) {
	int min = pos;
	int leftTree = 2*pos+1;
	int rightTree = leftTree+1;
	int len=heap->length;

	if (leftTree < len && heap->arr[leftTree]->freq 
		< heap->arr[min]->freq)	
			min = leftTree;
	if (rightTree < len && heap->arr[rightTree]->freq 
		< heap->arr[min]->freq)
			min = rightTree;

	if (min != pos) {
		Node* temp = heap->arr[min];
		heap->arr[min] = heap->arr[pos];
		heap->arr[pos] = temp;
		heapify(heap, min);
	}
}

Heap* builtHeap() {
	
	Heap* heap = (Heap*) malloc (sizeof(Heap));
	heap->length = 0;
	heap->maxLength = size;
	heap->arr = (Node**) malloc (heap->maxLength * sizeof(Node*));
	for (int i=0; i<size ; i++){
		Node* temp = (Node*) malloc (sizeof(Node*));
		temp->label = characters[i];
		temp->freq = frequency[i];
		temp->left = temp->right = NULL;
		heap->arr[i] = temp;

	}
	heap->length = size;
	int num = heap->length-1;
	for (int i=(num-1)/2; i>=0; i--){
		heapify(heap, i);
	}
	return heap;
}

Node* removeMin (Heap* heap){
	Node* temp = heap->arr[0];
	heap->arr[0] = heap->arr[heap->length-1];
	heap->length--;
	//printf ("in removeMin \n");
	heapify(heap, 0);
	return temp;
}

Node* builtTree() {	
				//builthuffmantree
	Node *left, *right;	//top
	Heap *heap = builtHeap();
	int flag;
	//printf ("in builtheap \n");
	//if (heap->length == 1) flag=1; 
	while (heap->length !=1){
		left = removeMin(heap);
		right = removeMin(heap);
		//printf ("in builtheap- while [%c] \n", right->label);
		Node* parent = (Node*) malloc(sizeof(Node));
		parent->label = 'X';
		parent->freq = (left->freq) + (right->freq);
		parent->left = left;
		parent->right = right;
	//printf ("in builtheap- while [%d] \n", parent->freq);
		heap->length++;
		int n = heap->length-1;
		while(n>0 && parent->freq < heap->arr[(n-1)/2]->freq ){
			heap->arr[n] = heap->arr[(n-1)/2];
			n = (n-1)/2;
		}
		heap->arr[n] = parent;
	}
	return removeMin(heap);
}

void displayHuffman (int index, Node* root) {

	char printArray[20];
	if (root->right) {
		huffCode[index] = 1;
		displayHuffman(index+1, root->right);
	}
	if (root->left) {
		huffCode[index] = 0;
		displayHuffman(index+1, root->left);
	}
	if (!(root->left && root->right)){

		printf("%c : ", root->label);
		
		for (int i=0; i<index; i++){
			printf("%d", huffCode[i]);
		}

		printf("\n");
	}
		
}

int main(int argc,char ** argv){
	char buff[100];
	char buff1[100];
	char *token;
	char c;
	
	FILE *fptr = fopen( "test.csv", "r");
	if(fptr!=NULL){
		fscanf(fptr,"%s\n",buff);
		int i=0, j=0;
		while (buff[i] != '\0') {
			c=buff[i];
			if (c == ',') ;
			else {
				characters[j] = c;
				j++;
			}
			i++;
		}
		size =j;
		i=0;
		fscanf(fptr,"%s\n",buff1);
		frequency[0]=atoi(strtok(buff1,","));
		for(int i=1;i<size;i++){
			
			frequency[i]=atoi(strtok(NULL,","));
		}
	}
	//printf ("in Main %d\n", size);
	Node* root = builtTree();
	int index =0;
	displayHuffman(index, root);
}