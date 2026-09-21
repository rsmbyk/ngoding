#include <iostream>
using namespace std;

int main (int argc, char **argv) {
    int tc, n, k;
    string b;
    cin >> tc;
    
    while (tc--) {
        cin >> n >> k;
        cin >> b;
        
        int s, d;
        s = ((n-k)/2) + ((n-k)%2);
        d = (n-k) / 2;
        bool flag[b.length ()] = {};
        
        for (int i = 0; i < b.length (); i++) {
            if (b[i] == '0' && d > 0) {
                flag[i] = true;
                d--;
            }
            else if (b[i] == '1' && s > 0) {
                flag[i] = true;
                s--;
            }
        }
        
        int left = s + d;
        for (int i = 0; i < b.length (); i++) {
            if (flag[i]) continue;
            if (left) left--;
            else cout << b[i];
        }
        
        cout << endl;
    }
    
    return 0;
}