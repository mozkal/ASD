#include <iostream>
#include <utility>

#define MAX_N 100000
#define BILLION 1000000000

long d[10][2 * MAX_N];
long n;
long M = 1;

long query(int j, long a) {
   long va = M - 1 + a , vb = M - 2 + n;
   if(va > vb)
        return 0;
   /* Skrajne przedziały do rozkładu. */
   long wyn = d[j][va];
   if (va != vb) wyn = (d[j][vb] + wyn) % BILLION;
   /* Spacer aż do momentu spotkania. */
   while ((va - 1) / 2 != (vb - 1) / 2) {
     if (va % 2 == 1) wyn = (wyn + d[j][va + 1]) % BILLION; /* prawa bombka na lewej ścieżce */
     if (vb % 2 == 0) wyn = (wyn + d[j][vb - 1]) % BILLION; /* lewa bombka na prawej ścieżce */
     va = (va - 1) / 2; vb = (vb - 1) / 2;
   }
   return wyn;
}

void insert(int j, long a, long val) { 
   long v = M - 2 + a;
   d[j][v] = (d[j][v] + val) % BILLION;
   while (v != 0) {
     v = (v - 1) / 2;
     d[j][v] = (d[j][2 * v + 1] + d[j][2 * v + 2]) % BILLION;
   }
}

int main() {
    long k;
    long A[MAX_N];


    std::cin >> n;
    std::cin >> k;

    while(M < n)
        M *= 2;

    for(long i = 0; i < n; i++) {
        std::cin >> A[i];
    }


    for(long i = 0; i < 2 * n; i++)
        for(long j = 0; j < 10; j++)
            d[j][i] = 0;


    for(long i = 0; i < n; i++) {
        for(long j = 0; j < k - 1; j++) {
            if(j == 0)
                insert(0, A[i], 1);
            long v = query(j, A[i]);
            insert(j + 1, A[i], v);
        }
    }


    std::cout << query(k - 1, 0);

    //std::cout << n << "|" << k;
    return 0;
}