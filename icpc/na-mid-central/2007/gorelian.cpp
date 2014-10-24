#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;

static const int oo = numeric_limits<int>::max();
static const int block_len = 2520;

enum Cardinal {
    NORTH,
    SOUTH,
    WEST,
    EAST
};

struct Intersection;

struct Road {
    Intersection* next;
    int time_cost;

    Road() : next(NULL) {}
};

struct Intersection {
    int min_time;
    Road roads[4];

    Intersection() : min_time(oo) {}
};

struct City {
    int width;
    vector<Intersection> intersections;

    City() : width(0) { intersections.reserve(21*21); }

    Intersection& at(int r, int c) {
        return intersections[r*width+c];
    }

    void resize(int r, int c) {
        width = c;
        intersections.clear();
        intersections.resize(r*c);
    }
};

struct QItem {
    Intersection* ptr;

    QItem(Intersection* ptr) : ptr(ptr) {}

    Intersection& get() const { return *ptr; }

    bool operator<(QItem const& other) const {
        return greater<int>()(get().min_time, other.get().min_time);
    }

    bool operator==(QItem const& other) const {
        return (ptr == other.ptr);
    }
};

template <typename T>
struct VecSet {
    typedef vector<T> Vec;
    typedef typename Vec::iterator Iter;

    Vec vec;

    void erase(T const& t) {
        Iter iter = lower_bound(vec.begin(),vec.end(),t);
        if (iter != vec.end() && *iter == t) {
            vec.erase(iter);
        }
    }

    void push(T const& t) {
        vec.insert(lower_bound(vec.begin(),vec.end(),t),t);
    }

    T const& top() { return vec.back(); }
    void pop() { vec.pop_back(); }
    void clear() { vec.clear(); }
    bool empty() { return vec.empty(); }

    bool dijkstra(City& city, int r, int c) {
        clear();

        city.at(0,0).min_time = 0;
        push(QItem(&city.at(0,0)));

        while (!empty()) {
            QItem qi = top();
            pop();

            if (qi == QItem(&city.at(r,c))) {
                return true;
            }

            for (int i=0; i<4; ++i) {
                Road& road = qi.get().roads[i];
                if (road.next) {
                    QItem next = QItem(road.next);
                    int t = qi.get().min_time + road.time_cost;
                    if (t < next.get().min_time) {
                        erase(next);
                        next.get().min_time = t;
                        push(next);
                    }
                }
            }
        }

        return false;
    }
};

int main() {
    City city;
    int r;
    int c;
    int spd;
    string str;
    VecSet<QItem> Q;

    while ((cin >> r >> c) && (r > 0 && c > 0)) {
        city.resize(r+1,c+1);

        for (int i=0; i<r+1; ++i) {
            for (int j=0; j<c; ++j) {
                cin >> spd >> str;
                if (spd > 0) {
                    if (str == "*" || str == ">") {
                        city.at(i,j).roads[EAST].next = &city.at(i,j+1);
                        city.at(i,j).roads[EAST].time_cost = block_len/spd;
                    }
                    if (str == "*" || str == "<") {
                        city.at(i,j+1).roads[WEST].next = &city.at(i,j);
                        city.at(i,j+1).roads[WEST].time_cost = block_len/spd;
                    }
                }
            }
            if (i != r) {
                for (int j=0; j<c+1; ++j) {
                    cin >> spd >> str;
                    if (spd > 0) {
                        if (str == "*" || str == "v") {
                            city.at(i,j).roads[SOUTH].next = &city.at(i+1,j);
                            city.at(i,j).roads[SOUTH].time_cost = block_len/spd;
                        }
                        if (str == "*" || str == "^") {
                            city.at(i+1,j).roads[NORTH].next = &city.at(i,j);
                            city.at(i+1,j).roads[NORTH].time_cost = block_len/spd;
                        }
                    }
                }
            }
        }

        if (Q.dijkstra(city,r,c)) {
            cout << city.at(r,c).min_time << " blips" << endl;
        } else {
            cout << "Holiday" << endl;
        }
    }
}
