#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using std::cout;
using std::cin;


int** createMatrix(int height, int width){
	srand (time(NULL));
	int** array = (int**)malloc(sizeof(int*)*height);
	for(int i=0;i<height;i++){
		array[i] = (int*)malloc(sizeof(int)*width);
		for(int j = 0;j<width;j++){
			array[i][j] =rand()%10;
		}
	}

	return array;
}


int main(int nArg, char** args){
	if(nArg!=4){
		std::cout<<"specify L,M,N\n";
	}

	int L = atoi(args[1]);
	int M = atoi(args[2]);
	int N = atoi(args[3]);
	std::cout<<"L = "<<L<<" M = "<<M<<" N= "<<N<<std::endl;
	int** A = createMatrix(L,M);
	int** B = createMatrix(M,N);
	int** C = createMatrix(L,N);	

	for(int i = 0;i<L;i++){
		for(int j=0;j<N;j++){
				C[i][j] = 0;
			for(int k=0;k<M;k++){
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
	return 0;	
}
