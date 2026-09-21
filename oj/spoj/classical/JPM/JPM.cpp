#include <iostream>
#include <vector>

static constexpr int kMaxN = 50000;

static std::vector<char> sieve_primes(int n) {
    std::vector<char> is_prime(n + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i] == 0) {
            continue;
        }
        for (int j = i * i; j <= n; j += i) {
            is_prime[j] = 0;
        }
    }
    return is_prime;
}

static int min_distinct_primes(int n, const std::vector<char>& is_prime) {
    // 4=2+2 and 6=3+3 are Goldbach but not distinct. 1 has no primes.
    if (n == 1 || n == 4 || n == 6) {
        return -1;
    }
    if (is_prime[n]) {
        return 1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    // Odd composite: the only pair is {2, n-2}.
    if (is_prime[n - 2]) {
        return 2;
    }
    return 3;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::vector<char> is_prime = sieve_primes(kMaxN);

    int t;
    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        std::cin >> n;
        std::cout << "Case " << i << ": " << min_distinct_primes(n, is_prime)
                  << '\n';
    }
}
