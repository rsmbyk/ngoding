#include <cstdint>
#include <iostream>

using u64 = std::uint64_t;

u64 gcd(u64 a, u64 b) {
    while (b != 0) {
        u64 t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;

        int ones[31] = {};
        for (int i = 0; i < n; ++i) {
            unsigned a;
            std::cin >> a;
            for (int b = 0; b < 31; ++b) {
                ones[b] += (a >> b) & 1u;
            }
        }

        const u64 pairs = u64(n) * u64(n - 1) / 2;
        u64 p = 0;
        for (int b = 0; b < 31; ++b) {
            const u64 z = u64(n - ones[b]);
            const u64 pairs_with_bit = pairs - z * (z - 1) / 2;
            p += (1ull << b) * pairs_with_bit;
        }

        const u64 g = gcd(p, pairs);
        std::cout << (p / g) << '/' << (pairs / g) << '\n';
    }
}
