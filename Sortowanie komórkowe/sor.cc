#include <iostream>
#include <vector>

#define LEFT 0
#define RIGHT 1
#define BILLION 1000000000

long T[1000][1000][2];

long SOR_left(std::vector<int> m, int i, int j);
long SOR_right(std::vector<int> m, int i, int j);
long SOR(std::vector<int> m);

long SOR_left(std::vector<int> m, int i, int j) {
    long result = T[i][j][LEFT];

    if(result >= 0)
        return result;

    int last = (i > 0 ? m.at(i - 1) : 0);
    long s_left = 0, s_right = 0;    
    if(i > j)
        result = 0;
    else if(i == j)
        result = last < m.at(i) ? 1 : 0;
    else {
        if(last < m.at(i))
            s_left = SOR_left(m, i + 1, j) % BILLION;

        if(last < m.at(j))
            s_right = SOR_right(m, i, j - 1) % BILLION;

        result = (s_left + s_right) % BILLION;
    }

    T[i][j][LEFT] = result;
    return result;
}

long SOR_right(std::vector<int> m, int i, int j) {
    long result = T[i][j][RIGHT];

    if(result >= 0)
        return result;

    int last = (j < m.size() - 1 ? m.at(j + 1) : m.size() + 1);
    long s_left = 0, s_right = 0;    
    if(i > j)
        result = 0;
    else if(i == j)
        result = last > m.at(j) ? 1 : 0;
    else {
        if(last > m.at(i))
            s_left = SOR_left(m, i + 1, j) % BILLION;
        if(last > m.at(j))
            s_right = SOR_right(m, i, j - 1) % BILLION;

        result = (s_left + s_right) % BILLION;
    }

    T[i][j][RIGHT] = result;
    return result;
}

long SOR(std::vector<int> m) {
    return SOR_left(m, 0, m.size() - 1);// + SOR_right(m, 0, m.length() - 1);
}

int main() {
    long n;
    std::vector<int> m;
    int d;

    std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> d;
        m.push_back(d);
    }

    for(int i = 0; i < 1000; i++)
        for(int j = 0; j < 1000; j++)
            for(int k = 0; k < 2; k++)
                T[i][j][k] = -1;

    std::cout << SOR(m);

    return 0;
}
