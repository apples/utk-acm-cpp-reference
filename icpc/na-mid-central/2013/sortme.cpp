#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Global comparison order. Represents the new alphabet.
vector<unsigned> char_values (26, 0);

// Compare two characters using the new alphabet.
bool g_char_comp(char a, char b)
{
    return (char_values[a-'A'] < char_values[b-'A']);
}

// Compare two strings using the new alphabet.
bool g_comp(const string& a, const string& b)
{
    // `lexicographical_compare` is what most containers use for `operator<`.
    return lexicographical_compare(
          a.begin(), a.end()
        , b.begin(), b.end()
        , g_char_comp
    );
}

// Builds the comparison values for g_char_comp to use.
void build_values(const string& str)
{
    for (unsigned i=0, ie=str.size(); i!=ie; ++i)
    {
        char_values[str[i]-'A'] = i;
    }
}

int main()
{
    ifstream in ("sortme.in");
    
    int numWords; // Number of words in the list.
    int year = 0; // Current iteration.
    
    string alphabet (26, '?'); // Alphabet has 26 characters.
    
    // There will be no more than 20 words with a maximum length of 30.
    vector<string> words(20, string(30, '?'));
    
    while (in >>numWords, numWords != 0)
    {
        ++year;
        
        // Read in and convert the alphabet.
        in >>alphabet;
        build_values(alphabet);
        
        // Read in the words.
        for (int i=0; i<numWords; ++i)
        {
            in >>words[i];
        }
        
        // Sort using our custom comparator.
        sort(words.begin(), words.begin()+numWords, g_comp);
        
        cout <<"year " <<year <<endl;
        
        for (int i=0; i<numWords; ++i)
        {
            cout <<words[i] <<endl;
        }
    }
}
