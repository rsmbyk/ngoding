#include <cstdio>
#include <iostream>
using namespace std;

int main (int argc, char **argv) {
    int tc;
    string s;
    cin >> tc;
    
    while (tc--) {
        cin >> s;
        
        int k=0, ke=0, kek=0;
        int p=0;
        
        for (int i = 0; i < s.length (); i++)
            if (s[i] == 'K')
                k++, kek += ke;
            else if (s[i] == 'E')
                ke += k;
        
        cout << kek << endl;
    }
}