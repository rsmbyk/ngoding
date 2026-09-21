#include <cstdio>
#include <queue>
#include <set>
using namespace std;

int n, m, k, room[102][102];
int move[][2] = {{1, 0}, {0, 1}, {1, 1}};
std::queue<int> maxs[102][102];
std::set<int> unique[102][102];

queue<int> walkToDoor (int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n) return queue<int> ();
    if (maxs[y][x].empty ()) {
        for (int i = 0; i < 3; i++) {
            queue<int> temp = walkToDoor (x+move[i][0], y+move[i][1]);
            while (!temp.empty ()) {
                int candidate = room[y][x] + temp.front ();
                if (candidate <= k) maxs[y][x].push (candidate);
                temp.pop ();
            }
        }
    }
    
    return maxs[y][x];
}

int main (int args, char const *argv[]) {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d %d", &n, &m, &k);
        
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                scanf ("%d", &room[y][x]);
                unique[y][x].clear ();
                while (!maxs[y][x].empty ()) maxs[y][x].pop ();
            }
        }
        
        maxs[n-1][m-1].push (room[n-1][m-1]);
        queue<int> result = walkToDoor (0, 0);
        int res = -1;
        while (!result.empty ()) {
            if (result.front () > res) res = result.front ();
            result.pop ();
        }
        
        printf ("%d\n", res);
    }
}