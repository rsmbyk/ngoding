#include <cstdio>
#include <queue>
#include <set>

int main (int argc, char const *argv[]) {
    int n, k, bill;
    scanf ("%d", &n);
    
    std::multiset<int> box;
    long long sum = 0;
    
    while (n--) {
        scanf ("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf ("%d", &bill);
            box.insert (bill);
        }
        
        sum += (*(--box.end ()) - *box.begin ());
        box.erase (box.begin ());
        box.erase (--box.end ());
    }
    
    printf ("%lld\n", sum);
    return 0;
}