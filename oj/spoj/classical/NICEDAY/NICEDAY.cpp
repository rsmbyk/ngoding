#include <iostream>
#include <vector>

struct FenwickMin {
    std::vector<int> tree;
    int inf;

    FenwickMin(int n, int inf) : tree(n + 1, inf), inf(inf) {}

    void set(int i, int val) {
        for (; i < static_cast<int>(tree.size()); i += i & -i) {
            tree[i] = std::min(tree[i], val);
        }
    }

    int prefix_min(int i) const {
        int ans = inf;
        for (; i > 0; i -= i & -i) {
            ans = std::min(ans, tree[i]);
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;

        // Contest-1 rank is a permutation, so slot each person by that rank
        // and walk 1…N instead of sorting.
        std::vector<int> contest2(n + 1);
        std::vector<int> contest3(n + 1);
        for (int i = 0; i < n; ++i) {
            int a, b, c;
            std::cin >> a >> b >> c;
            contest2[a] = b;
            contest3[a] = c;
        }

        const int inf = n + 1;
        FenwickMin best3(n, inf);
        int excellent = 0;
        for (int a = 1; a <= n; ++a) {
            const int b = contest2[a];
            const int c = contest3[a];
            // prefix_min(b - 1): best contest-3 among people already seen
            // with a strictly better contest-2 rank. b == 1 → empty → inf.
            if (best3.prefix_min(b - 1) > c) {
                ++excellent;
            }
            best3.set(b, c);
        }
        std::cout << excellent << '\n';
    }
}
