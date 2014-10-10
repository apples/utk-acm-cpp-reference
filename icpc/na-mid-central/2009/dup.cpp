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
}
