#include <iostream>
#include <utility>

#define MAX_N 4000000
#define BIALY 1
#define CZARNY -1
#define MIESZANY 0

long d[2 * MAX_N];
long n;
long M = 1;

long query(long v, long size) {
    if(size < 1)
        return 0;

    if(d[v] == BIALY)
        return size;
    else if(d[v] == CZARNY)
        return 0;
    else
        return query(2 * v, size / 2) + query(2 * v + 1, size / 2);
}

int insert(long a, long b, long v, long l, long p, int value, long &ret, long size) {
    if(d[v] == value) {
        ret = 0;
        return value;
    }

    if(l == a && p == b && d[v] != MIESZANY) {
        if(d[v] == BIALY && value == CZARNY)
            ret = -size;
        else if(d[v] == CZARNY && value == BIALY)
            ret = size;

        d[v] = value;
        return value;
    }
    
    if(d[v] == -value) {
        d[2 * v] = d[v];
        d[2 * v + 1] = d[v];
    }

    long s = (l + p) / 2;
    long lewy, prawy;
    long ret_l, ret_r;
    if(s < a) {
        lewy = d[2 * v];
        ret_l = 0;
        prawy = insert(a, b, 2 * v + 1, s + 1, p, value, ret_r, size / 2);
    } else if(b <= s) {
        lewy = insert(a, b, 2 * v, l, s, value, ret_l, size / 2);
        prawy = d[2 * v + 1];
        ret_r = 0;
    } else {
        lewy = insert(a, s, 2 * v, l, s, value, ret_l, size / 2);
        prawy = insert(s + 1, b, 2 * v + 1, s + 1, p, value, ret_r, size / 2);
    }

    ret = ret_l + ret_r;
    if(lewy == prawy)
        d[v] = lewy;
    else 
        d[v] = MIESZANY;

    return d[v];
}

int main() {
    long m;

    std::cin >> n;
    std::cin >> m;

    while(M < n)
        M *= 2;

    for(long i = 0; i < 2 * M; i++)
        d[i] = CZARNY;
    //std::cout << n << "|" << m << "@";
    long ret = 0;
    long ret_curr;
    for(long i = 0; i < m; i++) {
        long a, b;
        char c;
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        if(c == 'B')
            insert(a, b, 1, 1, M, BIALY, ret_curr, M);
        if(c == 'C')
            insert(a, b, 1, 1, M, CZARNY, ret_curr, M);

        ret += ret_curr;
        std::cout << ret << "\n";//query(1, M) << "\n";
        //std::cout << a << "|" << b << "|" << c << "@";
    }

    return 0;
}