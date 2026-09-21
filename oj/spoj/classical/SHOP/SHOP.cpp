#include <cstdio>
#include <cstring>
#include <climits>

using namespace std;
char shop[25][25];
int time[25][25];
bool visited[25][25];
int move[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int h, w, fastest;

void walk (int y, int x, int prev) {
    if (x < 0 || x >= w || y < 0 || y >= h) return;
    if (shop[y][x] == 'X') return;
    if (prev >= fastest) return;
    if (visited[y][x] && prev >= time[y][x]) return;
    
    if (shop[y][x] == 'D') {
        if (prev < fastest) fastest = prev;
        return;
    }
    
    time[y][x] = prev + shop[y][x] - '0';
    visited[y][x] = true;
    for (int i = 0; i < 4; i++) walk (y+move[i][0], x+move[i][1], time[y][x]);
}

int main (int args, char const *argv[]) {
    while (scanf ("%d %d", &w, &h) && (h > 0)) {
        memset (visited, false, sizeof (visited));
        for (int y = 0; y < 25; y++) for (int x = 0; x < 25; x++) time[y][x] = INT_MAX;
        fastest = INT_MAX;
        
        int sy, sx;
        for (int y = 0; y < h; y++) {
            scanf ("%s", shop[y]);
            for (int x = 0; x < w; x++) if (shop[y][x] == 'S') sy = y, sx = x;
        }
        
        walk (sy, sx, 0);
        printf ("%d\n", fastest + '0' - 'S');
    }
}