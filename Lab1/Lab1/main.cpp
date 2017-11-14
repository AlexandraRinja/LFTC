#include <iostream>
#include"Utility2.h"
using namespace std;
Utility2* utility;
vector<string> split(string s, char d){
    vector<string> ans;
    s+=d;
    string aux="";
    for(int i=0;i<s.size();i++){
        if(s[i]==d){
            ans.push_back(aux);
            aux="";
            continue;
        }
        aux+=s[i];
    }
    return ans;
}
void readFromFiles(string filename,unordered_map<string,int>& mapp){
    ifstream fin(filename);
    while(!fin.eof()){
        string line;
        getline(fin,line);
        if(line.size()!=0){
            vector<string> words=split(line,' ');
            int code;
            istringstream(words[1])>>code;
            mapp.insert(make_pair(words[0],code));
        }
    }
}
bool isValid(string line,unordered_map<string,int>& separators){
    for(auto pairr:separators){
        char separator=pairr.first[0];
        vector<string> tokens=split(line,separator);
        if(tokens[0]==line){
            continue;
        }
        for(int i=0;i<tokens.size();i++){
            bool ok=utility->isToken(tokens[i]);
            if(ok==false){
                return ok || isValid(tokens[i],separators);
            }
        }
        return true;
        cout<<"\n";
    }
    return false;
}
int main()
{
    utility=new Utility2();

    unordered_map<string,int> separators;
    readFromFiles("separators.txt",separators);
    utility->separators=separators;

    unordered_map<string,int> other;
    readFromFiles("other.txt",other);
    utility->other=other;

    int lineIndex=0;
    ifstream fin("test.in");
    while(!fin.eof()){
        lineIndex++;
        string line;
        getline(fin,line);
        if(line.size()!=0){
            vector<string> tokens=split(line,' ');
            for(int i=0;i<tokens.size();i++){
                bool flag=utility->isToken(tokens[i]);
                if(flag==false){
                    if(!isValid(tokens[i],separators)){
                        utility->printError("log.txt",lineIndex);
                        return 0;
                    }
                }
            }
        }
    }
    utility->print("log.txt");
}
