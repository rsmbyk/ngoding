#include <cstdio>
#include <queue>
#include <vector>


int getCommandCode (char c) {
    if (c == 'f') return 1;
    else if (c == 'b') return -1;
    else if (c == 't') return 2;
    else if (c == 'p') return -2;
    else return 0;
}

int main () {
    std::deque<int> jobs;
    char cmd[10];
    int query, n, head=1;
    scanf ("%d", &query);
    
    while (query--) {
        scanf ("%s", cmd);
        
        if (cmd[0] == 'r') head *= -1;
        else {
            int code = getCommandCode (cmd[0]) * head;
            
            if (code == 1) {
                if (jobs.empty ()) printf ("No job for Ada?\n");
                else {
                    printf ("%d\n", jobs.front ());
                    jobs.pop_front ();
                }
            }
            else if (code == -1) {
                if (jobs.empty ()) printf ("No job for Ada?\n");
                else {
                    printf ("%d\n", jobs.back ());
                    jobs.pop_back ();
                }
            }
            else if (code == 2) {
                scanf ("%d", &n); getchar ();
                jobs.push_front (n);
            }
            else {
                scanf ("%d", &n); getchar ();
                jobs.push_back (n);
            }
        }
    }
}