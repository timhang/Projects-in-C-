#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "webpage.h"
#include "setutility.h"
#include<set>
#include<map>
#include<vector>

std::set<std::string> candidateSet(std::map<std::string, WebPage*> &webpages,
			   std::set<WebPage*> &result);
void PageRank(std::map<std::string, WebPage*> &webpages,
			  std::set<std::string> candidate,
			  std::map<std::string, double> &constants,
			  std::ofstream &output);

void AND(std::stringstream &ss, std::set<WebPage*> &result,
		std::map <std::string, std::set<WebPage*> > &webmap,
		std::set<std::string> &keywords){

	std::string word;
	std::set<std::string> search_words;
	std::set<WebPage*> lhs;
	while(ss>>word){
		for(size_t i=0;i<word.length();i++){
			/*if(!(word[i]<='z' && word[i]>='a')&&
			   !(word[i]<='Z' && word[i]>='A')&&
			   !(word[i]<='9' && word[i]>='0')){
				return;
			}
			else */
			if(word[i]<='Z' && word[i]>='A')
				word[i]+=32;
		}
		search_words.insert(word);
	}

	if(search_words.size()==0) search_words.insert("and");
	search_words = intersectT(search_words,keywords);
	//std::cout<<search_words.size();
	if(search_words.size()==0) return;
	
	if(search_words.size()==1){
		result = webmap.find(*search_words.begin())->second;
		return;
	}
	std::set<std::string>::iterator at = search_words.begin();
	//needs to handle exceptions here
	lhs = webmap.find(*search_words.begin())->second;

	std::set<WebPage*>::iterator it = lhs.begin();

	for(at=search_words.begin();at!=search_words.end();++at){
		

		lhs = intersectT(lhs, webmap.find(*at)->second );
		//output<<(*it)<<" ";
	}
	result = lhs;
	//std::cout<<result.size()<<std::endl;
}

void OR(std::stringstream &ss, std::set<WebPage*> &result,
		std::map <std::string, std::set<WebPage*> > &webmap,
		std::set<std::string> &keywords){

	std::string word;
	std::set<std::string> search_words;
	std::set<WebPage*> lhs;

	while(ss>>word){
		for(size_t i=0;i<word.length();i++){
			/*if(!(word[i]<='z' && word[i]>='a')&&
			   !(word[i]<='Z' && word[i]>='A')&&
			   !(word[i]<='9' && word[i]>='0')){
				return;
			}
			else*/
			if(word[i]<='Z' && word[i]>='A')
				word[i]+=32;
		}
		search_words.insert(word);
	}
	if(search_words.size()==0) search_words.insert("or");
	search_words = intersectT(search_words,keywords);
	//std::cout<<search_words.size();

	if(search_words.size()==0) return;
	if(search_words.size()==1){
		result = webmap.find(*search_words.begin())->second;
		return;
	}
	std::set<std::string>::iterator it = search_words.begin();
	//needs to handle exceptions here
	lhs = webmap.find(*search_words.begin())->second;
	for(it=search_words.begin();it!=search_words.end();++it){
		lhs = unionT(lhs, webmap.find(*it)->second );
		//output<<(*it)<<" ";
	}
	result = lhs;
	//std::cout<<result.size()<<std::endl;
}

void OUTGOING(std::string name,std::ofstream &output,
			  std::map<std::string, WebPage*> &webpages){
	//print outgoing links
	std::map<std::string, WebPage*>::iterator it;
	it = webpages.find(name);
	std::set<std::string> links;
	links = webpages.find(name)->second->getlink();
	output<<(it->second)->getlink().size()<<std::endl;
	
	std::set<std::string>::iterator at = links.begin();
	for(at = links.begin(); at!= links.end(); at++){
				output<<(*at)<<'\n';
	}
}

void INCOMING_LINKS(std::string link,
			  std::map<std::string, WebPage*> &webpages){
	//storing the incoming links a webpage;
	std::map<std::string, WebPage*>::iterator it;
	std::map<std::string, WebPage*>::iterator temp = webpages.find(link);
	std::set<std::string> links;
	std::set<std::string> result;
	for(it=webpages.begin();it!=webpages.end();++it){
		links = it->second->getlink();
		if(links.find(link)!=links.end()){//if can find in outgoing links
			result.insert(it->first);
		}
	}
	temp->second->set_incoming(result);
}

void INCOMING(std::string link, std::ofstream &output,
			  std::map<std::string, WebPage*> &webpages){
	//print incoming links
	INCOMING_LINKS(link,webpages);
	std::map<std::string, WebPage*>::iterator it;
	std::set<std::string> result;
	it = webpages.find(link);
	output<<(it->second->get_incoming().size())<<'\n';
	result = it->second->get_incoming();
	
	std::set<std::string>::iterator at;
	for(at = result.begin();at!=result.end();at++){
		output<<(*at)<<'\n';
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

void readConfig(std::string name,std::map<std::string, std::string> &content,
				std::map<std::string, double> &constants){
	//reading the config file, storing the info in a map
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
				if(word=="RESTART_PROBABILITY"){
					double a;
					ss>>a;
					constants.insert(std::pair<std::string, double>
									("RESTART_PROBABILITY", a));
				}
				if(word=="STEP_NUMBER"){
					double a;
					ss>>a;
					constants.insert(std::pair<std::string, double>
									("STEP_NUMBER", a));
				}
			}
		}
	}
}

int main(int argc, char* argv[]){
	if(argc>2){
		std::cout<<"Error: More than one file is provided";
		return 1;
	}
	//double constants[2];
	std::map<std::string, std::string> content;
	std::map<std::string, double> constants;
	if(argc==2) readConfig(argv[1], content,constants);
	if(argc==1) readConfig("config.txt", content,constants);

	//Looking for the name of the files in the map
	std::ifstream index_(content.find("INDEX_FILE")->second.c_str());
	std::ifstream query_(content.find("QUERY_FILE")->second.c_str());
	std::ofstream output(content.find("OUTPUT_FILE")->second.c_str());
	std::map<std::string, WebPage*> webpages;
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
				std::string word="";
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
						if(webmap.find(word)==webmap.end()){
							std::set<WebPage*> temp;
							temp.insert(page);
							webmap.insert(std::pair<std::string, 
							std::set<WebPage*> >(word,temp));
						}
						else{
							std::set<WebPage*> temp;
							temp = webmap.find(word)->second;
							temp.insert(page);
							
							webmap.erase(word);
							webmap.insert(std::pair<std::string, 
										  std::set<WebPage*> >(word,temp));
						}
						/*if(webmap.size()==0){
							std::set<WebPage*> temp;
							temp.insert(page);
							webmap.insert(std::pair<std::string, 
							std::set<WebPage*> >(word,temp));
						}
						else{
							std::set<WebPage*> temp;
							temp = webmap.find(word)->second;
							temp.insert(page);
							
							webmap.erase(word);
							webmap.insert(std::pair<std::string, 
										  std::set<WebPage*> >(word,temp));
						}*/
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
			webpages.insert(
				std::pair<std::string,WebPage*>(page->getname(),page));
			//output<<page.if_contain("ucla")<<'\n';
		}
		
	}

	while(query_.good()){
		std::string line;//each line in index.txt
		while(getline(query_, line)){//get lines from index.txt
			//parse lines of query
			//std::cout<<line<<std::endl;

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

			if(print_ == false && result.size()>0){
				std::set<std::string> candidate;
				//std::vector<std::string> ranking;
				std::map<double,std::set<size_t> > ranked;
				//getting candidate set
				candidate = candidateSet(webpages,result);
				output<<candidate.size()<<'\n';
				//PageRank here
				PageRank(webpages,candidate,constants,output);
				//std::set<std::string>::iterator it;
					
					/*for(it = candidate.begin();it!=candidate.end();++it)
						output<<(*it)<<'\n';*/
					
					
				
			}
			else{
				if(print_==false)
					output<<0<<'\n';
			}
		}
	}
	//Free up memory here
	

	//output<<(*(webmap.begin()->second).begin())->getname()<<'\n';
	std::map<std::string, WebPage*>::iterator at;
	for(at=webpages.begin();at!=webpages.end();++at)
		delete at->second;
		//output<< (*it)->  getname() <<'\n';
	index_.close();
	query_.close();
	output.close();
	return 0;
}


//This part is for finding candidate set
std::set<std::string> candidateSet(std::map<std::string, WebPage*> &webpages,
			   std::set<WebPage*> &result){
	std::set<WebPage*>::iterator it;
	std::set<std::string> lhs;
	std::set<std::string> rhs;
	std::set<std::string> candidate;
	std::set<std::string> candidate1;
	for(it = result.begin();it!=result.end();++it){
		INCOMING_LINKS((*it)->getname(),webpages);
		lhs = webpages.find((*it)->getname())->second->getlink();
		rhs = webpages.find((*it)->getname())->second->get_incoming();
		candidate = unionT(candidate,unionT(lhs,rhs));
		candidate.insert((*it)->getname());
	}
	//eliminating pages that are not in index
	std::set<std::string>::iterator at;
	for(at = candidate.begin();at!=candidate.end();++at){
		if(webpages.count(*at)!=0)
			candidate1.insert(*at);
	}
	return candidate1;
}

void PageRank(std::map<std::string, WebPage*> &webpages,
			std::set<std::string> candidate,
			  std::map<std::string, double> &constants,
			  std::ofstream &output){
	std::set<std::string>::iterator it;
	std::set<std::string> incoming;
	std::set<std::string> outgoing;
	std::vector<WebPage> webpage_vec;
	std::vector<double> b;
	for(it = candidate.begin();it!=candidate.end();++it){
		INCOMING_LINKS(*it,webpages);
		webpage_vec.push_back(*(webpages.find(*it)->second));
	}
	//eliminate edges not in candidate sub-graph and add self-loop
	//std::vector<WebPage>::iterator i;
	for(size_t i=0;i<webpage_vec.size();i++){
		outgoing = webpage_vec[i].getlink();
		outgoing = intersectT(outgoing,candidate);
		outgoing.insert(webpage_vec[i].getname());
		webpage_vec[i].set_outgoing(outgoing);
		incoming = webpage_vec[i].get_incoming();
		incoming = intersectT(incoming,candidate);
		incoming.insert(webpage_vec[i].getname());
		webpage_vec[i].set_incoming(incoming);
	}
	size_t size = candidate.size();
	//std::cout<<size<<std::endl;
	b.assign(size,double(1/double(size)));
	
    //matrix multiplication
    double RP,step;
    if(constants.find("STEP_NUMBER")==constants.end()
    	||constants.find("RESTART_PROBABILITY")==constants.end()){
    	std::cout<<"Please provide step number and restart probability."
    	<<std::endl;
    	return;
    }
	else{
		RP = constants.find("RESTART_PROBABILITY")->second;
		step = constants.find("STEP_NUMBER")->second;
	}
    double **matrixA;
	matrixA= new double* [size];
	for(size_t i=0;i<size;i++){
		matrixA[i] = new double[size];
	}
	//std::cout<<matrixA[0][0];
    //std::cout<<b[0]<<" "<<b[1]<<" "<<b[2]<<" "<<b[3]<<std::endl;
    //Get matrixA
    for(size_t i=0;i<size;i++){
    	//std::cout<<webpage_vec[i].get_incoming().size()<<" ";
    	for(size_t j=0;j<size;j++){
    		
    		if(webpage_vec[j].getlink().count(webpage_vec[i].getname())==0){
    			matrixA[i][j]=0;
    		}
    		else{
    			matrixA[i][j] = 
    				double(1/double(webpage_vec[j].getlink().size()));
    		}
    		//std::cout<<matrixA[i][j]<<" ";
    	}
    	//std::cout<<std::endl;
    	
    }
    std::vector<double> temp;
    for(double k=0;k<step;k++){
    	
    	temp.assign(size,0);
    	for(size_t i=0;i<size;i++){

    		for(size_t j=0;j<size;j++){
    			temp[i]+=matrixA[i][j]*b[j];
    		}
    	
    		temp[i]*=double(1-RP);
    		temp[i]+=double(RP/double(size));
    	}
    	b=temp;
	}
	//std::cout<<b.size()<<std::endl;
	//utilizing map's ability to sort
	std::map<double,std::set<size_t> > ranked_result;
	for(size_t i=0;i<size;i++){
		std::set<size_t> index;
		if(ranked_result.find(b[i])==ranked_result.end()){

			index.insert(i);
			ranked_result.insert(std::pair<double,std::set<size_t> >
							(b[i],index) );
		}
		else{
			index = ranked_result.find(b[i])->second;
			index.insert(i);
			ranked_result.erase(b[i]);
			//std::cout<<index.size()<<" ";
			ranked_result.insert(std::pair<double,std::set<size_t> >
							(b[i],index) );
		}
		
	}

	std::map<double,std::set<size_t> >::reverse_iterator at;
	//print out in reverse order since biggest first
    for(at=ranked_result.rbegin();at!=ranked_result.rend();++at){
    	if(at->second.size()==1){
    		output<<webpage_vec[*(at->second.begin())].getname()
    			<<" "<<std::endl;
  			}
    	else{
    		std::set<size_t>::iterator et;
    		for(et = at->second.begin();et!=at->second.end();++et){
    			output<<webpage_vec[*et].getname()
    					<<" "<<std::endl;
    		}
    	}
    }
    for(size_t i=0;i<size;i++){
    	delete[] matrixA[i];
    }
    delete[] matrixA;
    
}