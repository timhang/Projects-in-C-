#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "webpage.h"
#include<set>
#include<map>

std::set<std::string> intersectString(std::set<std::string> lhs, 
									  std::set<std::string> rhs){
	std::set<std::string> resultant;
	std::set<std::string>::iterator it = lhs.begin();
	for(it = lhs.begin();it!=lhs.end();++it){
		resultant.insert(*(rhs.find(*it)) );
	}
	return resultant;
}
std::set<WebPage*> intersectWebPage(std::set<WebPage*> lhs,
									std::set<WebPage*> rhs){
	std::set<WebPage*> resultant;
	std::set<WebPage*>::iterator it = lhs.begin();
	for(it = lhs.begin();it!=lhs.end();++it){
		//if( (*rhs.find(*it))!=NULL )
			std::set<WebPage*>::iterator at = rhs.begin();
			for(at = rhs.begin();at!=rhs.end();++at){
				if((*it)->getname()==(*at)->getname()){
					resultant.insert(*at);
				}
			}

			
	}
	return resultant;
}
std::set<WebPage*> unionWebPage(std::set<WebPage*> lhs,
								std::set<WebPage*> rhs){
	std::set<WebPage*> resultant;
	std::set<WebPage*>::iterator it;
	for(it = lhs.begin();it!=lhs.end();++it){
		//if( (*rhs.find(*it))!=NULL )
		resultant.insert(*it);
	}
	for(it = rhs.begin();it!=rhs.end();++it){
		resultant.insert(*it);
	}
			
	return resultant;
}

void AND(std::stringstream &ss, std::set<WebPage*> &result,
		std::map <std::string, std::set<WebPage*> > &webmap,
		std::set<std::string> &keywords){

	std::string word;
	std::set<std::string> search_words;
	std::set<WebPage*> lhs;
	while(ss>>word){
		for(size_t i=0;i<word.length();i++){
			if(!(word[i]<='z' && word[i]>='a')&&
			   !(word[i]<='Z' && word[i]>='A')&&
			   !(word[i]<='9' && word[i]>='0')){
				return;
			}
			else if(word[i]<='Z' && word[i]>='A')
				word[i]+=32;
		}
		search_words.insert(word);
	}
	search_words = intersectString(search_words,keywords);
	if(search_words.size()==0) search_words.insert("and");
	if(search_words.size()==1){
		result = webmap.find(*search_words.begin())->second;
		return;
	}
	std::set<std::string>::iterator at = search_words.begin();
	//needs to handle exceptions here
	lhs = webmap.find(*search_words.begin())->second;

	std::set<WebPage*>::iterator it = lhs.begin();

	for(at=search_words.begin();at!=search_words.end();++at){
		

		lhs = intersectWebPage(lhs, webmap.find(*at)->second );
		//output<<(*it)<<" ";
	}
	result = lhs;
}

void OR(std::stringstream &ss, std::set<WebPage*> &result,
		std::map <std::string, std::set<WebPage*> > &webmap,
		std::set<std::string> &keywords){
	std::string word;
	std::set<std::string> search_words;
	std::set<WebPage*> lhs;
	while(ss>>word){
		for(size_t i=0;i<word.length();i++){
			if(!(word[i]<='z' && word[i]>='a')&&
			   !(word[i]<='Z' && word[i]>='A')&&
			   !(word[i]<='9' && word[i]>='0')){
				return;
			}
			else if(word[i]<='Z' && word[i]>='A')
				word[i]+=32;
		}
		search_words.insert(word);
	}
	search_words = intersectString(search_words,keywords);
	if(search_words.size()==0) search_words.insert("or");
	if(search_words.size()==1){
		result = webmap.find(*search_words.begin())->second;
		return;
	}
	std::set<std::string>::iterator it = search_words.begin();
	//needs to handle exceptions here
	lhs = webmap.find(*search_words.begin())->second;
	for(it=search_words.begin();it!=search_words.end();++it){
		lhs = unionWebPage(lhs, webmap.find(*it)->second );
		//output<<(*it)<<" ";
	}
	result = lhs;
}

void OUTGOING(std::string name,std::ofstream &output,
			  std::set<WebPage*> &webpages){
	std::set<WebPage*>::iterator it = webpages.begin();
	std::set<std::string> links;
	for(it=webpages.begin();it!=webpages.end();++it){
		if((*it)->getname() == name){
			output<<(*it)->getlink().size()<<'\n';
			links = (*it)->getlink();
			break;
		}
	
	}
	std::set<std::string>::iterator at = links.begin();
	for(at = links.begin(); at!= links.end(); at++){
				output<<(*at)<<'\n';
	}
}

void INCOMING(std::string link, std::ofstream &output,
			  std::set<WebPage*> &webpages){
	std::set<WebPage*>::iterator it = webpages.begin();
	std::set<std::string> links;
	std::set<WebPage*> result;
	for(it=webpages.begin();it!=webpages.end();++it){
		links = (*it)->getlink();
		std::set<std::string>::iterator at = links.begin();
		for(at = links.begin(); at!= links.end(); at++){
			if(link == (*at)){
				result.insert(*it);
				//output<<(*it)->getname()<<'\n';
				break;
			}
		}
	}
	output<<result.size()<<'\n';
	for(it = result.begin();it!=result.end();it++){
		output<<(*it)->getname()<<'\n';
	}
}

void PRINT(std::string name, std::ofstream &output){
	const char* filename = name.c_str();//convert string to filename
	std::ifstream pagefile(filename);
	output<<name<<'\n';
	if(!pagefile) {std::cout<<"Unable to open webpage file"<<std::endl;
				return;}

	std::string textline;//each line in webpage file
	while(getline(pagefile,textline)){//get lines from web files
		std::stringstream ss;
		std::string word;
		std::string result="";
		bool parenth = false;
		for(size_t i=0;i<textline.size();i++){
			//replacing special characters with space
			if((textline[i] != '(' && textline[i]!=')') && parenth == false){
				result = result+textline[i];
			}
			else if(textline[i] == '(') {
				parenth = true;
			}
			else if(textline[i] == ')'){
				parenth = false;
			}
		}
		ss.clear();
		output<<result<<'\n';
	}
	pagefile.close();
}

int main(int argc, char* argv[]){
	if(argc<4){
		std::cout<<"Please provide three files: index, query, and output.";
		return 1;
	}
	std::ifstream index_(argv[1]);
	std::ifstream query_(argv[2]);
	std::ofstream output(argv[3]);
	std::set<WebPage*> webpages;
	std::set<std::string> keywords;
	std::map<std::string, std::set<WebPage*> > webmap;
	//int pagecount = 0;

	if(!index_ || !query_){std::cout<<"Unable to open files"<<std::endl;
		return 1;}
	while(index_.good()){
		std::string line;//each line in index.txt
		while(getline(index_, line)){//get lines from index.txt
			//std::cout<<line<<std::endl;
			//pagecount++;
			WebPage* page = new WebPage(line);
			const char* filename = line.c_str();//convert string to filename
			std::ifstream pagefile(filename);

			if(!pagefile) {std::cout<<"Unable to open webpage file"<<std::endl;
						return 1;}

			std::string textline;//each line in webpage file
			while(getline(pagefile,textline)){//get lines from web files
				std::stringstream ss;
				std::string word;
				bool parenth = false;
				for(size_t i=0;i<textline.size();i++){
					//replacing special characters with space
					if(!(textline[i]<='z' && textline[i]>='a')&&
						!(textline[i]<='Z' && textline[i]>='A')&&
						!(textline[i]<='9' && textline[i]>='0')){
						//output<<textline[i]<<'\n';
						if(textline[i] == '(') {parenth = true;
							textline.replace(i,1,"( ");
						}
						if(textline[i] == ')') parenth = false;
						if(parenth == false)
							textline.replace(i,1," ");
					}
					if(textline[i]<='Z' && textline[i]>='A')
							textline[i] = textline[i]+32;
				}
				ss<<textline;
				
				std::string link;
				
				while(ss>>word){
					
					if(word == "(") {ss>>link;
						//store the link
						page->insert_link(link);
					}
					else{
						//store the word

						page->insert_word(word);
						keywords.insert(word);
						if(webmap.size()==0){
							std::set<WebPage*> temp;
							temp.insert(page);
;
							webmap.insert(std::pair<std::string, 
							std::set<WebPage*> >(word,temp));
						}
						else{
							std::set<WebPage*> temp=webmap.find(word)->second;
							temp.insert(page);
							
							webmap.erase(word);
							webmap.insert(std::pair<std::string, 
										  std::set<WebPage*> >(word,temp));
						}
					}
				}
				
				ss.clear();
				textline = "";
			}
			
			pagefile.close();

			/*std::vector<std::string> temp = page->getwords();
			for(size_t i=0;i<temp.size();i++)
				output<<temp[i]<<'\n';
			output<<page->getname()<<'\n';*/
			webpages.insert(page);
			//output<<page.if_contain("ucla")<<'\n';
		}
		
	}
	
	while(query_.good()){
		std::string line;//each line in index.txt
		while(getline(query_, line)){//get lines from index.txt
			//parse lines of query
			std::stringstream ss;
			std::string first;
			ss<<line;
			ss>>first;
			std::set<WebPage*> result;
			bool print_ = false;
			if(first=="AND"){
				//output<<"AND found!"<<'\n';
				AND(ss, result, webmap, keywords);
				
				//webmap.insert(std::make_pair("ucla", webpages ) );
			}
			else if(first == "OR"){
				//output<<"OR found!"<<'\n';
				
				OR(ss, result, webmap, keywords);
				
			}
			else if(first == "PRINT"){
				//output<<"PRINT found!"<<'\n';
				std::string name;
				if(ss>>name){
					PRINT(name,output);
					print_ = true;
				}
				else{
					//AND(ss,result,webmap,keywords,output);
					result = webmap.find("print")->second;
				}
				
			}
			else if(first == "INCOMING"){
				std::string name;
				if(ss>>name){
					INCOMING(name,output,webpages);
					print_ = true;
				}
				else{
					result = webmap.find("incoming")->second;
				}
				
			}
			else if(first == "OUTGOING"){
				std::string name;
				if(ss>>name){
					OUTGOING(name,output, webpages);
					print_ = true;
				}
				else{
					result = webmap.find("outgoing")->second;
				}
				
			}
			else{
				
				/*Second Edition*/
				std::string name;
				if(!(ss>>name)){
					for(size_t i=0;i<first.length();i++){
						if(first[i]<='Z' && first[i]>='A')
							first[i]+=32;
					}
					result = webmap.find(first)->second;
				}
				/*Second Edition ends here*/
				else{
					output<<"Invalid query"<<"\n";
					continue;
				}
			}
			//output results
			if(print_ == false){
				if(result.size()>0){
					std::set<WebPage*>::iterator it = result.begin();
					output<<result.size()<<'\n';
					for(it = result.begin();it!=result.end();++it)
						output<<(*it)->getname()<<'\n';
					
				}
				else
					output<<0<<'\n';
			}
		}
	}
	//Free up memory here
	

	//output<<(*(webmap.begin()->second).begin())->getname()<<'\n';
	std::set<WebPage*>::iterator at = webpages.begin();
	for(at=webpages.begin();at!=webpages.end();++at)
		delete (*at);
		//output<< (*it)->  getname() <<'\n';
	index_.close();
	query_.close();
	output.close();
	return 0;
}