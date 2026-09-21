#include <iostream>
using namespace std;

int main (int argc, char **argv) {
    string str;
    int tc=0;
    
    while (cin >> str) {
        if (str.find ("-") != std::string::npos) break;
        int pre=0, open=0;
        for (int i = 0; i < str.length (); i++) {
            if (str[i] == '{') open++;
            else if (open > 0) open--;
            else {
                open++;
                pre++;
            }
        }
        
        cout << ++tc << ". " << pre + (open/2) << endl; 
    }
}