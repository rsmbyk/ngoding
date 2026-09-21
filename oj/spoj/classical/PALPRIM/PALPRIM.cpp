#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u128 = __uint128_t;

static const i64 kPow10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
};

static u64 mul_mod(u64 a, u64 b, u64 mod) {
    return static_cast<u64>(u128(a) * b % mod);
}

static u64 pow_mod(u64 a, u64 exp, u64 mod) {
    u64 result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, a, mod);
        }
        a = mul_mod(a, a, mod);
        exp >>= 1;
    }
    return result;
}

static bool is_prime(u64 n) {
    if (n < 2) {
        return false;
    }
    for (u64 p : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull}) {
        if (n % p == 0) {
            return n == p;
        }
    }

    // n-1 = 2^s * d, d odd. Seven bases suffice for every n < 3.41e14.
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (u64 a : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull}) {
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool witness_ok = false;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                witness_ok = true;
                break;
            }
        }
        if (!witness_ok) {
            return false;
        }
    }
    return true;
}

static i64 reverse_digits(i64 x) {
    i64 rev = 0;
    while (x > 0) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return rev;
}

static std::vector<i64> palindromic_primes() {
    std::vector<i64> primes = {2, 3, 5, 7, 11};

    // Odd lengths 3..13: first half has 2..7 digits. Even length is 11×something.
    for (int half_digits = 2; half_digits <= 7; ++half_digits) {
        const i64 start = kPow10[half_digits - 1];
        const i64 last = kPow10[half_digits] - 1;
        const i64 shift = kPow10[half_digits - 1];
        for (i64 h = start; h <= last; ++h) {
            const int first = static_cast<int>(h / start);
            if (first % 2 == 0 || first == 5) {
                continue;
            }
            const i64 p = h * shift + reverse_digits(h / 10);
            if (is_prime(static_cast<u64>(p))) {
                primes.push_back(p);
            }
        }
    }
    return primes;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::vector<i64> primes = palindromic_primes();

    int t;
    std::cin >> t;
    while (t--) {
        i64 n;
        std::cin >> n;
        auto it = std::upper_bound(primes.begin(), primes.end(), n);
        --it;
        std::cout << *it << '\n';
    }
}
