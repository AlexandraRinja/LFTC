#include<iostream>
#include<fstream>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<vector>
//presupun ca toate starile o sa fie simple caractere
using namespace std;
class Automaton{
private:
    int inf=-1e6;
    set<pair<char,string>> visited;
    int id;
    string filename;
    unordered_map<char,unordered_set<string>> possiblePair; //toate elementele din alfabet ce pot fi folosite pentru cheia data
    char initialState; //initial state, e doar una deci tin o simpla varibila
    unordered_set<char> finalStates;
    unordered_set<string> alphabet;
    map<pair<char,string>,char> stateCh;

    unordered_set<string> split(string line,char d);
    unordered_set<char> splitCh(string line,char d);
    vector<string> splitVector(string line,char d);
    bool isEqual(string s,string t);
    string removeFirst(string s,int k);

public:
    Automaton(string filename);
    vector<char> getAllStates();
    int longestValidPrefix(string s,char currentState);
};

