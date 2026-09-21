#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

typedef struct node {
    int x, y, step;
    
    node (int nx, int ny, int step) {
        this->step = step;
        x = nx;
        y = ny;
    } 
} State;

int x[] = {1, 2,  2,  1, -1, -2, -2, -1};
int y[] = {2, 1, -1, -2, -2, -1,  1,  2};
queue<State> q;
int board[8][8];

bool inBound (int nx, int ny) {
    if (nx < 0 || ny < 0) return false;
    return !(nx >= 8 || ny >= 8);
}

int moves () {
    State s = q.front ();
    q.pop ();
    if (board[s.y][s.x] == 2) return s.step;
    board[s.y][s.x] = 1;
    for (int i = 0; i < 8; i++) {
        int nx, ny;
        nx = s.x + x[i];
        ny = s.y + y[i];
        if (board[ny][nx] != 1 && inBound (nx, ny))
            q.push (State (nx, ny, s.step+1));
    }
    return moves ();
}

int main (int argc, char **argv) {
    int T;
    scanf ("%d", &T);
    getchar ();
    
    while (T--) {
        string s;
        getline (cin, s);
        memset (board, 0, sizeof board);
        q = queue<State> ();
        
        int sx, sy, ex, ey;
        sx = s[0] - 'a';
        sy = s[1] - '0' - 1;
        ex = s[3] - 'a';
        ey = s[4] - '0' - 1;
        
        board[ey][ex] = 2;
        q.push (State (sx, sy, 0));
        printf ("%d\n", moves ());
    }
}