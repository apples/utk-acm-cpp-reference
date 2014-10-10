#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
using namespace std;

template <typename T>
struct Board {
    int width;
    vector<T> data;

    void resize(int w) {
        width = w;
        data.clear();
        data.resize(w*w, 0);
    }

    T& at(int row, int col) {
        return data[row*width+col];
    }
};

int main() {
    int N;
    string str;
    Board<int> board;
    Board<int_least64_t> paths;
    ifstream in ("pascal.in");

    while ((in >> N) && N != -1) {
        board.resize(N);
        paths.resize(N);
        paths.at(0,0) = 1;

        // Read in board.
        for (int row=0; row<N; ++row) {
            in >> str;
            for (int col=0; col<N; ++col) {
                board.at(row,col) = (str[col]-'0');
            }
        }

        // Algorithm
        for (int row=0; row<N; ++row) {
            for (int col=0; col<N; ++col) {
                // Check previous rows.
                for (int r=1; r<=row; ++r) {
                    if (board.at(row-r,col) == r) {
                        paths.at(row,col) += paths.at(row-r,col);
                    }
                }
                // Check previous cols.
                for (int c=1; c<=col; ++c) {
                    if (board.at(row,col-c) == c) {
                        paths.at(row,col) += paths.at(row,col-c);
                    }
                }
            }
        }

        cout << paths.at(N-1,N-1) << endl;
    }
}
