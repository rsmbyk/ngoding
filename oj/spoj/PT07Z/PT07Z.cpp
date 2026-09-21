#include <algorithm>
#include <iostream>
#include <vector>

static int longest_path(const std::vector<std::vector<int>>& adj) {
    int answer = 0;

    // Returns the longest single down-chain from u. The two-arm peak at u
    // is a finished path, so it updates answer and is not sent up.
    auto down = [&](auto&& self, int u, int parent) -> int {
        int best = 0;
        int second = 0;
        for (int v : adj[u]) {
            if (v == parent) {
                continue;
            }
            const int offer = 1 + self(self, v, u);
            if (offer > best) {
                second = best;
                best = offer;
            } else if (offer > second) {
                second = offer;
            }
        }
        answer = std::max(answer, best + second);
        return best;
    };

    down(down, 1, 0);
    return answer;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::cout << longest_path(adj) << '\n';
}
