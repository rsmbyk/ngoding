#include <iostream>
#include <vector>
using namespace std;

int main (int argc, char **argv) {
    int tc;
    std::string str;
    cin >> tc;
    
    while (tc--) {
        int h[8]={}, v[8]={};
        int r=0;
        bool valid = true;
        
        for (int i = 0; i < 8; i++) {
            cin >> str;
            for (int j = 0; j < 8; j++) {
                if (str[j] == 'R') {
                    if (h[i] > 0 || v[j] > 0) {
                        valid = false;
                        break;
                    }
            
                    r++;
                    h[i]++;
                    v[j]++;
                }
            }
        }
        
        if (valid && r == 8) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    
    return 0;
}