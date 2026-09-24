#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = std::int64_t;

struct Village {
    i64 cost;
    i64 loot;
};

static int best_pillages(i64 coins, std::vector<Village> weak,
                         std::vector<Village> strong) {
    std::sort(weak.begin(), weak.end(),
              [](const Village& left, const Village& right) {
                  return left.cost < right.cost;
              });

    // Weak villages never drain the bank: take every one that becomes affordable.
    i64 purse = coins;
    int weak_taken = 0;
    for (const Village& village : weak) {
        if (purse >= village.cost) {
            purse += village.loot - village.cost;
            ++weak_taken;
        }
    }

    // Strong doors above the purse can never be paid after the weak pass.
    std::vector<Village> attackable;
    for (const Village& village : strong) {
        if (village.cost <= purse) {
            attackable.push_back(village);
        }
    }

    // Subset DP needs a small strong set. Prefer cheapest doors if oversized.
    std::sort(attackable.begin(), attackable.end(),
              [](const Village& left, const Village& right) {
                  return left.cost < right.cost;
              });
    constexpr int kMaxStrong = 20;
    if (static_cast<int>(attackable.size()) > kMaxStrong) {
        attackable.resize(kMaxStrong);
    }

    const int strong_count = static_cast<int>(attackable.size());
    const int subsets = 1 << strong_count;
    // money_after[mask] = purse after completing every strong in mask, or -1.
    std::vector<i64> money_after(subsets, -1);
    money_after[0] = purse;

    int best_strong = 0;
    for (int mask = 0; mask < subsets; ++mask) {
        if (money_after[mask] < 0) {
            continue;
        }
        best_strong =
            std::max(best_strong, __builtin_popcount(static_cast<unsigned>(mask)));

        for (int next = 0; next < strong_count; ++next) {
            if ((mask >> next) & 1) {
                continue;
            }
            if (money_after[mask] < attackable[next].cost) {
                continue;
            }
            const int next_mask = mask | (1 << next);
            money_after[next_mask] = money_after[mask] + attackable[next].loot -
                                     attackable[next].cost;
        }
    }

    return weak_taken + best_strong;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests;
    std::cin >> tests;
    while (tests--) {
        int village_count;
        i64 coins;
        std::cin >> village_count >> coins;
        std::vector<Village> weak;
        std::vector<Village> strong;
        weak.reserve(village_count);
        strong.reserve(village_count);
        for (int i = 0; i < village_count; ++i) {
            Village village;
            std::cin >> village.cost >> village.loot;
            if (village.cost > village.loot) {
                strong.push_back(village);
            } else {
                weak.push_back(village);
            }
        }
        std::cout << best_pillages(coins, std::move(weak), std::move(strong))
                  << '\n';
    }
}
