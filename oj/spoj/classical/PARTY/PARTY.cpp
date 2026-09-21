#include <cstdio>
#include <vector>

using namespace std;

int main (int argc, char **argv) {
    int b, n, cost, fun;
    
    while (scanf ("%d %d", &b, &n)) {
        if (b == 0 && n == 0) break;
        
        vector<pair<int, int> > parties;
        for (int i = 0; i < n; i++) {
            scanf ("%d %d", &cost, &fun);
            parties.push_back (make_pair (cost, fun));
        }
        
        int f[n+1][b+1]={};
        for (int i = 1; i <= n; i++) 
            for (int j = 0; j <= b; j++)
                if (j < parties[(i-1)].first)
                    f[i][j] = f[i-1][j];
                else
                    f[i][j] = max (f[i-1][j], f[i-1][j-parties[(i-1)].first] + parties[(i-1)].second);
        
        int minB = b;
        while (f[n][minB] == f[n][minB-1]) minB--;
        printf ("%d %d\n", minB, f[n][b]);
    }
}