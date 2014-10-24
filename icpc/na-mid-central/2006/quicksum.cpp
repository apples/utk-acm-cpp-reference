#if true // Best solution

#include <iostream>
using namespace std;

int main() {
    int pos = 0;
    int val = 0;
    char c;
    while (cin.get(c) && c != '#') {
        if (c == '\n') {
            cout << val << endl;
            val = 0;
            pos = 0;
        } else {
            ++pos;
            val += ((c == ' ') ? 0 : pos*(c-'A'+1));
        }
    }
}

#else // Cool solution

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

int getval(char c) {
    return (c==' ' ? 0 : c-'A'+1);
}

struct numiter {
    int i;
    numiter(int i) : i(i) {}
    numiter& operator++() {++i; return *this;}
    int operator*() {return i;}
};

int main() {
    string line;
    vector<int> vals;

    while (getline(cin,line) && line != "#") {
        vals.clear();
        transform(line.begin(),line.end(), back_inserter(vals), getval);
        int sum = inner_product(vals.begin(),vals.end(), numiter(1), 0);
        cout << sum << endl;
    }
}

#endif
