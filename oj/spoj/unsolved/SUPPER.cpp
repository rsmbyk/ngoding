#include <cstdio>
#include <queue>

using namespace std;

int main (int args, char const *argv[]) {
    int n;
    scanf ("%d", &n);
    
    int numb[n];
    for (int i = 0; i < n; i++) scanf ("%d", &numb[i]);
    
    priority_queue<int> longest;
    priority_queue<int> supernumber;
    supernumber.push (-numb[0]);
    
    for (int i = 1; i < n; i++) {
        if (numb[i] > numb[i-1]) supernumber.push (-numb[i-1]);
        else {
            if (supernumber.size () > longest.size ()) longest = supernumber;
            supernumber = priority_queue<int> ();
        }
    }
    
    while (!longest.empty ()) {
        printf ("%d ", longest.top ());
        longest.pop ();
    }
}