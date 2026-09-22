#include <array>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using Matrix = std::array<std::array<i64, 4>, 4>;
using Vector = std::array<i64, 4>;

constexpr i64 kMod = 1'000'000'007;

// One step:
//   a(n+1) = 2*a(n) + a(n-1) + F(n-2)
//   F(n-1) = F(n-2) + F(n-3)
// Vector is [a(n), a(n-1), F(n-2), F(n-3)].
static Matrix step_matrix() {
    return {{
        {{2, 1, 1, 0}},
        {{1, 0, 0, 0}},
        {{0, 0, 1, 1}},
        {{0, 0, 1, 0}},
    }};
}

static Matrix multiply(const Matrix& left, const Matrix& right) {
    Matrix out{};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            i64 sum = 0;
            for (int mid = 0; mid < 4; ++mid) {
                sum = (sum + left[row][mid] * right[mid][col]) % kMod;
            }
            out[row][col] = sum;
        }
    }
    return out;
}

static Matrix identity() {
    Matrix out{};
    for (int i = 0; i < 4; ++i) {
        out[i][i] = 1;
    }
    return out;
}

static Matrix power(Matrix base, i64 exp) {
    Matrix result = identity();
    while (exp > 0) {
        if (exp & 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp >>= 1;
    }
    return result;
}

static Vector apply(const Matrix& matrix, const Vector& vector) {
    Vector out{};
    for (int row = 0; row < 4; ++row) {
        i64 sum = 0;
        for (int col = 0; col < 4; ++col) {
            sum = (sum + matrix[row][col] * vector[col]) % kMod;
        }
        out[row] = sum;
    }
    return out;
}

static i64 term(i64 n) {
    if (n <= 2) {
        return 1;
    }
    // Start at n = 3: [a(3), a(2), F(1), F(0)] = [3, 1, 1, 0]
    const Vector start{{3, 1, 1, 0}};
    const Matrix jumped = power(step_matrix(), n - 3);
    return apply(jumped, start)[0];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests;
    std::cin >> tests;
    while (tests--) {
        i64 n;
        std::cin >> n;
        std::cout << term(n) << '\n';
    }
}
