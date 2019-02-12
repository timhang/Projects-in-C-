#include<iostream>
#include "qsort.h"
#include<stdexcept>
#include"LengthMismatch.h"


std::vector<std::pair<int, int> > assignPlates(std::vector<int> turkeys, 
                                              std::vector<int> potatoes)
{
     /* your code here */
   	std::vector<std::pair<int, int> > output;
   	std::less<int> comp;
   	if(turkeys.empty() || potatoes.empty()){
   		std::cout<<"empty input vectors";
   		return std::vector<std::pair<int,int> >();
   	}
   	if(turkeys.size()!=potatoes.size()) 
	{
		throw LengthMismatch(int(turkeys.size()),int(potatoes.size()));
	}
	
   	/*if(){
   		std::cout<<"sizes not equal";
   		return std::vector<std::pair<int,int> >();
   	}*/
   	QuickSort(turkeys, comp);
   	QuickSort(potatoes, comp);
   	/*for(size_t i = 0;i<turkeys.size();i++){
    	std::cout<<turkeys[i]<<'\n';
    }
    for(size_t i = 0;i<potatoes.size();i++){
    	std::cout<<potatoes[i]<<'\n';
    }*/
   	std::vector<int>::iterator itt = --turkeys.end();
   	std::vector<int>::iterator itp = potatoes.begin();
   	int sum = *itt + *itp;
   	for(itt = --turkeys.end();itt>=turkeys.begin();--itt){
		if(*itt + *itp != sum){
			std::cout<<"No possible way to plate with equal calories\n";
			return std::vector<std::pair<int,int> >();
		}
   		output.push_back(std::pair<int, int> (*itt,*itp));
   		++itp;
   	}
   	return output;
}

/*int main(){
	std::vector<int> turkeys;
    std::vector<int> potatoes;
    int t_ints[]={500,580,550,54,3};
    int p_ints[]={440,470,520,0,0};
    turkeys.assign(t_ints,t_ints+5);
    potatoes.assign(p_ints,p_ints+5);
    
    std::vector<std::pair<int, int> > output;
    output = assignPlates(turkeys, potatoes);
    std::vector<std::pair<int,int> >::iterator it;
    for(it = output.begin();it!=output.end();++it){
    	std::cout<<it->first<<" "<<it->second<<'\n';
    }
    return 0;
}*/