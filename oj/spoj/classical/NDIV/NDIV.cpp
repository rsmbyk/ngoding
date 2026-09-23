#include <cstdint>
#include <iostream>
#include <vector>

using i64 = std::int64_t;

// Primes up to sqrt(10^9). Every x in the window factors using these, plus at
// most one leftover prime larger than that bound.
static std::vector<int> primes_to(int limit) {
    std::vector<char> is_composite(limit + 1);
    std::vector<int> primes;
    for (int value = 2; value <= limit; ++value) {
        if (is_composite[value]) {
            continue;
        }
        primes.push_back(value);
        if (static_cast<i64>(value) * value > limit) {
            continue;
        }
        for (int multiple = value * value; multiple <= limit; multiple += value) {
            is_composite[multiple] = 1;
        }
    }
    return primes;
}

static int divisor_count(int value, const std::vector<int>& primes) {
    if (value == 1) {
        return 1;
    }
    int count = 1;
    int leftover = value;
    for (int prime : primes) {
        if (static_cast<i64>(prime) * prime > leftover) {
            break;
        }
        if (leftover % prime != 0) {
            continue;
        }
        int exponent = 0;
        while (leftover % prime == 0) {
            leftover /= prime;
            ++exponent;
        }
        count *= exponent + 1;
    }
    // One prime factor larger than sqrt of the original value.
    if (leftover > 1) {
        count *= 2;
    }
    return count;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int left, right, target;
    std::cin >> left >> right >> target;

    // ceil(sqrt(10^9)) is 31623; that covers every possible first factor.
    const std::vector<int> primes = primes_to(31623);

    int answer = 0;
    if (left <= right) {
        for (int value = left; value <= right; ++value) {
            if (divisor_count(value, primes) == target) {
                ++answer;
            }
        }
    }
    std::cout << answer << '\n';
}
