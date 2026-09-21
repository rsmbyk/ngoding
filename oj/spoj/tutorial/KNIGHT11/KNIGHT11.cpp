#include <bits/stdc++.h>
using namespace std;

int cost[10][10];
bool visit[10][10];
int Dx[] = { -2, -1,  1,  2, 2, 1, -1, -2 };
int Dy[] = { -1, -2, -2, -1, 1, 2,  2,  1 };
string a, b;

void bfs (int sx, int sy, int dx, int dy) {
    int x, y;
    queue<pair<int, int> > Q;
    pair <int, int> pii;
    pii.first = sx;
    pii.second = sy;
    Q.push (pii);
    cost[sx][sy] = 0;
    memset (visit, false, sizeof (visit));
    visit[sx][sy] = true;
    
    while (!Q.empty ()) {
        pii = Q.front ();
        Q.pop ();
        if (pii.first == dx && pii.second == dy) {
            cout << "To get from " << a
                 << " to " << b
                 << " takes " << cost[pii.first][pii.second]
                 << " knight moves." << endl;
            return;
        }
        
        for (int i = 0; i < 8; i++) {
            x = pii.first  + Dx[i];
            y = pii.second + Dy[i];
            
            if ((x>=1 && x<=8) && (y>=1 && y<=8) && !visit[x][y]) {
                visit[x][y] = true;
                cost[x][y] = cost[pii.first][pii.second] + 1;
                Q.push (make_pair (x, y));
            }
        }
    }
}

int main () {
    int dx, dy, sx, sy;
    while (cin >> a >> b) {
        sx = a[0] - 96;
        sy = a[1] - '0';
        dx = b[0] - 96;
        dy = b[1] - '0';
        bfs (sx, sy, dx, dy);
    }
    return 0;
}