#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    ifstream in ("mad.in");
    
    int k, n;
    vector<int> sequence;
    
    sequence.reserve(26);
    
    while (in >>k, k != 0)
    {
        sequence.resize(k);
        
        for (int i=0; i<k; ++i)
        {
            in >>n;
            sequence[i] = n;
        }
        
        adjacent_difference(sequence.begin(), sequence.end(), sequence.begin());
        
        bool first = true;
        
        for (unsigned i=0, ie=sequence.size(); i!=ie; ++i)
        {
            for (int j=0, je=sequence[i]; j!=je; ++j)
            {
                if (!first) cout <<' ';
                cout <<(i+1);
                first = false;
            }
        }
        cout <<endl;
    }
}
