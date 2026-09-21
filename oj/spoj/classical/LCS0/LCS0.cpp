#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using u64 = std::uint64_t;

static int lcs_length(const std::string& walk, const std::string& houses) {
    const int m = static_cast<int>(houses.size());
    if (m == 0 || walk.empty()) {
        return 0;
    }

    const int words = (m + 63) / 64;
    const u64 last_mask =
        (m % 64 == 0) ? ~0ull : (1ull << (m % 64)) - 1ull;

    std::vector<u64> match[26];
    for (int c = 0; c < 26; ++c) {
        match[c].assign(words, 0);
    }
    for (int j = 0; j < m; ++j) {
        match[houses[j] - 'a'][j / 64] |= 1ull << (j % 64);
    }

    std::vector<u64> lamps(words, 0);
    std::vector<u64> united(words);
    std::vector<u64> gap_start(words);

    for (char ch : walk) {
        const std::vector<u64>& here = match[ch - 'a'];
        for (int w = 0; w < words; ++w) {
            united[w] = lamps[w] | here[w];
        }

        // 1 at house 0 and just after every old lamp: start of each gap.
        u64 shift_in = 1;
        for (int w = 0; w < words; ++w) {
            u64 shift_out = lamps[w] >> 63;
            gap_start[w] = (lamps[w] << 1) | shift_in;
            shift_in = shift_out;
        }
        gap_start[words - 1] &= last_mask;

        u64 borrow = 0;
        for (int w = 0; w < words; ++w) {
            const u64 u = united[w];
            const u64 g = gap_start[w];
            const u64 minus = u - g;
            const u64 br1 = u < g;
            const u64 diff = minus - borrow;
            const u64 br2 = minus < borrow;
            borrow = br1 | br2;
            // Leftmost 1 of each gap: bits that were on in U and flipped by the subtract.
            lamps[w] = u & (diff ^ u);
        }
        lamps[words - 1] &= last_mask;
    }

    int answer = 0;
    for (int w = 0; w < words; ++w) {
        answer += __builtin_popcountll(lamps[w]);
    }
    return answer;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string a;
    std::string b;
    std::getline(std::cin, a);
    std::getline(std::cin, b);
    if (!a.empty() && a.back() == '\r') {
        a.pop_back();
    }
    if (!b.empty() && b.back() == '\r') {
        b.pop_back();
    }

    // Inner work is |walk| * ceil(|houses| / 64). Walk the shorter street.
    if (a.size() < b.size()) {
        std::cout << lcs_length(a, b) << '\n';
    } else {
        std::cout << lcs_length(b, a) << '\n';
    }
}
