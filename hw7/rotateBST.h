#ifndef RORATEBST_H
#define ROTATEBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include "bst.h"
template<typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
public:
	//rotateBST(const Key& key, const Value& value);
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;

protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
};

template<typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const{
	rotateBST<Key,Value> temp1 = *this;
	rotateBST<Key,Value> temp2 = t2;
	//rotateBST<Key,Value> temp = this;
	typename rotateBST<Key,Value>::iterator it = temp1.begin();
	typename rotateBST<Key,Value>::iterator at = temp2.begin();
	while(it!=temp1.end()){
		if(at!=temp2.end()){
			if(it->first!=at->first){
				return false;
			}
			++it;
			++at;
		}
		else
			return false;
	}
	if(at!=temp2.end()) return false;
	//if(it==temp)
	return true;

}

template<typename Key, typename Value>
void rotateBST<Key,Value>::transform(rotateBST& t2) const{
	//while(t2->m)
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key, Value>* r){
	if((r!=NULL)&& (r->getRight()!=NULL)){
		Node<Key,Value>*temp = r->getRight();//this is node q
		r->setRight(r->getRight()->getLeft());
		if(r->getRight()!=NULL)
			r->getRight()->setParent(r);
		temp->setLeft(r);//set node q left child to be p
		temp->setParent(NULL);
		r->setParent(temp);//set node p parent to q
		r= temp; //set q to be new root
	}
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key, Value>* r){
	if((r!=NULL)&& (r->getLeft()!=NULL)){
		Node<Key,Value>*temp = r->getLeft();
		r->setLeft(r->getLeft()->getRight());
		if(r->getLeft()!=NULL)
			r->getLeft()->setParent(r);
		temp->setRight(r);
		temp->setParent(NULL);
		r->setParent(temp);
		r= temp; 
	}
}

#endif