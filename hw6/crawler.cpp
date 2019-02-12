#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>


std::pair<std::vector<std::string> ,bool> webparser(std::string name){
	std::pair<std::vector<std::string>, bool> resultant;
	resultant.second = true;
	std::ifstream seed_(name.c_str());
	if(seed_.fail()){std::cout<<"404 Not Found: "<<name<<std::endl;
		return std::pair<std::vector<std::string>, bool>
			 			(std::vector<std::string>(), false);
	}
	while(seed_.good()){
		std::string textline;//each line in index.txt
		while(getline(seed_, textline)){//get lines from index.txt
			//get lines from web files
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
					/*if(textline[i]<='Z' && textline[i]>='A')
							textline[i] = textline[i]+32;*/
				}
				ss<<textline;
				
				std::string link;
				
				while(ss>>word){
					
					if(word == "(") {ss>>link;
						//store the link
						resultant.first.push_back(link);
					}
				}
				
				ss.clear();
				textline = "";
			//
		}
		
	}
	seed_.close();
	return resultant;
}

void crawl_helper(std::string curr, 
		   std::set<std::string> &visited,std::ofstream &output){
	//what if
	std::pair<std::vector<std::string>,bool> links;
	links = webparser(curr);
	if(links.second==false) return;
	if(visited.find(curr)==visited.end())
		output<<curr<<std::endl; 
	visited.insert(curr);
		
	//std::cout<<visited.size()<<std::endl;
	std::vector<std::string>::iterator it;
	for(it = links.first.begin();it!=links.first.end();++it){
		if(visited.find(*it)==visited.end()){
			//visited.insert(*it);
			crawl_helper(*it,visited,output);
		}
	}
}

void crawl(std::string name, std::ofstream &output){
	std::set<std::string> visited;
	//visited.insert(curr);
	/*if(links.length() == 0 || linkbool[links] == true){
		return;
	}*/
	std::ifstream seed_(name.c_str());
	if(seed_.fail()){std::cout<<"Unable to open seed file"<<std::endl;
		return;}
	while(seed_.good()){
		std::string textline;//each line in index.txt
		while(getline(seed_, textline)){
			if(!(visited.find(textline)!=visited.end()))
				crawl_helper(textline,visited,output);
		}
	}
	

}

void readConfig(std::string name,std::map<std::string, std::string> &content){
	std::ifstream config(name.c_str());
	while(config.good()){
		std::string line;
		std::string word;
		
		while(getline(config,line)){
			std::stringstream ss;
			std::string line_result;
			for(size_t i=0;i<line.size();i++){
				if(line[i]=='#'){
					break;
				}
				
				if(line[i]==' '){
					continue;
				}
				if(line[i]=='='){
					line.replace(i,1," ");
				}
				
				line_result = line_result+line[i];

			}
			ss<<line_result;
			//std::cout<<ss.str()<<std::endl;
			while(ss>>word){
				//std::cout<<"MARK  ";
				if(word=="INDEX_FILE"){
					ss>>word;
					content.insert(std::pair<std::string, std::string>
									("INDEX_FILE", word));
				}
				if(word=="OUTPUT_FILE"){
					ss>>word;
					content.insert(std::pair<std::string, std::string>
									("OUTPUT_FILE", word));
				}
				if(word=="QUERY_FILE"){
					ss>>word;
					content.insert(std::pair<std::string, std::string>
									("QUERY_FILE", word));
				}
			}
		}
	}
}

int main(int argc, char* argv[]){
	//std::ifstream seed_();
	if(argc>2){
		std::cout<<"Error: More than one file is provided";
		return 1;
	}
	std::map<std::string, std::string> content;
	if(argc==2) readConfig(argv[1], content);
	if(argc==1) readConfig("config.txt", content);
	
	std::ofstream output(content.find("OUTPUT_FILE")->second.c_str());
	//std::map<std::string, std::set<std::string> > outlinks;
	//std::string name = 
	crawl(content.find("INDEX_FILE")->second.c_str(),output);
	return 0; 


}
/*in order to crawl, need to parse the seed files, find the links
  and parse the files in the links, until all options are exhausted
  print out all the files in the order they've been discovered.
	
  Now I need to fix the visited and make sure the links are outputed 
  in the order they are discovered. 
  Need to make sure that visited nodes do not get outputted again
  Also, files that can't be opened should not be outputted.
*/