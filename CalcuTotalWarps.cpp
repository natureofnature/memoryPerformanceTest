#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
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
	if(arg==6){
		string w1 = argv[4];
		string w2 = argv[5];
		warp1 = stoi(w1);
		warp2 = stoi(w2);	
	}		
	ofstream ous;
	ous.open(output.c_str(),ios::out);
	ifstream ins1;
	ifstream ins2;
	ins1.open(target1.c_str(),ios::in);
	ins2.open(target2.c_str(),ios::in);
	ulong timer_start_E = 99999999999;
	ulong timer_end_L = 0;
	string content1;
	string content2;
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
	cout<<"starts at "<<timer_start_E<<" ,";
	cout<<"ends at "<<timer_end_L<<" ,";
	cout<<"GAP is "<<timer_end_L - timer_start_E<<endl;
	ulong gap = timer_end_L - timer_start_E;
	int* counter = new int[gap];
	for(int i=0;i<gap;i++){
		counter[i]=0;
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
		}
        }
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
                } 
	}
	for(int i=0;i<gap;i++){
		ous<<counter[i]<<endl;
	}
	delete counter;
	ins1.close();
	ins2.close();
	ous.close();
	return 0;


}


