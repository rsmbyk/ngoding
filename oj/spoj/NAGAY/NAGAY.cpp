#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using i128 = __int128;

static void print_i128(i128 x) {
    if (x == 0) {
        std::cout << '0';
        return;
    }
    char buf[80];
    int len = 0;
    while (x > 0) {
        buf[len++] = static_cast<char>('0' + static_cast<int>(x % 10));
        x /= 10;
    }
    while (len--) {
        std::cout << buf[len];
    }
}

static i128 remainder_sum(i64 n, i64 k) {
    i128 ans = 0;
    if (n > k) {
        ans += i128(k) * (n - k);
        n = k;
    }

    for (i64 i = 1; i <= n;) {
        const i64 p = k / i;
        const i64 rem = k % i;
        // Remainder counts down by p until it would go negative.
        i64 last = i + rem / p;
        if (last > n) {
            last = n;
        }
        const i64 cnt = last - i + 1;
        const i128 drop = i128(cnt - 1) * p;
        ans += i128(cnt) * (2 * i128(rem) - drop) / 2;
        i = last + 1;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 n, k;
    std::cin >> n >> k;
    print_i128(remainder_sum(n, k));
    std::cout << '\n';
}
