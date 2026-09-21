#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, d;
    std::cin >> n >> d;

    std::vector<std::array<int, 6>> points(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            std::cin >> points[i][j];
        }
    }

    i64 answer = 0;
    const int masks = 1 << d;
    for (int mask = 0; mask < masks; ++mask) {
        i64 mx = std::numeric_limits<i64>::min();
        i64 mn = std::numeric_limits<i64>::max();
        for (int i = 0; i < n; ++i) {
            i64 sum = 0;
            for (int j = 0; j < d; ++j) {
                // Bit j set → +p_j, unset → -p_j. A mask and its negation share a span.
                if (mask & (1 << j)) {
                    sum += points[i][j];
                } else {
                    sum -= points[i][j];
                }
            }
            mx = std::max(mx, sum);
            mn = std::min(mn, sum);
        }
        answer = std::max(answer, mx - mn);
    }

    std::cout << answer << '\n';
}
