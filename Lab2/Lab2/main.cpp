#include <iostream>
#include "Automaton.h"
using namespace std;

int main()
{
    Automaton* aut=new Automaton("in.txt");
    cout<<aut->longestValidPrefix("89ll",'S');
}
