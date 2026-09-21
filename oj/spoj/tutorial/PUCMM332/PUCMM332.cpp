#include <iostream>
#include <cstdio>
using namespace std;

int main (int argc, char **argv) {
    int tc;
    scanf ("%d", &tc);
    
    for (int t = 1; t <= tc; t++) {
        string input;
        int shift;
        
        cin >> input >> shift;
        for (int i = 0; i < input.length (); i++) {
            input[i] = (input[i] - shift);
            if (input[i] < 'A')
                input[i] = input[i] + 26;
        }
        cout << "Test Case #" << t << ": " << input << endl;
    }
}