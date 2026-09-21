#include <iostream>
int tc, n, sum;

int main () {
    std::cin >> tc;
    while (tc--) {
        std::cin >> n;
        sum += (n > 0 ? n : 0);
    }
    std::cout << sum;
}