#include <vector>
#include <cstdio>
#include <algorithm>

#define MOD 1000000007
std::vector<int> numb[10001];
long long hash[10001], memo[10001];

long long hashf (int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

int main (int argc, char const *args[]) {
    for (int i = 1; i <= 10000; i++) memo[i] = hashf (i);
    int tc, n, m, a, b;
    tc = getNumb ();
    
    for (int t = 1; t <= tc; t++) {
        n = getNumb ();
        m = getNumb ();
        for (int i = 1; i <= n; i++) hash[i] = 0;
        for (int i = 0; i < m; i++) {
            a = getNumb ();
            b = getNumb ();
            numb[a].push_back (b);
            numb[b].push_back (a);
            hash[a] = hash[a] + memo[b];
            hash[b] = hash[b] + memo[a];
        }
        
        bool valid = false;
        for (int i = 1; i <= n && !valid; i++) {
            std::sort (numb[i].begin (), numb[i].end ());
            for (int u = 0; u < numb[i].size (); u++) {
                int j = numb[i][u];
                long long a2, b2;
                a2 = hash[i];
                b2 = hash[j];
                a2 = a2 - memo[j];
                b2 = b2 - memo[i];
                
                if (a2 == b2) {
                    printf ("Case #%d: %d %d\n", t, i, j);
                    valid = true;
                    break;
                }
            }
        }
        
        if (!valid) printf ("Case #%d: No twins\n", t);
        for (int i = 0; i <= 10001; i++) numb[i].clear ();
    }
}