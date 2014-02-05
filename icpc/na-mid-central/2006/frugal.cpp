#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool is_match(const string& word, const string& query)
{
    bool unsgn = false;
    
    for (string::const_iterator i=query.begin(), ie=query.end(); i!=ie; ++i)
    {
        switch (*i)
        {
            case '+':
                ++i;
                if (word.find(*i) == string::npos) return false;
                break;
            
            case '-':
                ++i;
                if (word.find(*i) != string::npos) return false;
                break;
            
            default:
                if (word.find(*i) != string::npos) unsgn = true;
                break;
        }
    }
    
    return unsgn;
}

bool str_ptr_comp(string* const s1, string* const s2)
{
    return (*s1 < *s2);
}

void add_word(vector<string>& words, string& word)
{
    words.push_back(word);
}

void get_word(vector<string>& words, string& query)
{
    typedef vector<string>::iterator VSIter;
    vector<string*> results;
    vector<string> terms;
    
    while (!query.empty())
    {
        string::size_type loc = query.find_last_of('|');
        
        if (loc == string::npos)
        {
            terms.push_back(query);
            query.clear();
        }
        else
        {
            terms.push_back(string(query.begin()+loc+1, query.end()));
            query.erase(query.begin()+loc, query.end());
        }
    }
    
    for (VSIter i=words.begin(), ie=words.end(); i!=ie; ++i)
    {
        for (VSIter j=terms.begin(), je=terms.end(); j!=je; ++j)
        {
            if (is_match(*i, *j))
            {
                results.push_back(&*i);
                break;
            }
        }
    }
    
    if (results.empty())
    {
        cout <<"NONE" <<endl;
    }
    else
    {
        string& s = **min_element(results.begin(), results.end(), str_ptr_comp);
        cout <<s <<endl;
    }
}

typedef void (*Mode)(vector<string>&, string&);

int main()
{
    ifstream in ("frugal.in");
    
    vector<string> words;
    words.reserve(100);
    
    Mode mode = add_word;
    
    string line;
    
    while (getline(in, line) && line!="#")
    {
        if (line == "**")
        {
            cout <<"$" <<endl;
            words.clear();
            mode = add_word;
        }
        else if (line == "*")
        {
            mode = get_word;
        }
        else
        {
            (*mode)(words, line);
        }
    }
}
