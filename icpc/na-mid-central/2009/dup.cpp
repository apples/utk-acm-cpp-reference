// Duplicate Removal
// http://mcicpc.cs.atu.edu/archives/2009/mcpc2009/dup/dup.html

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    int N;
    vector<int> vec;
    ifstream in ("dup.in");

    while ((in >> N) && N != 0) {
        vec.resize(N);
        for (int i=0; i<N; ++i) {
            in >> vec[i];
        }

        vec.erase(unique(vec.begin(),vec.end()),vec.end());

        for (int i=0, ie=vec.size(); i<ie; ++i) {
            cout << vec[i] << " ";
        }
        cout << "$" << endl;
    }

    // This is another solution that uses O(1) space.
#if 0
    int last;
    int current;
    while ((in >> N) && N != 0) {
        last = 0;
        for (int i=0; i<N; ++i) {
            in >> current;
            if (current != last) {
                cout << current << " ";
            }
            last = current;
        }
        cout << "$" << endl;
    }
#endif
}
