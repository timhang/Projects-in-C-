#include <iostream>
#include "lliststr.h"
using namespace std;

int main(){
	LListStr list;
	for(int i=0;i<10;i++){
		list.insert(0,"haha");
		cout<<list.get(0)<<endl;
		cout<<list.size()<<endl;
	}
	list.insert(2,"gg");
	cout<<list.get(2)<<endl;
	cout<<list.size()<<endl;
	list.remove(2);
	cout<<list.get(2)<<endl;
	cout<<list.size()<<endl;
	list.remove(0);
	list.remove(0);
	list.remove(0);
	list.remove(6);
	cout<<list.size()<<endl;
	list.set(0, "bala");
	cout<<list.get(0)<<endl;
	list.remove(0);
	cout<<list.get(0)<<endl;
	cout<<list.size()<<endl;
	return 0;
}