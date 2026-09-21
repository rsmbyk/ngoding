#include <cstdio>
#include <queue>
using namespace std;

int getNum () {
    int r=0, sign=1;
    char c;
    
    while (true) {
        c = getchar_unlocked ();
        if (c == '-') sign = true;
        else if (c == ' ' || c == '\n') continue;
        else break;
    }
    
    if (c != '-') r = c - '0';
    
    while (true) {
        c = getchar_unlocked ();
        if (c >= '0' && c <= '9') r = 10 * r + c -'0';
        else break;
    }
    
    return r * sign;
}

int main () {
    int tc;
    tc = getNum ();
    
    while (tc--) {
        int phoneCalls, numb, res, k;
        priority_queue<int> numList;
        phoneCalls = getNum ();
        k = getNum ();
        
        while (phoneCalls--) {
            numb = getNum ();
            
            if (numb == 0) {
                if (k > numList.size ()) printf ("-1\n");
                else printf ("%d\n", numList.top ());
            }
            else {
                if (numList.size () < k) numList.push (numb);
                else if (numb < numList.top ()) {
                    numList.pop ();
                    numList.push (numb);
                }
            }
        }
    }
    
    return 0;
}
