#include <cstdio>
#include <utility>
#include <vector>
#include <map>

typedef unsigned long long ll;
using namespace std;

int main (int argc, char **argv) {
    ll tc, n, M, p, m;
    scanf ("%llu", &tc);
    
    while (tc--) {
        scanf ("%llu %llu", &n, &M);
        map<ll, ll>  robots;
        
        for (int i = 0; i < n; i++) {
            scanf ("%llu %llu", &p, &m);
            robots[p] += m;
        }
        
        ll upgrade, invest, last;
        map<ll, ll>::iterator i = robots.begin ();
        upgrade = i->second;
        last = i->first;
        invest = 0;
        
        while (++i != robots.end ()) {
            if (invest + (upgrade * (i->first - last)) <= M) {
                invest += upgrade * (i->first - last);
                upgrade += i->second;
                last = i->first;
            }
            else break;
        }
    
        last += (M - invest) / (upgrade);
        printf ("%llu\n", last);
    }
    
    return 0;
}