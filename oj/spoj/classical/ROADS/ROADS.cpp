#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Road {
    int to;
    int length;
    int toll;
};

struct Place {
    int length;
    int city;
    int coins;
};

struct ShorterLength {
    bool operator()(const Place& left, const Place& right) const {
        return left.length > right.length;
    }
};

// One place is a city plus the coins already spent. The heap grows by length.
static int shortest_affordable(int city_count, int budget,
                               const std::vector<std::vector<Road>>& roads) {
    constexpr int kUnreached = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> best(
        city_count + 1, std::vector<int>(budget + 1, kUnreached));
    std::priority_queue<Place, std::vector<Place>, ShorterLength> open;

    best[1][0] = 0;
    open.push({0, 1, 0});

    while (!open.empty()) {
        const Place here = open.top();
        open.pop();
        // Same city and same coins: a longer road is worse on both.
        if (here.length != best[here.city][here.coins]) {
            continue;
        }
        // Length order, so the first time city N is settled nothing shorter is waiting.
        if (here.city == city_count) {
            return here.length;
        }
        for (const Road& road : roads[here.city]) {
            const int spent = here.coins + road.toll;
            if (spent > budget) {
                continue;
            }
            const int arrived = here.length + road.length;
            if (arrived < best[road.to][spent]) {
                best[road.to][spent] = arrived;
                open.push({arrived, road.to, spent});
            }
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests;
    std::cin >> tests;
    while (tests--) {
        int budget, city_count, road_count;
        std::cin >> budget >> city_count >> road_count;
        std::vector<std::vector<Road>> roads(city_count + 1);
        for (int i = 0; i < road_count; ++i) {
            int from, to, length, toll;
            std::cin >> from >> to >> length >> toll;
            roads[from].push_back({to, length, toll});
        }
        std::cout << shortest_affordable(city_count, budget, roads) << '\n';
    }
}
