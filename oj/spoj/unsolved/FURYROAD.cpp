#include <cstdio>
#include <utility>

int parents[1001];
void initSet (int n) { for (int i = 0; i < n; i++) parents[i] = i; }
int findSet (int i) { return parents[i] == i ? i : parents[i] = findSet (parents[i]); }
bool sameSet (int a, int b) { return findSet (a) == findSet (b); }
void unionSet (int a, int b) { parents[findSet (a)] = findSet (b); }

int main (int argc, char **argv) {
    int tc, n;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n);
        
        std::pair<int, int> pos[n];
        for (int i = 0; i < n; i++)
            scanf ("%d %d", &pos[i].first, &pos[i].second);
        
        for (int i = 0; i <)
    }
}