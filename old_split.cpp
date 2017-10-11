#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
int main(int arg, char**argv){
	printf("There are %d args\n",arg);
	if(arg<3){
		printf("You should define target file and target prefix name\n");
		exit(0);
	}
	for(int i=0;i<arg;i++){
		printf("[Arg%d]is[%s]\n",i,argv[i]);
	}
	char* targetfile = argv[1];
	printf("Target file is %s ",targetfile);
	char* prefix = argv[2];
	ifstream in;
	in.open(targetfile,ios::in);
	if(!in){
		printf(",but target file does not exist\n");
		exit(0);
	}
	printf("Target prefix is %s\n",argv[2]);
	int num_sm=20;
	ofstream* ous = new ofstream[20];
	int filenamelen = strlen(prefix);
	for(int i=0;i<20;i++){
		int low2 = i /10;
		int low1 = 0;
		int low = low2<1?1:2;
		if(low2>0) {
			low1=i%10;
		}else{
			low2 = i%10;
		}
		char* name = new char[low+1+filenamelen];
		memset(name,0,low+1+filenamelen);
		strcpy(name,prefix);
		name[filenamelen]=low2+'0';
		if(low>1)name[filenamelen+1]=low1+'0';
		printf("file %d is %s\n",i,name);
		ous[i].open(name,ios::out);
	}
	string content;
	while(1){
		in>>content;
		if(content==" ")break;
		printf("%s\n",content.c_str());
	}
	printf("Release resources\n");
	for(int i=0;i<num_sm;i++)
		ous[i].close();
	in.close();	
	return 0;
}
