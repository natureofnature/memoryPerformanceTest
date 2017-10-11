#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
using namespace std;
#define NUMSM 20
//argv[1] file to be splited according to sm_id 
//argv[2] prefix of the files
int main(int arg,char** argv){
	if(arg<3){
		printf("You should specify the source file and target prefix!\n");
		exit(0);
	}
	string sourcefile(argv[1]);
	ifstream ins;
	ins.open(sourcefile.c_str(),ios::in);
	if(!ins){
		cout<<"Source file does not exist!\n";
		exit(0);
	};
	string prefix(argv[2]);
	cout<<"Soruce file is "<<sourcefile<<", prefix  is "<<prefix<<endl;
	int num_sm = NUMSM;
	ofstream* ous = new ofstream[num_sm];
	for(int i=0;i<num_sm;i++){
		string name=prefix;
		string suffix = to_string(i);
		name.append(suffix);
	//	cout<<"Going to write to "<<name<<endl;
		ous[i].open(name.c_str(),ios::out);
	}
	string content;
	while(getline(ins,content)){
	//	cout<<content<<endl;
		size_t pos = content.find(" ");
		string smid = content.substr(0,pos);
		string time = content.substr(pos);
		int sm_id = stoi(smid);
		ous[sm_id]<<content<<endl;
	}

	for(int i=0;i<num_sm;i++){
		ous[i].close();
	}
	ins.close();
}
