#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

struct Chamber;

struct Passage {
    Chamber* to;
};

struct Chamber {
    vector<Passage*> exits;
    int value;
    bool visited;

    Chamber() : visited(false) {}
};

struct Map {
    vector<Chamber> chambers;
    vector<Passage> passages;
};

bool DFS(Chamber* from, Chamber* to, vector<Chamber*>& path) {
    if (from->visited) {
        return false;
    }
    if (from == to) {
        path.push_back(from);
        return true;
    }
    from->visited = true;
    for (int i=0; i<from->exits.size(); ++i) {
        if (DFS(from->exits[i]->to, to, path)) {
            path.push_back(from);
            return true;
        }
    }

    return false;
}

int main() {
    int T;
    int N;
    int P;

    Map map;

    cin >> T;

    for (int _=0; _<T; ++_) {
        cin >> N >> P;
        map.chambers.clear();
        map.chambers.resize(N);
        map.passages.clear();
        map.passages.resize(P*2);

        for (int i=0; i<N; ++i) {
            cin >> map.chambers[i].value;
        }

        for (int i=0; i<P; ++i) {
            int a;
            int b;
            bool a2b;
            bool b2a;

            cin >> a >> b >> a2b >> b2a;
            --a;
            --b;

            if (a2b) {
                Passage& pass = map.passages[i*2];
                map.chambers[a].exits.push_back(&pass);
                pass.to = &map.chambers[b];
            }

            if (b2a) {
                Passage& pass = map.passages[i*2+1];
                map.chambers[b].exits.push_back(&pass);
                pass.to = &map.chambers[a];
            }
        }

        int s;
        int t;

        cin >> s >> t;
        --s;
        --t;

        vector<Chamber*> path;
        DFS(&map.chambers[s], &map.chambers[t], path);

        for (int i=path.size(); i!=0; --i) {
            cout << path[i-1]->value;
            if (i != 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}
