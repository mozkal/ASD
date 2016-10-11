#include <iostream>

#define MAX_N 40000

int main() {
    long n, m, g;
    long long players[MAX_N];

    std::cin >> n;
    std::cin >> m;

    for(long k = 0; k < n; k++)
        players[k] = 0;

    for(long i = 0; i < m; i++)
        for(long j = 0; j < n; j++) {
            std::cin >> g;
            if(j >= (n / 2))
                players[g - 1] |= (long long) 1 << i;
        }


    for(long i = 0; i < n; i++)
        for(long j = i + 1; j < n; j++)
            if(players[i] == players[j]) {
                std::cout << "NIE";
                return 0;
            }

    std::cout << "TAK";

    return 0;
}
