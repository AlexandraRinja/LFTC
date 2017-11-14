#include "Automaton.h"
unordered_set<string> Automaton::split(string line,char d){
    unordered_set<string> ans;
    line+=d;
    string aux="";
    for(int i=0;i<line.size();i++){
        if(line[i]==d){
            ans.insert(aux);
            aux="";
            continue;
        }
        aux+=line[i];
    }
    return ans;
}
vector<string> Automaton::splitVector(string line,char d){
    vector<string> ans;
    line+=d;
    string aux="";
    for(int i=0;i<line.size();i++){
        if(line[i]==d){
            ans.push_back(aux);
            aux="";
            continue;
        }
        aux+=line[i];
    }
    return ans;
}
unordered_set<char> Automaton::splitCh(string line,char d){
    unordered_set<char> ans;
    line+=d;
    string aux="";
    for(int i=0;i<line.size();i++){
        if(line[i]==d){
            ans.insert(aux[0]);
            aux="";
            continue;
        }
        aux+=line[i];
    }
    return ans;
}
Automaton::Automaton(string filename){
    visited.clear();
    this->filename=filename;
    ifstream fin(filename);
    string line;
    fin>>line;
    this->alphabet=split(line,',');

    fin>>line;
    this->initialState=line[0]; //iau numai primu caracter

    fin>>line;
    this->finalStates=splitCh(line,',');

    while(!fin.eof()){
        fin>>line;
        //cout<<line<<"\n";
        vector<string> aux1=splitVector(line,'-');
        char currentState=aux1[0][0];
        aux1=splitVector(aux1[1],',');
        string chAlphabet=aux1[0];
        char resultState=aux1[1][0];
        if(possiblePair.find(currentState)==possiblePair.end()){
            unordered_set<string> availabeCh;
            possiblePair.insert(make_pair(currentState,availabeCh));
        }
        possiblePair[currentState].insert(chAlphabet); //ai statetul current si stice charactere poti aplica pe el
        stateCh.insert(make_pair(make_pair(currentState,chAlphabet),resultState));
    }
}
vector<char> Automaton::getAllStates(){
    vector<char> ans;
    for(auto pairr:possiblePair){
        ans.push_back(pairr.first);
    }
    return ans;
}
bool Automaton::isEqual(string s,string t){
    for(int i=0;i<t.size();i++){
        if(s[i]!=t[i]){
            return false;
        }
    }
    return true;
}
string Automaton::removeFirst(string s,int k){
    string ans="";
    for(int i=k;i<s.size();i++){
        ans+=s[i];
    }
    return ans;
}
int Automaton::longestValidPrefix(string s,char currentState){
    //cout<<"String:"<<s<<" CurrentState:"<<currentState<<" ";
    if(s.size()==0 && finalStates.find(currentState)!=finalStates.end()){
      //  cout<<"SE POATE \n";
        return 0;
    }
    if(s.size()==0 && finalStates.find(currentState)==finalStates.end()){
       // cout<<"NU SE POATE\n";
        return -inf;
    }
    int maxx=0;
    for(int i=0;i<s.size();i++){
        unordered_set<string> possibleCh=possiblePair[currentState];
        for(auto key:possibleCh){
            //cout<<s<<" "<<key<<" "<<isEqual(s,key)<<"\n";
            if(isEqual(s,key)){
                string aux=removeFirst(s,key.size());
                pair<char,string> currentPair=make_pair(currentState,key);
                char resultState=stateCh[currentPair];
                //cout<<" Key:"<<key<<" ResultState:"<<resultState<<"\n";
                if(visited.find(make_pair(resultState,aux))==visited.end()){
                    int auxKey=key.size();
                    maxx=max(maxx,auxKey+longestValidPrefix(aux,resultState));
                    visited.insert(make_pair(resultState,aux));
                }
                else{
                    continue;
                }
            }
        }
    }
    return maxx;
}

