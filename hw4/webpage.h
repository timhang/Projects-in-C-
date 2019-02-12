#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <string>
#include <vector>
#include <set>

class WebPage{

public:
	WebPage(std::string name_);
	~WebPage();
	//void parsefile();
	void insert_word(std::string content);
	void insert_link(std::string link);
	//void print();
	std::set<std::string> getlink();
	std::vector<std::string> getwords();
	//int size();
	std::string getname();
	bool if_contain(std::string lookup);
private:
	std::vector<std::string> words;
	std::set<std::string> link_to_file;
	std::string name;
};

#endif