#include <cstdio>
#include <map>
#include <set>

std::map<int, int> sizes;
std::multiset<int> sizes2;
int parents[100001];
void initSet (int n) { for (int i = 1; i <= n; i++) parents[i] = i, sizes[i] = 1; }
int findSet (int i) { return parents[i] == i ? i : parents[i] = findSet (parents[i]); }
bool sameSet (int a, int b) { return findSet (a) == findSet (b); }
void unionSet (int a, int b) { parents[findSet (a)] = findSet (b); }

int main (int argc, char const *argv[]) {
    int n, q, a, b;
    scanf ("%d %d", &n, &q);
    initSet (n);
    
    int max=1, min=1;
    
    while (q--) {
        scanf ("%d %d", &a, &b);
        if (!sameSet (a, b)) {
            a = findSet (a);
            b = findSet (b);
            if (sizes[a] > sizes[b]) {
                int c = a;
                a = b;
                b = c;
            }
            
            unionSet (a, b);
            sizes[b] += sizes[a];
            sizes2.insert (sizes[b]);
            if (sizes[b] > max) max = sizes[b];
            if (sizes[a] == min) {
                sizes.erase (a);
                min = max;
                for (std::map<int, int>::iterator it = sizes.begin (); it != sizes.end (); it++) {
                    int i = (*it).first;
                    //printf("i: %d\n", i);
                    if (sizes[i] < min) min = sizes[i];
                }
            }
            else sizes.erase (a);
        }
        
        //printf ("%d-%d\n", max, min);
        printf ("%d\n", max - min);
    }
}