#include <cstdio>
#include <utility>
#include <algorithm>

int knapsack (int m, int n, std::pair<int, int> bags[]) {
    int rucksack[n+1][m+1];
    
    for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) {
        if (i == 0 || j == 0)
            rucksack[i][j] = 0;
        else if (bags[i-1].first <= j)
            rucksack[i][j] = std::max (bags[i-1].second + rucksack[i-1][j-bags[i-1].first], rucksack[i-1][j]);
        else
            rucksack[i][j] = rucksack[i-1][j];
    }
    
    return rucksack[n][m];
}

int main (int argc, char const *argv[]) {
    int tc, m, n;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &m, &n);
        std::pair<int, int> bags[n];
        for (int i = 0; i < n; i++) scanf ("%d %d", &bags[i].first, &bags[i].second);
        printf ("Hey stupid robber, you can get %d.\n", knapsack (m, n, bags));
    }
    
    return 0;
}