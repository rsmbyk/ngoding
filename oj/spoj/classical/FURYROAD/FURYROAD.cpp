#include <iostream>
#include <queue>
#include <utility>
#include <vector>

constexpr int kMaxCoord = 1000;

static const int kDx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
static const int kDy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

static int count_parties(const std::vector<std::pair<int, int>>& boys) {
    std::vector<std::vector<char>> occupied(
        kMaxCoord + 1, std::vector<char>(kMaxCoord + 1, 0));
    std::vector<std::vector<char>> painted(
        kMaxCoord + 1, std::vector<char>(kMaxCoord + 1, 0));

    for (const auto& boy : boys) {
        occupied[boy.first][boy.second] = 1;
    }

    int parties = 0;
    for (const auto& boy : boys) {
        const int start_x = boy.first;
        const int start_y = boy.second;
        if (painted[start_x][start_y]) {
            continue;
        }
        ++parties;
        // Flood fill one connected blob under the eight-neighbor rule.
        std::queue<std::pair<int, int>> walk;
        walk.push({start_x, start_y});
        painted[start_x][start_y] = 1;
        while (!walk.empty()) {
            const auto [x, y] = walk.front();
            walk.pop();
            for (int dir = 0; dir < 8; ++dir) {
                const int nx = x + kDx[dir];
                const int ny = y + kDy[dir];
                if (nx < 0 || ny < 0 || nx > kMaxCoord || ny > kMaxCoord) {
                    continue;
                }
                if (!occupied[nx][ny] || painted[nx][ny]) {
                    continue;
                }
                painted[nx][ny] = 1;
                walk.push({nx, ny});
            }
        }
    }
    return parties;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests;
    std::cin >> tests;
    for (int scenario = 1; scenario <= tests; ++scenario) {
        int boy_count;
        std::cin >> boy_count;
        std::vector<std::pair<int, int>> boys(boy_count);
        for (auto& boy : boys) {
            std::cin >> boy.first >> boy.second;
        }
        std::cout << "Case " << scenario << ": " << count_parties(boys)
                  << '\n';
    }
}
