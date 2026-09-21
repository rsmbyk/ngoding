#include <cstdint>
#include <iostream>

using i64 = std::int64_t;

constexpr i64 kMod = 1'000'000'007;

static i64 mod_pow(i64 base, i64 exp) {
    i64 result = 1;
    base %= kMod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % kMod;
        }
        base = (base * base) % kMod;
        exp >>= 1;
    }
    return result;
}

static i64 max_product(i64 n) {
    if (n <= 3) {
        return n;
    }
    const i64 m = n / 3;
    const i64 r = n % 3;
    if (r == 0) {
        return mod_pow(3, m);
    }
    if (r == 1) {
        // 3m+1 would leave a 1; rewrite as (m-1) threes and two twos.
        return (mod_pow(3, m - 1) * 4) % kMod;
    }
    return (mod_pow(3, m) * 2) % kMod;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 n;
    std::cin >> n;
    std::cout << max_product(n) << '\n';
}
