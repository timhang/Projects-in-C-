#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "lliststr.h"
using namespace std;


int main(int argc, char* argv[]){
    if (argc < 2) {
       cerr << "Please provide an input file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    
    string line;
    string first;
    int pos;
    string name;
    LListStr players;
    while(input.good()){
        stringstream ss;
        getline(input,line);
        //cout<<line<<endl;
        ss<<line;
        ss>>first;
        //cout<<first<<endl;
        if(first == "ADD"){
            ss>>pos;
            ss>>name;
            //cout<<pos<<" "<<name<<endl;
            players.insert(pos,name);
        }
        else if(first == "REPLACE"){
            ss>>pos;
            ss>>name;
            players.set(pos,name);
        }
        else if(first == "ACT"){
            ss>>pos;
            ss>>name;
            if(players.size()>1 && pos<players.size()){
                if(pos == players.size()-1){
                    cout<<"Assasinated: "<<players.get(0)<<endl;
                    players.remove(0);
                }
                else{
                    cout<<"Assasinated: "<<players.get(pos+1)<<endl;
                    players.remove(pos+1);
                }
            }
        }
    }

    if(players.size()==1)
        cout<<"Winner: "<<players.get(0)<<endl;
    
    else if(players.size()>1){
        cout<<"Remaining Players: "<<players.size()<<endl;
        for(int i=0;i<players.size();i++)
            cout<<players.get(i)<<endl;
        
    }
    input.close();
    return 0;
}