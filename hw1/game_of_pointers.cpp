#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
              int rows, int columns, int &reserves, ofstream &output){

    if(skirmish_row>=columns || skirmish_row<0) //out of bounds
        return false;

    for(int i=0;i<rows;i++){
        //protectors[i][skirmish_row];
        //invaders[skirmish_row][i];
        if(protectors[i][skirmish_row]==NULL && invaders[skirmish_row][i]!=NULL) 
            //no protector
            return true;
        else if(protectors[i][skirmish_row]!=NULL && 
                invaders[skirmish_row][i]!=NULL){
            //both present
            
            int axecount=0;
            if(protectors[i][skirmish_row]->weapon=="axe")
                axecount++;
            if(invaders[skirmish_row][i]->weapon=="axe")
                axecount++;

            if(axecount == 1){// 1 axe
                if(invaders[skirmish_row][i]->weapon=="axe"){//invader wins
                    bool flag= false;
                    
                    for(int j=0;j<columns;j++){//search for space in invader army
                        for(int k=0;k<rows;k++){
                            if(invaders[j][k]==NULL){
                                flag = true;
                                invaders[j][k]=protectors[i][skirmish_row];
                                //delete protectors[i][skirmish_row];
                                protectors[i][skirmish_row]=NULL;
                                output<<"Protector defected\n";
                                break;
                            }
                        }
                        if(flag==true) break;
                    }
                    if(flag == false){//no space
                        output<<"Protector killed\n";
                        delete protectors[i][skirmish_row];
                        protectors[i][skirmish_row]=NULL;
                    }
                        
                    if(reserves>0){//fill in reserves
                        reserves--;
                        Warrior* temp = new Warrior();
                        temp->weapon = "axe";
                        temp->power = 100;
                        protectors[i][skirmish_row] = temp;
                        //delete temp;
                    }

                }
                
                else{//protector wins
                    delete invaders[skirmish_row][i];
                    invaders[skirmish_row][i] = NULL;
                    output<<"Invader killed\n";
                }
            }
            else{//2 axes or 2 swords
                if(protectors[i][skirmish_row]->power > 
                    invaders[skirmish_row][i]->power){
                    //protector wins
                    delete invaders[skirmish_row][i];
                    invaders[skirmish_row][i]=NULL;
                    output<<"Invader killed\n";
                }
                else if(protectors[i][skirmish_row]->power < 
                        invaders[skirmish_row][i]->power){
                    //invader wins
                    bool flag= false;
                    
                    for(int j=0;j<columns;j++){//search for space in invader army
                        for(int k=0;k<rows;k++){
                            if(invaders[j][k]==NULL){
                                flag = true;
                                invaders[j][k]=protectors[i][skirmish_row];
                                //delete protectors[i][skirmish_row];
                                protectors[i][skirmish_row]=NULL;
                                output<<"Protector defected\n";
                                break;
                            }
                        }
                        if(flag == true) break;
                    }
                    if(flag == false){//no space
                        output<<"Protector killed\n";
                        delete protectors[i][skirmish_row];
                        protectors[i][skirmish_row]=NULL;
                    }
                        
                    if(reserves>0){//fill in reserves
                        reserves--;
                        Warrior* temp = new Warrior();
                        temp->weapon = "axe";
                        temp->power = 100;
                        protectors[i][skirmish_row] = temp;
                        //delete temp;
                    }
                }
                else{//draw
                    output<<"Duel ends in draw\n";
                }
            }
        }
        else{
            output<<"No assault\n";
        }

        
    }
    //returns true if the invaders breach the walls.
    return false;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
       cerr << "Please provide an input and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.
    input>>rows>>cols>>reserve>>skirmishes;
    Warrior ***protectors;
    Warrior ***invaders;

    //initialize the protectors and invaders here.
    
    protectors = new Warrior ** [rows];
    for(int i=0;i<rows;i++)
        protectors[i]= new Warrior* [cols];
    
    for(int i=0;i<rows;i++){
        
        for(int j=0;j<cols;j++){
            protectors[i][j]=new Warrior();
        }//dynamically allocating protectors
    }


    invaders = new Warrior ** [cols];
    for(int i=0;i<cols;i++)
        invaders[i] = new Warrior* [rows];
    
    for(int i=0;i<cols;i++){
        
        for(int j=0;j<rows;j++){
            invaders[i][j]=new Warrior();
        }//dynamically allocating invaders
    }

    for(int i=0;i<rows;i++){//Initializing Protector Army
        for(int j=0;j<cols;j++){
            if(i==0 || i%2==0)
                protectors[i][j]->weapon="axe";
            else protectors[i][j]->weapon="sword";
            protectors[i][j]->power=i*10+(j+1)*10;
            //cout<<protectors[i][j]->power<<" "<<protectors[i][j]->weapon<<" ";
        }
        //cout<<endl;
    }

    for(int i=0;i<cols;i++){//Initializing Invader Army
        for(int j=0;j<rows;j++){
            if(i%2==1)
                invaders[i][j]->weapon="axe";
            else invaders[i][j]->weapon="sword";
            invaders[i][j]->power=i*10+(j+1)*10;
            //cout<<invaders[i][j]->power<<" "<<invaders[i][j]->weapon<<" ";
        }
        //cout<<endl;
    }

    bool end;
    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
        
        //read the input file to find the value for skirmish row
        input>>skirmish_row;
        //In general, it is bad style to throw everything into your main function
        end = skirmish(protectors, invaders, skirmish_row, rows, 
                        cols, reserve, output);
        if (end ==true){
            break;
        }
    }

    //output the winner and deallocate your memory.
    if(end==true) output<<"Winner: invaders\n";
    else output<<"Winner: protectors\n";

    for(int i=0;i<rows;i++){
        
        for(int j=0;j<cols;j++)
            delete protectors[i][j];
    }
    for(int i=0;i<rows;i++)
        delete[] protectors[i];

    for(int i=0;i<cols;i++){
        
        for(int j=0;j<rows;j++)
            delete invaders[i][j];
    }
    for(int i=0;i<cols;i++)
        delete[] invaders[i];

    delete[] protectors;
    delete[] invaders;
    input.close();
    output.close();
    //cout<<rows<<cols<<reserve<<skirmishes;
    
    return 0;
}