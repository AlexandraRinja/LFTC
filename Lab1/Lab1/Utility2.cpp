#include"Utility2.h"
vector<string> Utility2::split(string s, char d){
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
bool Utility2::isLowerCaseLetter(char s){
    return s>='a' && s<='z';
}
bool Utility2::isUpperCaseLetter(char s){
    return s>='A' && s<='Z';
}
bool Utility2::isLetter(char s){
    return isLowerCaseLetter(s) || isUpperCaseLetter(s);
}
bool Utility2::isDigit(char s){
    return s>='0' && s<='9';
}
bool Utility2::isConstString(string s){
    int n=s.size();
    if(n<3){
        return false;
    }
    bool ok=(s[0]=='\"');
    bool ok2=(s[n-1]=='\"');
    bool res=(ok&&ok2);
    if(res==false){
        return false;
    }
    for(int i=1;i<n-1;i++){
        if(isLetter(s[i])==false && isDigit(s[i])==false){
            return false;
        }
    }
    return true;
}
bool Utility2::isConstChar(string s){
    if(s.size()!=3){
        return false;
    }
    return s[0]=='\''&& s[2]=='\'' && (isLetter(s[1]) || isDigit(s[1]));
}
bool Utility2::isConstInteger(string s){
    if(s.size()==0){
        return false;
    }
    if(s.size()==1 && s[0]=='0'){
        return true;
    }
    for(int i=0;i<s.size();i++){
        if(isDigit(s[i])){
            if(i==0 && s[i]=='0' || (i==1 && s[i]=='0' && s[0]=='-')){
                return false;
            }
        }
        else{
            if(i==0 && s[i]=='-'){
                continue;
            }
            return false;
        }
    }
    return true;
}
bool Utility2::isConstReal(string s){
    vector<string> parts=split(s,'.');
    if(parts.size()!=2){
        return false;
    }
    bool realPart=isConstInteger(parts[0]);
    if(realPart==false){
        if(parts[0]=="-0" && parts[1].size()!=0){
            return true;
        }
        return false;
    }
    for(int i=0;i<parts[1].size();i++){
        if(isDigit(parts[1][i])){
            continue;
        }
        return false;
    }
    return true;
}

bool Utility2::isConst(string s){
    return isConstInteger(s) || isConstReal(s) || isConstChar(s) ||isConstString(s);
}

bool Utility2::isIdentifier(string s){
    if(s.size()>8){
        return false;
    }
    bool firstL=isUpperCaseLetter(s[0]);
    if(firstL==false){
        return false;
    }
    bool auxL=true;
    for(int i=1;i<s.size();i++){
        auxL=isLowerCaseLetter(s[i]) || isDigit(s[i]);
        if(auxL==false){
            return false;
        }
    }
    return true;
}
bool Utility2::isSeparators(string s){
    if(separators.find(s)!=separators.end()){
        return true;
    }
    return false;
}
bool Utility2::isOther(string s){
    if(other.find(s)!=other.end()){
        return true;
    }
    return false;
}
void Utility2::addConst(string s){
    int index=PIF.size();
    PIF.push_back(make_pair(1,-1));
    if(symbolTableConstant.find(s)!=symbolTableConstant.end()){
        //mai exista, pun doar pozitia la care e acum
        symbolTableConstant[s].push_back(index);
    }
    else{
        //acum e pentru prima data
        vector<int> aux;
        symbolTableConstant[s]=aux;
        symbolTableConstant[s].push_back(index);
    }
}
void Utility2::addIdentifier(string s){
    int index=PIF.size();
    PIF.push_back(make_pair(0,-1));
    if(symbolTableIdentifier.find(s)!=symbolTableIdentifier.end()){
        //mai exista, pun doar pozitia la care e acum
        symbolTableIdentifier[s].push_back(index);
    }
    else{
        //acum e pentru prima data
        vector<int> aux;
        symbolTableIdentifier[s]=aux;
        symbolTableIdentifier[s].push_back(index);
    }
}
bool Utility2::isToken(string s){
    if(isConst(s)){
        addConst(s);
        return true;
    }
    if(isIdentifier(s)){
        addIdentifier(s);
        return true;
    }
    if(isOther(s)){
        int code=other[s];
        PIF.push_back(make_pair(code,0));
        return true;
    }
    if(isSeparators(s)){
        int code=separators[s];
        PIF.push_back(make_pair(code,0));
        return true;
    }
    return false;
}
void Utility2::print(string filename){
    int index=0;
    ofstream fout(filename);
    fout<<"SYMBOL TABLE IDENTIFIERS\n";
    for(auto pairr:this->symbolTableIdentifier){
        fout<<pairr.first<<" "<<index<<"\n";
        for(auto indexPIF:pairr.second){
            this->PIF[indexPIF].second=index;
        }
        index++;
    }
    index=0;
    fout<<"SYMBOL TABLE CONSTANTS\n";
    for(auto pairr:this->symbolTableConstant){
        fout<<pairr.first<<" "<<index<<"\n";
        for(auto indexPIF:pairr.second){
            this->PIF[indexPIF].second=index;
        }
        index++;
    }
    fout<<"PROGRAM INTERNAL FORM\n";
    for(auto pairr:PIF){
        fout<<pairr.first<<" "<<pairr.second<<"\n";
    }
}
void Utility2::printError(string filename,int line){
    ofstream fout(filename);
    fout<<"ERROR line:"<<line<<"\n";
}
