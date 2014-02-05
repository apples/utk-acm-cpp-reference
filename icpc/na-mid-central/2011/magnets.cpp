#include <fstream>
#include <iostream>
#include <set>

using namespace std;

// Determines if a string contains no duplicate letters.
bool is_valid(const string& str)
{
    // A set might not be the fastest way of solving this, but it's the easiest.
    set<char> letters;
    
    for (unsigned i=0, ie=str.size(); i!=ie; ++i)
    {
        if (str[i]!=' ')
        {
            if (!letters.insert(str[i]).second) return false;
        }
    }
    
    return true;
}

int main()
{
    ifstream in ("magnets.in");
    
    string line;
    
    while (getline(in, line) && line != "END")
    {
        if (is_valid(line)) cout <<line <<endl;
    }
}
