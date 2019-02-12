#include "lliststr.h"
#include <iostream>
#include <new>
#include <string>


  /**
   * Default constructor
   */

	LListStr::LListStr(){
		head_ = NULL;
		tail_ = NULL;
		size_ = 0;
	}

  /**
   * Destructor
   */
  	LListStr::~LListStr(){
        Item* n = head_;
        while(size_>1){
            delete n->prev;
            size_--;
            if(size_!=1)
                n = n->next;
        }
        
        if(size_==0) return;
        if(size_==1){
            n->prev=NULL;
            n->next=NULL;
            delete n;
            size_--;
            return;
        } 
        
        //delete head_;*/
  	}

  /**
   * Returns the current number of items in the list
   */
  	int LListStr::size() const{
  		return size_;
  	}

  /**
   * Returns true if the list is empty, false otherwise
   */
  	bool LListStr::empty() const{
  		if (size_ == 0)
  			return true;
  		else
  			return false;
  	}

  /**
   * Inserts val so it appears at the index given as pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  	void LListStr::insert(int pos, const std::string &val){
  		if(pos>size_||pos<0) return;
  		if(size_==0){
  				Item* n = new Item;
  				n->prev = NULL;
  				n->next = NULL;
  				n->val = val;
  				head_ = n;
  				tail_ = n;
  				size_++;
  				return;
  		}
  		if(size_==pos){
  			push_back(val);
  			return;
  		}
  		if(pos == 0){
  			push_front(val);
  			return;
  		}

  		Item*temp = head_;
  		for(int i=0;i<pos;i++)
  			temp = temp->next;
  		Item* n = new Item;
  		n->val = val;
  		n->prev = temp->prev;
  		n->next = temp;
  		temp->prev->next = n;
  		temp->prev = n;
  		size_++;
  	}

  /**
   * Removes the value at the index given by pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  	void LListStr::remove(int pos){
  		if(pos>size_-1||pos<0||size_<1) return;
        if(size_==1){
            head_->prev = NULL;
            head_->next = NULL;
            delete head_;
            head_=NULL;
            tail_=NULL;
            size_--;
            return;
        }
        if(size_-1==pos){
            //pop_back();
            //if(size==1) NULL
            Item * temp = tail_;
            tail_ = tail_->prev;
            delete temp;
            tail_->next = head_;
            size_--;
            return;

        }
        if(pos==0){
            //pop_front();
            Item * temp = head_;
            head_ = head_->next;
            delete temp;
            head_->prev = tail_;
            size_--;
            return;
        }
  		Item*temp = head_;
  		for(int i=0;i<pos;i++){
  			temp = temp->next;
  		}
  		temp->prev->next = temp ->next;
  		temp->next->prev = temp->prev;
  		delete temp;
  		size_--;
  		return;
  	}

  /**
   * Overwrites the old value at the index given by pos with val. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  	void LListStr::set(int pos, const std::string &val){
  		if(pos<0||pos>size_-1||size_<1) return;
  		Item* temp = head_;
  		for(int i=0;i<pos;i++)
  			temp = temp->next;
  		temp->val = val;
  		return;
  	}

  /**
   * Returns the value at the index given by pos.  If the index pos is invalid,
   * then you should return the empty string.
   */
  	std::string LListStr::get(int pos) const{
  		if(pos<0||pos>size_-1||size_<1) return std::string();
  		Item* temp = head_;
  		for(int i=0;i<pos;i++){
  			temp=temp->next;
  		}
  		return temp->val;
  	}


  	

  	// Feel free to add private helper functions if you desire.
    

  	void LListStr::push_front(const std::string &val){
  		Item * n = new Item;
  		n->val = val;
  		n->next = head_;
  		head_->prev = n;
  		head_ = n;
  		tail_->next = head_;
  		head_->prev = tail_;
  		size_++;
  	};

  	void LListStr::push_back(const std::string &val){
  		Item* n = new Item;
  		n->val = val;
  		n->prev = tail_;
  		tail_->next = n;
  		tail_ = n;
  		tail_ -> next = head_;
  		head_ ->prev = tail_;
  		size_++;
  	};
  	/**
   	* Data members
   	*/
  	