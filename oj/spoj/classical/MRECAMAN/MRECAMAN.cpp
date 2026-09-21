#include <map>
#include <set>
#include <cstdio>

int main (int argc, char const *argv[]) {
    int recaman[500005]={0}, n;
    std::set<int> distinct;
    
    for (int i = 1; i <= 500000; i++) {
        int r = recaman[i-1] - i;
        if (r <= 0 || !distinct.insert (r).second) r += (2 * i);
        distinct.insert (r);
        recaman[i] = r;
    }
    
    while (scanf ("%d", &n)) {
        if (n == -1) break;
        printf ("%d\n", recaman[n]);
    }
    
    return 0;
}