#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int fixed_r;
int fixed_c;

vector<int> brd(8);
vector< vector<int> > solutions;
vector< vector<int>* > answers;

bool is_valid(int c)
{
    int r = brd[c];
    
    for (int i=0; i<c; ++i)
    {
        if (brd[i]==r ||
            brd[i]==r-(c-i) ||
            brd[i]==r+(c-i)
        ) return false;
    }
    
    return true;
}

void make_solutions(int c)
{
    if (c==8) return solutions.push_back(brd);
    
    for (int r=0; r<8; ++r)
    {
        brd[c] = r;
        if (is_valid(c)) make_solutions(c+1);
    }
    
    return;
}

void find_answers()
{
    answers.clear();
    
    for (int i=0, ie=solutions.size(); i<ie; ++i)
    {
        if (solutions[i][fixed_c] == fixed_r)
        {
            answers.push_back(&solutions[i]);
        }
    }
}

void print_answers()
{
    cout << "SOLN       COLUMN" << endl;
    cout << " #      1 2 3 4 5 6 7 8" << endl;
    cout << endl;
    
    for (int i=0, ie=answers.size(); i<ie; ++i)
    {
        cout << setw(2) << (i+1) << "      ";
        for (int j=0; j<8; ++j)
        {
            if (j>0) cout << " ";
            cout << ((*answers[i])[j]+1);
        }
        cout << endl;
    }
}

int main()
{
    ifstream in ("queens.in");
    
    int N;
    in >> N;
    
    solutions.reserve(92);
    make_solutions(0);
    sort(solutions.begin(), solutions.end());
    
    for (int i=0; i<N; ++i)
    {
        in >> fixed_r >> fixed_c;
        --fixed_r;
        --fixed_c;
        
        find_answers();
        
        print_answers();
        if (i!=N-1) cout << endl;
    }
}

