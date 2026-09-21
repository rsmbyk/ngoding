#include <cstdio>
#include <map>
#include <vector>

int main (int args, char const *argv[]) {
    int n;
    while (scanf ("%d", &n) && n != 0) {
        std::map<int, int> permut;
        std::vector<int> order;
        order.push_back (0);
        int input;
        
        for (int i = 1; i <= n; i++) {
            scanf ("%d", &input);
            permut.insert (std::pair<int, int> (input, i));
            order.push_back (input);
        };
        bool ambiguous = true;
        for (int i = 1; i <= n; i++) {
            int index = permut[i];
            if (permut[index] != order[index]) {
                ambiguous = false;
                break;
            }
        }
        
        if (ambiguous) printf ("ambiguous\n");
        else printf ("not ambiguous\n");
    }
}