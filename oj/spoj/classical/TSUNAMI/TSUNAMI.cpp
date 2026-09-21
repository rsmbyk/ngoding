#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int parents[1001];
void initSet (int n) { for (int i = 0; i < n; i++) parents[i] = i; }
int findSet (int i) { return parents[i] == i ? i : parents[i] = findSet (parents[i]); }
bool sameSet (int a, int b) { return findSet (a) == findSet (b); }
void unionSet (int a, int b) { parents[findSet (a)] = findSet (b); }

typedef struct city {
    int x, y;
    
    bool operator < (const struct city &other) const {
        if (y == other.y)
            return x < other.x;
        return y < other.y;
    }
} City;

typedef struct edge {
    double length;
    int a, b;
    
    bool operator < (const struct edge &other) const {
        return length > other.length;
    }
} Edge;

double dist (const struct city &a, const struct city &b) {
    return sqrt (pow (abs (a.x - b.x), 2) + pow (abs (a.y - b.y), 2));
}

City make_city () {
    City c;
    scanf ("%d %d", &c.x, &c.y);
    return c;
}

int main (int argc, char **argv) {
    int n;
    
    while (scanf ("%d", &n)) {
        if (n == 0) break;
    
        priority_queue<Edge> edges;
        vector<City> cities;
    
        for (int i = 0; i < n; i++) cities.push_back (make_city ());
        sort (cities.begin (), cities.end ());
        
        double cable = 0.0;
        initSet (n);
        int set = 0;
    
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                Edge e;
                e.length = dist (cities[i], cities[j]);
                e.a = j;
                e.b = i;
                edges.push (e);
            }
    
            if (cities[i].y < cities[i+1].y || i == n-1) 
                while (!edges.empty () && set < i) {
                    if (!sameSet (edges.top ().a, edges.top ().b)) {
                        unionSet (edges.top ().a, edges.top ().b);
                        cable += edges.top ().length;
                        set++;
                    }
                    
                    edges.pop ();
                }
        }
    
    
        
    
        printf ("%.2lf\n", cable);
    }
}