#include "stackstr.h"
#include "lliststr.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

//void operator_+{}
std::string minus_(std::string top, std::string last){
	size_t index;	
						
	std::string reverse1="";
	std::string reverse2="";
	unsigned int strlen1 = 
	(unsigned int)top.length();

	unsigned int strlen2 = 
		(unsigned int)last.length();
	for(int k=strlen1-1;k>=0;k--){
		reverse1=reverse1+top[k];
	}
	for(int k=strlen2-1;k>=0;k--){
		reverse2=reverse2+last[k];
	}
	index = reverse2.find(reverse1);
	//std::cout<<reverse1<<" " <<reverse2 <<std::endl;
	if (index != std::string::npos && 
		((index)<=strlen2)){
		// If found then erase it from string
		reverse2.erase(index, strlen1);
	}
	std::string reverse3="";
	strlen2 = (unsigned int)reverse2.length();
	for(int k=strlen2-1;k>=0;k--){
		reverse3=reverse3+reverse2[k];
	}
	return reverse3;
}


int main(int argc, char * argv[]){
	if(argc<3){
		std::cout<<"Please provide an input and a output file."<<std::endl;
		return 1;
	}
	//StackStr stack_;
	std::ifstream myfile(argv[1]);
	std::ofstream output(argv[2]);
	if(!myfile){std::cout<<"unable to open file"<<std::endl;
		return 1;}

	
	char temp;
	
	while(myfile.good()){
		//int parenth_count=0;
		
		std::string line;
		while(getline(myfile,line)){//each line in file
			StackStr stack_;
			std::stringstream ss;
			ss<<line;
			bool malforme=false;
			bool been = false;
			while(ss>>temp){//each character in line
				
				
				if(temp!=')'){//if not the closing parenthesis
					stack_.push(std::string(1,temp));
				}
				else{//if reach end of parenthesis
					been = true;
					std::string inside="";
					while(stack_.top()!="("){
						
						if(stack_.size()<1){//malforme when no matching left
								//parenthesis
							malforme =true;
							break;
						}
						inside=inside+stack_.top();//go till next parenthesis
						stack_.pop();
					}
					stack_.pop();//pop the left parenthesis

					//evaluate the inside
					std::string last = "";

					int pluscount = 0;
					int minuscount = 0;
					bool popfront = false;
					stack_.push("");
					for(unsigned int i=0;i<inside.length();i++){
						
						//std::cout<<inside[i]<<std::endl;

						if(inside[i]!='+' && inside[i]!='-'&& inside[i]!='<' 
							&& inside[i]!='>'){//normal nonCap letters
							if(inside[i]>='a' && (inside[i] <= 'z')
								&& popfront == false){
								last = last+inside[i];
								
							}
							else{
								malforme = true;
								break;
							}
								
						}

						else if(inside[i]=='+'){//plus sign
							popfront = false;
							if(i==inside.length()-1){
								malforme = true;
								break;
							}
							last = stack_.top()+last;
							stack_.pop();
							stack_.push(last);
							
							last = "";
							
							pluscount++;

						}
						else if(inside[i]=='-'){//minus operations
							popfront=false;
							if(i==inside.length()-1|| minuscount>=1){
								malforme = true;
								break;
							}
							
							//std::string holder = minus_(stack_.top(),last);
							stack_.pop();
							stack_.push(last);
							
							last = "";
							minuscount++;
						}
						else if(inside[i]=='<'){
							popfront=true;
							if(last.length()==0){
								malforme=true;
								break;
							}
							if(last.length()>1)
								//remove back
								last = last.substr(1, last.length());
							

						}
						else if(inside[i]=='>'){
							popfront=true;
							if(last.length()==0){
								malforme=true;
								break;
							}
							if(last.length()>1)
								//remove front
								last = last.substr(0, last.length() - 1);


						}
						
					}

					if(pluscount>0&&minuscount>0){
						malforme = true;
						break;
					}
					if(pluscount==0&&minuscount==0){
						malforme = true;
						break;
					}
					if(pluscount>0){
						last = stack_.top()+last;
						stack_.pop();
						stack_.push(last);
						//std::cout<<last<<std::endl;
						last = "";
					}

					if(minuscount>0){
						if(minuscount>1){
							malforme = true;
							break;
						}
						std::string hold = minus_(stack_.top(),last);
						if (hold==""){
							malforme = true;
							break;
						}
						stack_.pop();
						stack_.push(hold);

					}
					
					
					//std::cout<<last<<std::endl;
				}

				
				//std::cout<<temp<<std::endl;
			}
			//std::cout<<stack_.size()<<std::endl;
			if(stack_.size()==0){
				malforme=true;
			}
			if(stack_.size()>=1 && malforme == false){//outside of parentheses
				std::string inside = stack_.top();
				if(inside=="" )
					malforme = true;
				if(inside.length()==1 && ((inside[0] <= 'a') || (inside[0] >= 'z')))
					malforme = true;
				stack_.pop();
				bool popfront = false;
				while(stack_.size()>0 && malforme == false){
					if(stack_.top()[0]!='+' && stack_.top()[0]!='-' 
						&& stack_.top()[0]!='<' && stack_.top()[0]!='>'
						&&stack_.top()[0]!='('){
						if(stack_.top()[0]>='a' && (stack_.top()[0] <= 'z')
							&& been == false && popfront == false)
						//std::cout<<stack_.top()<<std::endl<<'\n';
							inside = inside+stack_.top();
						else{
							malforme = true;
							break;
						}

					}
					else if(stack_.top()[0]=='+'||stack_.top()[0]=='-'
							||stack_.top()[0]=='('){
						malforme = true;
						break;
					}
					else if(stack_.top()[0]=='<'){
						popfront = true;
						if(inside.length()==0){
								malforme=true;
								break;
							}
						if(inside.length()>1)
							//remove back
							inside = inside.substr(1, inside.length());
					}
					else if(stack_.top()[0]=='>'){
						popfront = true;
						if(inside.length()==0){
								malforme=true;
								break;
							}
						if(inside.length()>1)
							//remove front
							inside = inside.substr(0, inside.length() -1);
					}
					else{
						malforme = true;
						break;
					}
					
					stack_.pop();
				}
				
				stack_.push(inside);
			}
			if (stack_.top()=="")
				malforme = true;
			if(stack_.size()==0)
				malforme = true;
			if(malforme == true)
				output<<"Malformed"<<'\n';
			else{
			
				unsigned int strlen = (unsigned int)stack_.top().length();
				for(int i=strlen-1;i>=0;i--)
					output<<stack_.top()[i];
				
				output<<'\n';
				ss.str(std::string());
			}
			
		}
		
		
		
	}
	
	myfile.close();
	output.close();
}