#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Exception object thrown when a character cannot be reversed.
struct Invalid_Word {};

// Mirrors a character. Throws Invalid_Word upon failure.
char mirror(char c)
{
    switch (c)
    {
        // 'b' :=: 'd'
        case 'b': return 'd';
        case 'd': return 'b';
        
        // 'p' :=: 'q'
        case 'p': return 'q';
        case 'q': return 'p';
        
        // "iovwx" are mirrors of themselves.
        case 'i': case 'o': case 'v': case 'w': case 'x': return c;
        
        // Cannot be mirrored.
        default: throw Invalid_Word();
    }
}

int main()
{
    ifstream in ("mirror.in");
    
    string word;
    
    while (in >>word, word != "#") try
    {
        // Mirror each character.
        transform(word.begin(), word.end(), word.begin(), mirror);
        
        // Reverse the whole word.
        reverse(word.begin(), word.end());
        
        cout <<word <<endl;
    }
    catch (const Invalid_Word&)
    {
        cout <<"INVALID" <<endl;
    }
}
