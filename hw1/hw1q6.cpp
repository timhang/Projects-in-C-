#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

string yodaspeak(stringstream & ss,int min,int max){
	if(min>=max) {string s;
		ss>>s; 
		//cout<<s<<" ";
		return s;
	}
	string s;
	ss>>s;
	//s = s+;
	
	//string s;
	cout<<yodaspeak(ss,++min,max)<<" ";
	return s;
}

int main(int argc, char* argv[]){
	if(argc<2){cout<<"Please provide a file."<<endl;
		return 1;}
	ifstream myfile;
	myfile.open(argv[1]);
	if(!myfile){cout<<"unable to open file"<<endl;
		return 1;}
	int n;
	myfile>>n;
	//cout<<n<<endl;
	string line;
	stringstream ss;
	getline(myfile,line);
	while(myfile.good()){
		getline(myfile,line);
		ss<<line;
		ss<<" ";
	}
	/*for(int i=0;i<n;i++){
		ss>>s[i];
		//cout<<s[i]<<endl;
	}*/


	
	//for(int i=0;i<n;i++)
		//cout<<ss.str()<<" ";
	cout<<yodaspeak(ss,0,n-1)<<endl;
	//cout<<s[0]<<" "<<s[1]<<endl;
	//cout<<ss.str()<<endl;
	myfile.close();

	return 0;
}