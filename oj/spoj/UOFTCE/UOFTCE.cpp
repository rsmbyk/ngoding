#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using i64 = std::int64_t;

constexpr int kDr[4] = {-1, 1, 0, 0};
constexpr int kDc[4] = {0, 0, -1, 1};

static i64 mall_time(const std::vector<std::string>& grid) {
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());

    int sr = 0;
    int sc = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 'C') {
                sr = r;
                sc = c;
            }
        }
    }

    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, -1));
    std::queue<std::pair<int, int>> q;
    dist[sr][sc] = 0;
    q.emplace(sr, sc);

    i64 walk_both_ways = 0;
    int farthest = 0;
    int stores = 0;

    while (!q.empty()) {
        const auto [r, c] = q.front();
        q.pop();
        const int d = dist[r][c];

        if (grid[r][c] == 'S') {
            walk_both_ways += 2LL * d;
            if (d > farthest) {
                farthest = d;
            }
            ++stores;
        }

        for (int k = 0; k < 4; ++k) {
            const int nr = r + kDr[k];
            const int nc = c + kDc[k];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                continue;
            }
            if (grid[nr][nc] == '#' || dist[nr][nc] != -1) {
                continue;
            }
            dist[nr][nc] = d + 1;
            q.emplace(nr, nc);
        }
    }

    // Subtract the unpaid first outbound: clock starts at the first shop.
    return walk_both_ways - farthest + 60LL * stores;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int malls;
    std::cin >> malls;
    while (malls--) {
        int rows, cols;
        std::cin >> rows >> cols;
        std::vector<std::string> grid(rows);
        for (int r = 0; r < rows; ++r) {
            std::cin >> grid[r];
        }
        std::cout << mall_time(grid) << '\n';
    }
}
