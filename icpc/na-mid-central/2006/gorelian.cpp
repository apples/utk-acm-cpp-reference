#include <cstddef>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Planet
{
    int id;
    
    int x;
    int y;
    int z;
    
    vector<Planet*> warps;
};

int get_dist(const Planet& p1, const Planet& p2)
{
    int dx = p1.x-p2.x;
    int dy = p1.y-p2.y;
    int dz = p1.z-p2.z;
    
    return (dx*dx + dy*dy + dz*dz);
}

template <typename Iter>
Planet* find_closest(Iter b, Iter e, const Planet& p)
{
    if (b == e) return NULL;
    
    Planet* rv = &*b;
    int dist = get_dist(p, *b);
    
    ++b;
    
    for (; b!=e; ++b)
    {
        int d = get_dist(p, *b);
        
        if (d < dist)
        {
            rv = &*b;
            dist = d;
        }
    }
    
    return rv;
}

int calculate_score(const Planet& p, const Planet* prev)
{
    typedef vector<Planet*>::const_iterator Iter;
    
    int rv = 0;
    
    for (Iter i=p.warps.begin(), ie=p.warps.end(); i!=ie; ++i)
    if (*i != prev)
    {
        int s = calculate_score(**i, &p);
        if (s > rv) rv = s;
    }
    
    return (rv+1);
}

template <typename Iter>
pair<int,int> find_best(Iter b, Iter e)
{
    pair<int,int> best (b->id, -1);
    int best_score = calculate_score(*(b++), NULL);
    
    for (; b!=e; ++b)
    {
        int s = calculate_score(*b, NULL);
        if (s < best_score)
        {
            best_score = s;
            best.first = b->id;
            best.second = -1;
        }
        else if (s == best_score)
        {
            best.second = b->id;
        }
    }
    
    return best;
}

int main()
{
    ifstream in ("gorelian.in");
    
    deque<Planet> planets;
    
    int N;
    
    while (in >>N, N!=0)
    {
        planets.clear();
        
        for (int i=0; i<N; ++i)
        {
            Planet* warp = NULL;
            
            {
                Planet p;
                in >>p.id >>p.x >>p.y >>p.z;
                
                warp = find_closest(planets.begin(), planets.end(), p);
                
                planets.push_back(p);
            }
            Planet& p = planets.back();
            
            if (warp)
            {
                p.warps.push_back(warp);
                warp->warps.push_back(&p);
            }
        }
        
        pair<int,int> best = find_best(planets.begin(), planets.end());
        
        if (best.second > 0)
        {
            if (best.second < best.first) swap(best.first, best.second);
            cout <<best.first <<" " <<best.second <<endl;
        }
        else
        {
            cout <<best.first <<endl;
        }
    }
}
