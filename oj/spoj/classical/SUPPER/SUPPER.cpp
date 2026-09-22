#include <algorithm>
#include <iostream>
#include <vector>

// Prefix maximums over values 1..n. Each index stores one block; the block
// width is the lowest set bit of the index.
struct PrefixMax {
    std::vector<int> blocks;

    explicit PrefixMax(int value_count) : blocks(value_count + 1) {}

    void raise(int value, int length) {
        for (int index = value; index < static_cast<int>(blocks.size());
             index += index & -index) {
            blocks[index] = std::max(blocks[index], length);
        }
    }

    int prefix(int value) const {
        int best = 0;
        for (int index = value; index > 0; index -= index & -index) {
            best = std::max(best, blocks[index]);
        }
        return best;
    }

    void clear() { std::fill(blocks.begin(), blocks.end(), 0); }
};

static void supernumbers(const std::vector<int>& permutation) {
    const int value_count = static_cast<int>(permutation.size());
    std::vector<int> from_left(value_count), from_right(value_count);
    PrefixMax best(value_count);

    for (int place = 0; place < value_count; ++place) {
        const int value = permutation[place];
        from_left[place] = best.prefix(value - 1) + 1;
        best.raise(value, from_left[place]);
    }

    int longest = 0;
    for (int length : from_left) {
        longest = std::max(longest, length);
    }

    // Greater values become a prefix when the slot is n+1-value.
    best.clear();
    for (int place = value_count - 1; place >= 0; --place) {
        const int value = permutation[place];
        const int flipped = value_count + 1 - value;
        from_right[place] = best.prefix(flipped - 1) + 1;
        best.raise(flipped, from_right[place]);
    }

    std::vector<int> chosen;
    for (int place = 0; place < value_count; ++place) {
        // The value itself is in both lengths.
        if (from_left[place] + from_right[place] - 1 == longest) {
            chosen.push_back(permutation[place]);
        }
    }
    std::sort(chosen.begin(), chosen.end());

    std::cout << chosen.size() << '\n';
    for (int i = 0; i < static_cast<int>(chosen.size()); ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << chosen[i];
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // The judge always sends ten permutations and no leading count.
    for (int test = 0; test < 10; ++test) {
        int value_count;
        std::cin >> value_count;
        std::vector<int> permutation(value_count);
        for (int& value : permutation) {
            std::cin >> value;
        }
        supernumbers(permutation);
    }
}
