#include <algorithm>
#include <iostream>
#include <vector>

// The slot index is the berry total. A slot is on if that total is reachable.
// "left" means the previous bush was skipped, so this bush may be taken.
static int max_berries(const std::vector<int>& bushes, int limit) {
    std::vector<char> left(limit + 1), took(limit + 1);
    std::vector<char> next_left(limit + 1), next_took(limit + 1);
    left[0] = 1;

    for (int berries : bushes) {
        std::fill(next_left.begin(), next_left.end(), 0);
        std::fill(next_took.begin(), next_took.end(), 0);

        for (int filled = 0; filled <= limit; ++filled) {
            if (left[filled] || took[filled]) {
                next_left[filled] = 1;
            }
            // Only a skipped neighbor may start a new pick.
            if (left[filled] && berries > 0 && berries <= limit - filled) {
                next_took[filled + berries] = 1;
            }
        }

        left.swap(next_left);
        took.swap(next_took);
    }

    for (int filled = limit; filled >= 0; --filled) {
        if (left[filled] || took[filled]) {
            return filled;
        }
    }
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests;
    std::cin >> tests;
    for (int scenario = 1; scenario <= tests; ++scenario) {
        int bushes_count, limit;
        std::cin >> bushes_count >> limit;
        std::vector<int> bushes(bushes_count);
        for (int& berries : bushes) {
            std::cin >> berries;
        }
        std::cout << "Scenario #" << scenario << ": " << max_berries(bushes, limit) << '\n';
    }
}
