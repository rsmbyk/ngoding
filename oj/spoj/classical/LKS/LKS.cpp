#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int rucksack[2][2002];

int getNumb () {
    int r=0;
    int c;
    
    while (true) {
        c = getchar ();
        if (c == ' ' || c == '\n') continue;
        else break;
    }
    
    if (c != '-') r = r + c - '0';
    
    while (true) {
        c = getchar ();
        if (c >= '0' && c <= '9') r = 10 * r + c -'0';
        else break;
    }
    
    return r;
}

pair<int, int> getPair () {
    int v, w;
    v = getNumb ();
    w = getNumb ();
    return make_pair (w, v);
};

int main (int argc, char **argv) {
    int k, n;
    scanf ("%d %d", &k, &n);
    
    vector<pair<int, int> > items;
    for (int i = 0; i < n; i++) items.push_back (getPair ());
    
    int a=1, *prev, *now;
    prev = rucksack[0];
    now = rucksack[1];
    
    for (int i = 0; i < n; i++) {
        pair<int, int> item = items[i];
        for (int j = 0; j <= k; j++)
            if (j < item.second) now[j] = prev[j];
            else now[j] = max (prev[j - item.second] + item.first, prev[j]);
        a++;
        swap (prev, now);
    }
    
    swap (prev, now);
    printf ("%d\n", now[k]);
}