#include <cstdio>
#include <vector>
#include <queue>

int main (int argc, char const *argv[]) {
    int n, input, total=0;
    std::vector<int> groups;
    std::queue<int> seats;
    scanf ("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf ("%d", &input);
        groups.push_back (input);
        total += input;
    }
    
    int size = 0;
    for (int i = 0; i < n; i++) {
        size += groups[i];
        int pair = 0;
        
        for (int j = i+1; j < n; j++) {
            pair += groups[j];
            if (pair == size) pair = 0;
            else if (pair > size) break;
        }
        
        if (pair == 0) seats.push (size);
    }
    
    while (!seats.empty ()) {
        printf ("%d %d\n", seats.front (), total/seats.front ());
        seats.pop ();
    }
}