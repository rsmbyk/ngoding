#include <cstdio>
#include <queue>
#include <climits>

int main () {
    std::deque<int> set, que;
    int *max = new int (INT_MIN);
    int n, k, numb;
    scanf ("%d", &n);
    
    while (n--) {
        scanf ("%d", &numb);
        set.push_back (numb);
    }
    
    scanf ("%d", &k);
    k--;
    while (k--) {
        que.push_back (set.front ());
        set.pop_front ();
        if (que.back () > *max) max = &que.back ();
    }
    
    while (!set.empty ()) {
        que.push_back (set.front ());
        if (que.back () > *max) max = &que.back ();
        printf ("%d ", *max);
        
        if (&que.front () == max) {
            *max = 0;
            for (std::deque<int>::iterator it = que.begin (); it < que.end (); it++) {
                if (*it > *max) max = &(*it);
            }
        }
        
        que.pop_front ();
        set.pop_front ();
    }
}