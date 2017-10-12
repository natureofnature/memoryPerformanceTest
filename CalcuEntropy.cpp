#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <math.h> 
#include<sys/time.h>
#include<unistd.h>
#include <sstream>
using namespace std;
int main(int arg, char** argv){
	if(arg<3){
		printf("You should specify the targetfiles\n");
		exit(0);
	}
	if(arg<4){
		cout<<"You should specify the output data file\n"<<endl;
		exit(0);
	}
	int warp1 = 1;
	int warp2 = 1;
	if(arg<6){
		cout<<"You should specify the number of warps each workgroup contains, now use default value (1,1)\n";
	}
	string target1 = argv[1];
	string target2 = argv[2];
	string output = argv[3];
	if(arg>=6){
		string w1 = argv[4];
		string w2 = argv[5];
		warp1 = stoi(w1);
		warp2 = stoi(w2);	
	}		
	ofstream ous;
	ous.open(output.c_str(),ios::out);
	ofstream ous_total_counter;
	ofstream ous_first_counter;
	ofstream ous_second_counter;
	if(arg==9){
		ous_total_counter.open(argv[6],ios::out);
		ous_first_counter.open(argv[7],ios::out);
		ous_second_counter.open(argv[8],ios::out);
	}
	ifstream ins1;
	ifstream ins2;
	ins1.open(target1.c_str(),ios::in);
	ins2.open(target2.c_str(),ios::in);
	ulong timer_start_E = 99999999999;
	ulong timer_end_L = 0;
	string content1;
	string content2;







	struct  timeval start;
        struct  timeval end;
        unsigned  long diff;



        gettimeofday(&start,NULL);






	while(getline(ins1,content1)){
//		cout<<content1<<endl;
		int pos = content1.find(" ");
		string s_sm_id = content1.substr(0,pos);
		string time = content1.substr(pos+1);
		pos = time.find(" ");
		string s_timer_start = time.substr(0,pos);
		string s_timer_end = time.substr(pos+1);
		uint sm_id = stoul(s_sm_id);
		ulong timer_start = stoull(s_timer_start);
		ulong timer_end = stoull(s_timer_end);
		timer_start_E = timer_start_E<timer_start?timer_start_E:timer_start;
		timer_end_L = timer_end_L>timer_end?timer_end_L:timer_end;
	}

	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 1  is %ld\n",diff);
        gettimeofday(&start,NULL);


	while(getline(ins2,content2)){
//		cout<<content2<<endl;
		int pos = content2.find(" ");
		string s_sm_id = content2.substr(0,pos);
                string time = content2.substr(pos+1);
                pos = time.find(" ");
                string s_timer_start = time.substr(0,pos);
                string s_timer_end = time.substr(pos+1);
                uint sm_id = stoul(s_sm_id);
                ulong timer_start = stoull(s_timer_start);
                ulong timer_end = stoull(s_timer_end);
                timer_start_E = timer_start_E<timer_start?timer_start_E:timer_start;
                timer_end_L = timer_end_L>timer_end?timer_end_L:timer_end;
	}	

	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 1  is %ld\n",diff);
        gettimeofday(&start,NULL);

	cout<<"starts at "<<timer_start_E<<" ,";
	cout<<"ends at "<<timer_end_L<<" ,";
	cout<<"GAP is "<<timer_end_L - timer_start_E<<endl;
	ulong gap = timer_end_L - timer_start_E;
	int* counter = new int[gap];
	int* portion1 = new int[gap];
	int* portion2 = new int[gap];
	float* entropy = new float[gap];
	for(int i=0;i<gap;i++){
		counter[i]=0;
		portion1[i]=0;
		portion2[i]=0;
		entropy[i]=0.0f;
	}
	ins1.clear();//must be called when meets eof
	ins1.seekg(0,ins1.beg);
	ins2.clear();
	ins2.seekg(0,ins2.beg);
	while(getline(ins1,content1)){
                int pos = content1.find(" ");
                string s_sm_id = content1.substr(0,pos);
                string time = content1.substr(pos+1);
                pos = time.find(" ");
                string s_timer_start = time.substr(0,pos);
                string s_timer_end = time.substr(pos+1);
                uint sm_id = stoul(s_sm_id);
                ulong timer_start = stoull(s_timer_start);
                ulong timer_end = stoull(s_timer_end);
		timer_start -= timer_start_E;
		timer_end -= timer_start_E;
		for(int i=timer_start;i<timer_end;i++){
			counter[i]+=warp1;
			portion1[i]+=warp1;
		}
        }

	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 1  is %ld\n",diff);
        gettimeofday(&start,NULL);

	while(getline(ins2,content2)){
  //              cout<<content2<<endl;
                int pos = content2.find(" ");
                string s_sm_id = content2.substr(0,pos);
                string time = content2.substr(pos+1);
                pos = time.find(" ");
                string s_timer_start = time.substr(0,pos);
                string s_timer_end = time.substr(pos+1);
                uint sm_id = stoul(s_sm_id);
                ulong timer_start = stoull(s_timer_start);
                ulong timer_end = stoull(s_timer_end);
       		timer_start -= timer_start_E;
                timer_end -= timer_start_E;
                for(int i=timer_start;i<timer_end;i++){
                        counter[i]+=warp2;
			portion2[i]+=warp2;
                } 
	}

	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 1  is %ld\n",diff);
        gettimeofday(&start,NULL);
	
	std::stringstream ss1,ss2,ss3,ss0;

	for(int i=0;i<gap;i++){

		if(ous_total_counter.is_open()){
			//ous_total_counter<<counter[i]<<endl;
			ss1 << counter[i]<<endl;
	//	counter[i] = counter[i]%3+ portion1[i]/3;
		}
	}
	for(int i=0;i<gap;i++){
		if(ous_first_counter.is_open()){
		//	ous_first_counter<<portion1[i]<<endl;
			ss2 << portion1[i]<<endl;
			//portion1[i] = log2(portion1[i]);
		}
	}
	for(int i=0;i<gap;i++){
		if(ous_second_counter.is_open()){
		//	ous_second_counter<<portion2[i]<<endl;
			ss3 << portion2[i]<<endl;
			//portion2[i] = counter[i] / portion1[i];
		}

		float p1 = (float)portion1[i]/(portion1[i]+portion2[i]);
		float p2 = 1.0f -p1;
		float r =0;
		if((p1!=0)&&(p2!=0)){
			r= -p1*log2(p1)-p2*log2(p2);
		}
		//ous<<counter[i]<<endl;
		//ous<<r<<endl;
		ss0 << r<<endl;
		
	}
	gettimeofday(&end,NULL);
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("block 1  is %ld\n",diff);

	ous_total_counter<<ss1.rdbuf();
	ous_first_counter<<ss2.rdbuf();
	ous_second_counter<<ss3.rdbuf();
	ous<<ss0.rdbuf();
	
	

	delete[] counter;
	delete[] portion1;
	delete[] portion2;
	delete[]  entropy;
	ins1.close();
	ins2.close();
	ous_total_counter.close();
	ous_first_counter.close();
	ous_second_counter.close();
	ous.close();
	return 0;


}


