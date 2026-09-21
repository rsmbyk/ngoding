#include <cstdint>
#include <iostream>
#include <vector>

using i64 = std::int64_t;

static bool enough(const std::vector<int>& quality, i64 time, i64 target) {
    i64 made = 0;
    for (int q : quality) {
        made += time / q;
        // Exact total can overflow 64-bit; we only need "at least T".
        if (made >= target) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests;
    std::cin >> tests;
    while (tests--) {
        int n;
        i64 target;
        std::cin >> n >> target;

        std::vector<int> quality(n);
        int fastest = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> quality[i];
            if (i == 0 || quality[i] < fastest) {
                fastest = quality[i];
            }
        }

        i64 low = 1;
        i64 high = static_cast<i64>(fastest) * target;
        while (low < high) {
            i64 mid = low + (high - low) / 2;
            if (enough(quality, mid, target)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        std::cout << low << '\n';
    }
}
