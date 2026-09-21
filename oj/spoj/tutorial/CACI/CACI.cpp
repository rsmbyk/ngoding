#include <iostream>
#include <cstdio>
using namespace std;

int main (int argc, char **argv) {
    string input;
    while (getline (cin, input)) {
        for (int i = 0; i < input.length (); i++)
            if (input[i] == ' ')
                printf (" ");
            else
                printf ("%c", ((input.c_str ()[i] - 'A' + 3) % 26) + 'A');
        printf ("\n");
    }
}