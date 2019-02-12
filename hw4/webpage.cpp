#include "webpage.h"
#include <string>
#include <vector>
#include <set>


	WebPage::WebPage(std::string name_){
		name = name_;
	};
	WebPage::~WebPage(){};
	//void parsefile();
	void WebPage::insert_word(std::string content){
		words.push_back(content);
	}
	void WebPage::insert_link(std::string link){
		link_to_file.insert(link);
	}
	//bool WebPage::lookup();
	std::set<std::string> WebPage::getlink(){
		return link_to_file;
	}
	std::vector<std::string> WebPage::getwords(){
		return words;
	}
	std::string WebPage::getname(){
		return name;
	}
	bool WebPage::if_contain(std::string lookup){
		for(size_t i=0;i<lookup.length();i++){
			if(lookup[i]>='A'&&lookup[i]<='Z')
				lookup[i]+=32;
		}
		for(size_t i=0;i<words.size();i++){
			if (lookup == words[i])
				return true;
		}
		return false;
	}
	//int size();

//	std::vector<std::string> words;
//	std::vector<std::string> link_to_file;
