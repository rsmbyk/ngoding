#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int main (int argc, char **argv) {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        string s, r;
        cin >> s;
        r = s;
        reverse (r.begin (), r.end ());
        
        int lcs[s.length ()+1][s.length ()+1]={};
        for (int i = 1; i <= s.length (); i++)
            for (int j = 1; j <= s.length (); j++)
                if (s[i-1] == r[j-1])
                    lcs[i][j] = lcs[i-1][j-1] + 1;
                else
                    lcs[i][j] = max (lcs[i-1][j], lcs[i][j-1]);
        cout << s.length () - lcs[s.length ()][s.length ()] << endl;
    }
}