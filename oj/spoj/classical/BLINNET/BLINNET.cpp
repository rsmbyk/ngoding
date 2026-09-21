#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

int network[10001];
int findNetwork (int i) { return network[i] == i ? i : network[i] = findNetwork (network[i]); }
bool sameNetwork (int a, int b) { return findNetwork (a) == findNetwork (b); }
void unionNetwork (int a, int b) { network[findNetwork (a)] = findNetwork (b); }

int main (int args, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, p;
        cin >> n;
    
        string cityname;
        priority_queue<pair<int, pair<int, int> > > costs;
        
        for (int i = 1; i <= n; i++) {
            cin >> cityname >> p;
            network[i] = i;
            int neigh, cost;
            
            while (p--) {
                cin >> neigh >> cost;
                costs.push (make_pair (-cost, make_pair (i, neigh)));
            }
        }
        
        int connections = 0;
        int networkCost = 0;
        while (connections < n-1) {
            pair<int, pair<int, int> > connect;
            connect = costs.top ();
            costs.pop ();
            
            if (!sameNetwork (connect.second.first, connect.second.second)) {
                unionNetwork (connect.second.first, connect.second.second);
                networkCost += (-connect.first);
                connections++;
            }
        }
        
        cout << networkCost << endl;
    }
}