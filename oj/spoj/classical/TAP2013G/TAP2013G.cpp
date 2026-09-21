#include <cstdio>
#include <queue>
#include <algorithm>

int main (int argc, char const *argv[]) {
    int n, input;
    scanf ("%d", &n);
    
    std::priority_queue<int> quadradonia, nlogonia;
    for (int i = 0; i < n; i++) scanf ("%d", &input), quadradonia.push (-input);
    for (int i = 0; i < n; i++) scanf ("%d", &input), nlogonia.push (-input);
    
    int res = 0;
    while (!quadradonia.empty () && !nlogonia.empty ()) {
        int a, b;
        a = -quadradonia.top ();
        b = -nlogonia.top ();
        
        if (b > a) quadradonia.pop (), res++;
        nlogonia.pop ();
    }
    
    printf ("%d\n", res);
    return 0;
}