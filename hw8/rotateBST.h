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
private:
	void transformHelper1(Node<Key,Value>* r,rotateBST& t2) const;
	void transformHelper2(Node<Key,Value>* root,rotateBST& t2,Node<Key,Value>* root2) const;
	int heightHelper(Node<Key,Value>* root);
	//void leftRotateHelper(Node<Key, Value>* r,rotateBST& t2) const;
	//void rightRotateHelper(Node<Key, Value>* r,rotateBST& t2) const;
};

template<typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const{
	rotateBST<Key,Value> temp1(*this);
	rotateBST<Key,Value> temp2(t2);
	

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
	
	//if(temp1->mRoot==temp2->mRoot)
	//	return true;
	return true;

}

template<typename Key, typename Value>
void rotateBST<Key,Value>::transformHelper1(Node<Key,Value>* root,rotateBST& t2) const{
	if(root==NULL) return;
	
	while(root->getLeft()!=NULL){
		t2.rightRotate(root);
		if(root->getParent()!=NULL)
			root = root->getParent();
	}

	transformHelper1(root->getRight(),t2);
	
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::transformHelper2(Node<Key,Value>* root,rotateBST& t2,Node<Key,Value>* root2) const{
/*Perform right rotations on the root node of t2 until it has no left child.
Recursively move to the right child and repeat the above operation.
This should produce a tree which is effectively a linked list.
Now perform left rotations on the root node of t2, until the root of t2 is the same as the root of this.
Recursively do rotations on the left child and the right child until they match the node at that position of this.
This should produce the specified tree using only rotations.*/
	if(root==NULL||root2==NULL) return;
	
	while(root->getRight()!=NULL&&root->getKey()!=root2->getKey()){
		t2.leftRotate(root);
		if(root->getParent()!=NULL)
			root = root->getParent();
	}
	//std::cout<<"test"<<std::endl;
	transformHelper2(root->getLeft(),t2,root2->getLeft());
	transformHelper2(root->getRight(),t2,root2->getRight());
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::transform(rotateBST& t2) const{
	//rotateBST<Key,Value> temp2 = t2;
	//Node<Key,Value>* r = temp2.mRoot;
	//std::cout<<t2.mRoot->getHeight()<<std::endl;
	//if(sameKeys(t2)){
	
		transformHelper1(t2.mRoot,t2);//get to linked list form
		transformHelper2(t2.mRoot,t2,this->mRoot);
	//}

	//std::cout<<t2.mRoot->getHeight()<<std::endl;
	
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key, Value>* r){
	if((r!=NULL)&& (r->getRight()!=NULL)){
		Node<Key,Value>*temp = r->getRight();//this is node q
		r->setRight(temp->getLeft());
		if(temp->getLeft()!=NULL)
			temp->getLeft()->setParent(r);
		temp->setParent(r->getParent());
		if(r->getParent()==NULL){
			this->mRoot = temp;
		}
		else if(r == r->getParent()->getLeft()){
			r->getParent()->setLeft(temp);
		}
		else{
			r->getParent()->setRight(temp);
		}
		temp->setLeft(r);//set node q left child to be p
		r->setParent(temp);//set node p parent to q
		/*if(r->getLeft()==NULL&&r->getRight()==NULL)
			r->setHeight(1);
		else if(r->getLeft()==NULL&&r->getRight()!=NULL)
			r->setHeight(r->getRight()->getHeight()+1);
		else if(r->getLeft()!=NULL&&r->getRight()==NULL)
			r->setHeight(r->getLeft()->getHeight()+1);
		else{
			r->setHeight(std:max(r->getRight()->getHeight(),r->getLeft()->getHeight())+1);
		}*/
		heightHelper(this->mRoot);
	}
}
template<typename Key, typename Value>
int rotateBST<Key, Value>::heightHelper(Node<Key,Value>* root){
	if (root==NULL){
		return 0;
	}
	int left = heightHelper(root->getLeft());
	int right = heightHelper(root->getRight());
	root->setHeight(std::max(left,right)+1);
	return std::max(left,right)+1;
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key, Value>* r){
	if((r!=NULL)&& (r->getLeft()!=NULL)){
		Node<Key,Value>*temp = r->getLeft();//this is node q
		r->setLeft(temp->getRight());
		if(temp->getRight()!=NULL)
			temp->getRight()->setParent(r);
		temp->setParent(r->getParent());
		if(r->getParent()==NULL){
			this->mRoot = temp;
		}
		else if(r == r->getParent()->getLeft()){
			r->getParent()->setLeft(temp);
		}
		else{
			r->getParent()->setRight(temp);
		}
		temp->setRight(r);//set node q right child to be p
		r->setParent(temp);//set node p parent to q
		/*if(r->getLeft()==NULL&&r->getRight()==NULL)
			r->setHeight(1);
		else if(r->getLeft()==NULL&&r->getRight()!=NULL)
			r->setHeight(r->getRight()->getHeight()+1);
		else if(r->getLeft()!=NULL&&r->getRight()==NULL)
			r->setHeight(r->getLeft()->getHeight()+1);
		else{
			r->setHeight(std:max(r->getRight()->getHeight(),r->getLeft()->getHeight())+1);
		}
		if(temp->getLeft()==NULL){
			temp->setHeight()
		}*/
		heightHelper(this->mRoot);
	}
}

#endif