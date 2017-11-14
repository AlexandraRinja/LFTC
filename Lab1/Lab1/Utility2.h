#include<bits/stdc++.h>
#include"Automaton.h"
using namespace std;
class Utility2{
private:
    string removeFirst(string s,int k);
    bool isConstInteger(string s);
    bool isConstReal(string s);
    bool isConstChar(string s);
    bool isConstString(string s);

    bool isSeparators(string s);
    bool isOther(string s);
    bool isConst(string s);
    bool isIdentifier(string s);

    bool isLowerCaseLetter(char s);
    bool isUpperCaseLetter(char s);
    bool isLetter(char s);
    bool isDigit(char s);

    void addIdentifier(string s);
    void addConst(string s);
    vector<string> split(string s, char d);

public:
    bool isConstInteger2(string s);
    bool isConstReal2(string s);
    bool isConstChar2(string s);
    bool isConstString2(string s);

    bool isConst2(string s);
    bool isIdentifier2(string s);

    unordered_map<string,int> other;
    unordered_map<string,int> separators;
    vector<pair<int,int>> PIF;
    map<string,vector<int>> symbolTableIdentifier; //perechi de forma identificator indice din PIF, sortate lexicografic
                                                  //pentru cazul in care ai int A.....int A; (e acelasi A si deci trebuie modificat in mai mult locuri)
    map<string,vector<int>> symbolTableConstant;  //perechi de forma constanta indice din PIF, sortate lexicografic

    Utility2(){};
    bool isToken(string s);
    bool isToken2(string s);
    void print(string filename);
    void printError(string filename,int index);
};

