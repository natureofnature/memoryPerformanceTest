#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using std::cout;
using std::cin;


float** createMatrix(int height, int width){
	srand (time(NULL));
	float** array = (float**)malloc(sizeof(float*)*height);
	for(int i=0;i<height;i++){
		array[i] = (float*)malloc(sizeof(float)*width);
		for(int j = 0;j<width;j++){
			array[i][j] =(float)(rand()%100)/(rand()%1000+1)+rand()%10;
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
	float** A = createMatrix(L,M);
	float** B = createMatrix(M,N);
	float** C = createMatrix(L,N);	

	for(int i = 0;i<L;i++){
		for(int j=0;j<N;j++){
			float sum = 0;
			for(int k=0;k<M;k++){
				sum += A[i][k]*B[k][j];
				sum = sum>1000?sum-1000:sum;
			}
			C[i][j]=sum;
		}
	}
	return 0;	
}
