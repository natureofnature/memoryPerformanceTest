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

/*
	initialisation
*/

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





/*
	memory copy	
*/




	gettimeofday(&start,NULL);
	memcpy(f_array_2,f_array,sizeof(float)*num_array);
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 2  is %ld\n",diff);
	std::cout<< "Copy speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;

/* 	memory read   */



	int r_position;
	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		r_position = position_array[i];
	}
	gettimeofday(&end,NULL);
        pos_diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;


/*	random memory write    */

	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i++){
		f_array [position_array[i]] = (float)i;
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 3  is %ld\n",diff);
        std::cout<< "Random Write speed is "<<(float) num_array*4/(1024*1024*(diff-pos_diff)/1000000)<<" MB/s"<<std::endl;



/*	sequential  memory write    */

	gettimeofday(&start,NULL);
	for(int i=0;i<num_array;i=i+1){
		f_array [i] = (float)i;
//		f_array [i+1] = (float)(i+1);
//		f_array [i+2] = (float)(i+2);
//		f_array [i+3] = (float)(i+3);
//		f_array [i+4] = (float)(i+4);
//		f_array [i+5] = (float)(i+5);
//		f_array [i+6] = (float)(i+6);
//		f_array [i+7] = (float)(i+7);
//		f_array [i+8] = (float)(i+8);
	//	f_array [i+9] = (float)(i+9);
	//	f_array [i+10] = (float)(i+10);
	//	f_array [i+11] = (float)(i+11);
		//f_array [i+12] = (float)(i+12);
		//f_array [i+13] = (float)(i+13);
		//f_array [i+14] = (float)(i+14);
		//f_array [i+15] = (float)(i+15);
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        //printf("block 3  is %ld\n",diff);
        std::cout<< "Write speed is "<<(float) num_array*4/(1024*1024*diff/1000000)<<" MB/s"<<std::endl;

/*	sequential  memory read    */

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
	std::cout<<index<<" --> "<<f_array[index]<<"vs "<<f_array_2[index]<<std::endl;
	std::cout<<tmp<<std::endl;

	free(f_array);
	free(f_array_2);
	free(position_array);
}
