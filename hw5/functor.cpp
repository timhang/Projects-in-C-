#include <iostream>
#include <string>
#include "functor.h"

    bool AlphaStrComp::operator()
    	(const std::string& lhs, const std::string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    };

    bool LengthStrComp::operator()
    	(const std::string& lhs, const std::string& rhs)
    { 
      return lhs.size() < rhs.size(); 
    };


  	bool NumStrComp::operator()
  		(const std::string& lhs, const std::string& rhs)
  	{
  		int lhs1 = 0,rhs1 = 0;
  		for(size_t i=0;i<lhs.size();i++){
  			lhs1+=lhs[i];
  		}
  		for(size_t i=0;i<rhs.size();i++){
  			rhs1+=rhs[i];
  		}
  		if (rhs1 == lhs1){
  			return lhs<rhs;
  		}
  		else
  			return lhs1<rhs1;
  	};



/*template <class Comparator>
void DoStringCompare(const std::string& s1, const std::string& s2, 
					Comparator comp)
{
  std::cout << comp(s1, s2) << std::endl;  // calls comp.operator()(s1,s2);
}

int main(){
  std::string s1 = "Blue";
  std::string s2 = "Red";
  AlphaStrComp comp1;
  LengthStrComp comp2;
  NumStrComp comp3;
  DoStringCompare(s1,s2,comp1);
  // Use string length comparison
  DoStringCompare(s1,s2,comp2);
  DoStringCompare(s1,s2,comp3);
  return 0;
}*/
