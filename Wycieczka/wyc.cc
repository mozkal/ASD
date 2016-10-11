#include <cstring>
#include <cstdio>
#include <iostream>

#define INFINITY 1005000000
#define MAX_K 1002


int main() {
    int n, k;
    //Train i Plane [i] to koszt z i do i + 1
    int Taxi[1002] = {};
    int Train[1002] = {};
    int Plane[1002] = {};


    scanf("%d %d", &n, &k);
    if(k % 2 == 0)
        --k;
    scanf("%d", &Taxi[0]);
    for(int i = 1; i <= n; i++)
        scanf("%d %d %d", &Train[i - 1], &Taxi[i], &Plane[i - 1]);

    //suma do i-tego elementu WYŁĄCZNIE, czyli koszt przejazdu z miasta 0 do miasta i bez przesiadek
    long prefix_t[n + 1];
    long prefix_p[n + 1];

    prefix_t[0] = 0;
    prefix_p[0] = 0;
    for(int i = 1; i <= n; i++) {
        prefix_t[i] = Train[i - 1] + prefix_t[i - 1];
        prefix_p[i] = Plane[i - 1] + prefix_p[i - 1];
    }


    long (*Route)[MAX_K / 2] = new long[n + 1][MAX_K / 2]();
    long (*Prev_Route)[MAX_K / 2] = new long[n + 1][MAX_K / 2]();

    //0 przesiadek
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n / 2; j++)
            Route[i][j] = (j == 0) ? prefix_p[n] - prefix_p[i] : -1;

    long global_min = INFINITY;
    long (*temp)[MAX_K / 2];
    long min;
    for(int l = 1; l <= k; l++) {
        temp = Prev_Route;
        Prev_Route = Route;
        Route = temp;

        for(int i = n; i >= 0; i--) {
            if(l % 2 != 0) {
                for(int j = 0; j <= n / 2; j++) {
                    long route1;
                    if(i == n) {
                        route1 = INFINITY;
                    } else if(j > 0)
                        route1 = (Route[i + 1][j - 1] >= 0) ? Train[i] + Route[i + 1][j - 1] : INFINITY;
                    else
                        route1 = INFINITY;

                    long route2 = (Prev_Route[i][j] >= 0) ? Taxi[i] + Prev_Route[i][j] : INFINITY;
                    min = route1 <= route2 ? route1 : route2;
                    Route[i][j] = (min < INFINITY) ? min : -1;
                }
            } else {
                for(int j = 0; j <= n / 2; j++) {
                    long route1;
                    if(i == n)
                        route1 = INFINITY;
                    else
                        route1 = Route[i + 1][j] >= 0 ? Plane[i] + Route[i + 1][j] : INFINITY;

                    long route2 = (Prev_Route[i][j] >= 0) ? Taxi[i] + Prev_Route[i][j] : INFINITY;
                    min = route1 <= route2 ? route1 : route2;
                    Route[i][j] = (min < INFINITY) ? min : -1;
                }
            }
        }
        if(l % 2 != 0) {
            long cand = Route[0][n / 2];
            if(cand >= 0 && cand < global_min) {
                global_min = cand;
            }
        }
    }

    delete Route;
    delete Prev_Route;

    printf("%ld", global_min);
    return 0;
}