#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = std::int64_t;

struct FenwickSum {
    std::vector<int> tree;

    explicit FenwickSum(int n) : tree(n + 1, 0) {}

    void add(int i, int val) {
        for (; i < static_cast<int>(tree.size()); i += i & -i) {
            tree[i] += val;
        }
    }

    int prefix(int i) const {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
};

struct Task {
    int burst;
    int pos;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Task> tasks(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> tasks[i].burst;
        tasks[i].pos = i + 1;
    }

    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.burst != b.burst) {
            return a.burst < b.burst;
        }
        return a.pos < b.pos;
    });

    FenwickSum alive_left(n);
    for (int pos = 1; pos <= n; ++pos) {
        alive_left.add(pos, 1);
    }

    std::vector<i64> done(n + 1);
    i64 clock = 0;
    int prev_burst = 0;
    int alive = n;

    for (const Task& task : tasks) {
        clock += static_cast<i64>(task.burst - prev_burst) * alive;
        // clock is "round ran to the end"; trim people still sitting after us.
        done[task.pos] = clock - alive + alive_left.prefix(task.pos);
        alive_left.add(task.pos, -1);
        --alive;
        prev_burst = task.burst;
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << done[i] << '\n';
    }
}
