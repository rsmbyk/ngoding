#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using i64 = std::int64_t;

constexpr i64 kInf = std::numeric_limits<i64>::max() / 4;

// Prefix minima over compressed B ranks. Empty slots stay at kInf.
struct PrefixMin {
    std::vector<i64> blocks;

    explicit PrefixMin(int value_count)
        : blocks(value_count + 1, kInf) {}

    void lower(int rank, i64 value) {
        for (int index = rank; index < static_cast<int>(blocks.size());
             index += index & -index) {
            blocks[index] = std::min(blocks[index], value);
        }
    }

    i64 prefix(int rank) const {
        i64 best = kInf;
        for (int index = rank; index > 0; index -= index & -index) {
            best = std::min(best, blocks[index]);
        }
        return best;
    }
};

struct Camp {
    i64 position;
    i64 gold;
    i64 energy;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int camp_count;
    std::cin >> camp_count;
    std::vector<Camp> camps(camp_count);
    for (Camp& camp : camps) {
        std::cin >> camp.position >> camp.gold >> camp.energy;
    }

    if (camp_count == 0) {
        std::cout << 0 << '\n';
        return 0;
    }

    std::vector<i64> energy_prefix(camp_count);
    std::vector<i64> gold_prefix(camp_count);
    std::vector<i64> right_key(camp_count);
    std::vector<i64> left_key(camp_count);

    i64 energy_sum = 0;
    i64 gold_sum = 0;
    for (int i = 0; i < camp_count; ++i) {
        // B[i] uses energy before i, so build it before adding this camp.
        left_key[i] = energy_sum - camps[i].position;
        energy_sum += camps[i].energy;
        gold_sum += camps[i].gold;
        energy_prefix[i] = energy_sum;
        gold_prefix[i] = gold_sum;
        right_key[i] = energy_sum - camps[i].position;
    }

    std::vector<i64> ordered = left_key;
    std::sort(ordered.begin(), ordered.end());
    ordered.erase(std::unique(ordered.begin(), ordered.end()), ordered.end());

    auto rank_of = [&](i64 key) {
        return static_cast<int>(
            std::lower_bound(ordered.begin(), ordered.end(), key) -
            ordered.begin()) +
               1;
    };
    auto rank_at_most = [&](i64 key) {
        return static_cast<int>(
            std::upper_bound(ordered.begin(), ordered.end(), key) -
            ordered.begin());
    };

    PrefixMin best_before(static_cast<int>(ordered.size()));
    i64 answer = 0;

    for (int right = 0; right < camp_count; ++right) {
        const i64 gold_before =
            right == 0 ? 0 : gold_prefix[right - 1];
        // Insert this camp as a left end, then ask among B <= A[right].
        best_before.lower(rank_of(left_key[right]), gold_before);

        const int query_rank = rank_at_most(right_key[right]);
        const i64 smallest_before = best_before.prefix(query_rank);
        answer = std::max(answer, gold_prefix[right] - smallest_before);
    }

    std::cout << answer << '\n';
}
