#include <iostream>
#include <cstring>
#include <cstdio>

int main () {
    char smiley[1000001];
    scanf ("%s", smiley);
    int sub[4], ln;
    memset (sub, 0, sizeof (sub));
    ln = strlen (smiley);
    
    for (int i = 0; i < ln; i++) {
        if (smiley[i] == '1') sub[0]++;
        else if (smiley[i] == '8') {
            if (sub[0] || sub[1]) sub[1] = std::max (sub[0], sub[1]) + 1;
        }
        else if (smiley[i] == '0') {
            if (sub[1] || sub[2]) sub[2] = std::max (sub[1], sub[2]) + 1;
        }
        else if (smiley[i] == '7') {
            if (sub[2] || sub[3]) sub[3] = std::max (sub[2], sub[3]) + 1;
        }
    }
    
    std::cout <<  sub[3] << std::endl;
}