#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include"bst.h"
#include"rotateBST.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
template<typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();
protected:
	void splay(Node<Key, Value> *r);
private:
	void insertHelper(const std::pair<const Key, Value>& keyValuePair);
	
	
};

template<typename Key, typename Value>
void SplayTree<Key,Value>::insertHelper(const std::pair<const Key, Value>& keyValuePair){
	 // Simple Case: If tree is empty
    if (this->mRoot == NULL) {
    	return newNode(k);
    }
 
    // Bring the closest leaf node to root
    root = splay(root, k);
 
    // If key is already present, then return
    if (root->key == k) return root;
 
    // Otherwise allocate memory for new node
    struct node *newnode  = newNode(k);
 
    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->key > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
 
    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
 
    return newnode; // newnode becomes new root
}
template<typename Key, typename Value>
void SplayTree<Key,Value>::insert(const std::pair<const Key, Value>& keyValuePair){
	 this->mRoot = insertHelper(this->mRoot,keyValuePair);
}
template<typename Key, typename Value>
void SplayTree<Key,Value>::remove(const Key& key){

}
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key,Value>::find(const Key& key){
	//This function should splay the node with the specified key to the root, and return an iterator
	 //to that item. If the key is not found, splay the last visited node to the root, 
	 //and return the end iterator.
}
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key,Value>::findMin(){
//This function finds the node with the minimum key value and splays it to the root. 
//Returns an iterator to the item with the minimum value key.
}
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key,Value>::findMax(){
//This function finds the node with the maximum key value and splays it to the root. 
//Returns an iterator to the item with the maximum value key.
}
template<typename Key, typename Value>
void SplayTree<Key,Value>::deleteMinLeaf(){
//This function deletes the leaf with minimum key value, exactly as if you had called the remove function.
}
template<typename Key, typename Value>
void SplayTree<Key,Value>::deleteMaxLeaf(){
//This function deletes the leaf with maximum key value, exactly as if you had called the remove function.
}
template<typename Key, typename Value>
Node<Key,Value>* SplayTree<Key,Value>::splayHelper(Node<Key, Value> *r,const Key& key){
	// Base cases: root is NULL or key is present at root
	if (r == NULL || r->getKey() == key)
        return r;
 
    // Key lies in left subtree
    if (r->getKey() > key)
    {
        // Key is not in tree, we are done
        if (r->getLeft() == NULL) return r;
 
        // Zig-Zig (Left Left)
        if (r->getLeft()->getKey() > key)
        {
            // First recursively bring the key as root of left-left
            r->getLeft()->setLeft(splayHelper(r->getLeft()->getLeft(), key));
 
            // Do first rotation for root, second rotation is done after else
            rightRotate(r);
        }
        else if (r->getLeft()->getKey() < key) // Zig-Zag (Left Right)
        {
            // First recursively bring the key as root of left-right
            r->getLeft()->setRight(splayHelper(r->getLeft()->getRight(), key));
 
            // Do first rotation for root->left
            if (r->getLeft()->getRight() != NULL)
                leftRotate(r->getLeft());
        }
 
        // Do second rotation for root
        if (r->getLeft() == NULL)
        	return r;
        else{
        	rightRotate(r);
        	return r;
        }
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (r->getRight() == NULL) return r;

        // Zig-Zag (Right Left)
        if (r->getRight()->getKey() > key)
        {
            // Bring the key as root of right-left
            r->getRight()->setLeft(splayHelper(r->getRight()->getLeft(), key));
 
            // Do first rotation for root->right
            if (r->getRight()->getLeft() != NULL)
            	rightRotate(r->getRight());
                r->setRight(r->getRight());
        }
        else if (r->getRight()->getKey() < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of right-right and do first rotation
            r->getRight()->setRight(splayHelper(r->getRight()->getRight(), key));
            leftRotate(r);
        }
 
        // Do second rotation for root
        if(r->getRight() == NULL)
        	return r;
        else{
        	leftRotate(r);
        	return r;
        }
    }
}
template<typename Key, typename Value>
void SplayTree<Key,Value>::splay(Node<Key, Value> *r){
	this->mRoot = splayHelper(this->mRoot,r->getKey());
    
}
#endif