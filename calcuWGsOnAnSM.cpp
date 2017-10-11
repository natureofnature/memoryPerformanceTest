#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
int main(int arg, char** argv){
	if(arg<2){
		printf("You should specify the targetfile\n");
		exit(0);
	}
	string target = argv[1];
	ifstream ins;
	ins.open(target.c_str(),ios::in);
	ulong timer_start_E = 99999999999;
	ulong timer_end_L = 0;
	string content;
	while(getline(ins,content)){
		cout<<content<<endl;
		int pos = content.find(" ");
		string s_sm_id = content.substr(0,pos);
		string time = content.substr(pos+1);
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
	ins.clear();//must be called when meets eof
	ins.seekg(0,ins.beg);
	while(getline(ins,content)){
                int pos = content.find(" ");
                string s_sm_id = content.substr(0,pos);
                string time = content.substr(pos+1);
                pos = time.find(" ");
                string s_timer_start = time.substr(0,pos);
                string s_timer_end = time.substr(pos+1);
                uint sm_id = stoul(s_sm_id);
                ulong timer_start = stoull(s_timer_start);
                ulong timer_end = stoull(s_timer_end);
		timer_start -= timer_start_E;
		timer_end -= timer_start_E;
		for(int i=timer_start;i<timer_end;i++){
			counter[i]++;
		}
        }
	for(int i=0;i<gap;i++){
		cout<<counter[i]<<endl;
	}
	delete counter;
	ins.close();
	return 0;


}


