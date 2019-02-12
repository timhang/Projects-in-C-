#include <iostream>
#include "lliststr.h"
#include "stackstr.h"
#include <string>
#include <sstream>
//using namespace std;
int main(){
	StackStr stack_;
	std::cout<<stack_.size()<<'\n';
	stack_.push("haha");
	std::cout<<stack_.size()<<'\n';
	std::cout<<stack_.top()<<'\n';
	stack_.pop();
	std::cout<<stack_.size()<<'\n';
	stack_.pop();
	std::cout<<stack_.size()<<'\n';
	stack_.pop();
	for(int i=0;i<10000;i++){
		std::stringstream ss;
		ss<<i;
		std::string str = ss.str();
		stack_.push(str);
		//std::cout<<stack_.top()<<" "<<stack_.size()<<'\n';
		//stack_.pop();
	}
	std::cout<<stack_.size()<<'\n';
	return 0;
}