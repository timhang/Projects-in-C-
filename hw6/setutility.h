#include<set>
#include<vector>


template <typename T>
typename std::set<T> intersectT(std::set<T> lhs, 
									  std::set<T> rhs){
	std::set<T> resultant;
	typename std::set<T>::iterator it = lhs.begin();
	for(it = lhs.begin();it!=lhs.end();++it){
		if(rhs.find(*it)!=rhs.end())
			resultant.insert(*(rhs.find(*it)) );
	}
	return resultant;
};

template <typename T>
typename std::set<T> unionT(std::set<T> lhs,
								std::set<T> rhs){
	std::set<T> resultant;
	typename std::set<T>::iterator it;
	for(it = lhs.begin();it!=lhs.end();++it){
		//if( rhs.find(*it)!=rhs.end() )
			resultant.insert(*it);
	}
	for(it = rhs.begin();it!=rhs.end();++it){
		//if( lhs.find(*it)!=lhs.end() )
		resultant.insert(*it);
	}
			
	return resultant;
};