#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<unistd.h>
#include <math.h>
#include <cstring>
#include <time.h>
using namespace std;
int main(){
	int num_array = 2*40960000;
	int* position_array = (int*)malloc(sizeof(int)*num_array);

	srand (time(NULL));
	
	struct  timeval start;
        struct  timeval end;
        unsigned  long diff;
        unsigned  long pos_diff; //reference for random write
        gettimeofday(&start,NULL);

	float* f_array = (float*)malloc(sizeof(float)*num_array);
	for(int i=0;i<num_array;i++){
		f_array[i] =(float)(rand()%100)/(1+rand()%1000);
		position_array[i] = rand()%num_array;
	}
	std::cout<<"Generate seed like:\n";
	for(int i=0;i<10;i++){
		std::cout<<position_array[i]<<" ";
	}
	std::cout<<std::endl;	
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
       // printf("block 1  is %ld\n",diff);
	//std::cout<< "Have created array with size :"<<num_array*4/1024/1024<<" MB"<<std::endl;	

	float* f_array_2 =  (float*)malloc(sizeof(float)*num_array);
	gettimeofday(&start,NULL);
	memcpy(f_array_2,f_array,sizeof(float)*num_array);
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 2  is %ld\n",diff);
	std::cout<< "Copy speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;


	int r_position;
	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		r_position = position_array[i];
	}
	gettimeofday(&end,NULL);
        pos_diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;




	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		f_array [position_array[i]] = i;
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 3  is %ld\n",diff);
        std::cout<< "Random Write speed is "<<(float) num_array*4/(1024*1024*(diff-pos_diff)/1000000)<<" MB/s"<<std::endl;

	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		f_array [i] = i;
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 3  is %ld\n",diff);
        std::cout<< "Write speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;

	float tmp;
	gettimeofday(&start,NULL);
        for(int i=0;i<num_array;i++){
                tmp = f_array [i];
        }
        gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 4  is %ld\n",diff);
        std::cout<< "Read speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;



	int index = rand()%num_array;
	std::cout<<f_array[index]<<" "<<f_array_2[index]<<std::endl;
	std::cout<<tmp<<std::endl;

	free(f_array);
	free(f_array_2);
	free(position_array);
}
