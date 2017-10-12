#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<unistd.h>
using namespace std;
int main(){
	int num_array = 2*40960000;
	
	struct  timeval start;
        struct  timeval end;
        unsigned  long diff;
        gettimeofday(&start,NULL);

	float* f_array = (float*)malloc(sizeof(float)*num_array);
	for(int i=0;i<num_array;i++){
		f_array[i] =(float)(rand()%100)/(1+rand()%1000);
	}
	
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 1  is %ld\n",diff);
	std::cout<< "Have created array with size :"<<num_array*4/1024/1024<<" MB"<<std::endl;	

	float* f_array_2 =  (float*)malloc(sizeof(float)*num_array);
	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		f_array_2[i] = f_array[i];
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 2  is %ld\n",diff);
	std::cout<< "Copy speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;



	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		f_array [i] = i;
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 3  is %ld\n",diff);
        std::cout<< "Write speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;


	free(f_array);
	free(f_array_2);

}
