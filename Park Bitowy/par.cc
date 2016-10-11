#include <iostream>
#include <math.h>
#include <cstdio>

#define MAX_N 500003
#define MAX_LOG_N 20

long log_n = -1; //inicjalizowane w main
long farthest_down_d[MAX_N], farthest_down_v[MAX_N], 
	 farthest_up_d[MAX_N], farthest_up_v[MAX_N],
	 farthest_d[MAX_N], farthest_v[MAX_N],
	 ancestors[MAX_N][MAX_LOG_N], depth[MAX_N],
	 left[MAX_N], right[MAX_N], parent[MAX_N], quest_d[MAX_N], quest_v[MAX_N];

long ancestor(long v, long h) {
	long u = v;
	int i = log_n;

	while(h > 0) {
		long p = pow(2, i);
		if(p > h)
			--i;
		else {
			u = ancestors[u][i];
			h -= p;
		}
	}

	return u;
}

long lca(long v, long u) {
	if(depth[u] > depth[v])
		u = ancestor(u, depth[u] - depth[v]);
	else if(depth[u] < depth[v])
		v = ancestor(v, depth[v] - depth[u]);

	if(u == v)
		return u;

	long i = log_n;
	while(i >= 0) {
		if(ancestors[u][i] != ancestors[v][i]) {
			u = ancestors[u][i];
			v = ancestors[v][i];
		}
		--i;
	}
	return parent[u];
}

long far_down(long v, long &dist) {
	if(v == -1) {
		dist = -1;
		return -1;
	} else {
		long dist_l, dist_p;
		long v_l = far_down(left[v], dist_l);
		long v_p = far_down(right[v], dist_p);

		if(dist_p >= dist_l) {
			dist = dist_p + 1;
			v_p = (v_p == -1) ? v : v_p;
			farthest_down_d[v] = dist;
			farthest_down_v[v] = v_p;
			return v_p;
		} else {
			dist = dist_l + 1;
			v_l = (v_l == -1) ? v : v_l;
			farthest_down_d[v] = dist;
			farthest_down_v[v] = v_l;
			return v_l;
		}
	}
}

void far_up(long v) {
	if(v != -1) {
		long dist_p, dist_s;

		if(parent[v] == -1) {
			farthest_up_d[v] = 0;
			farthest_up_v[v] = v;
		} else {
			dist_p = farthest_up_d[parent[v]] + 1;
			if(left[parent[v]] == v)
				dist_s = (right[parent[v]] != -1) ? farthest_down_d[right[parent[v]]] + 2 : 0;
			else
				dist_s = (left[parent[v]] != -1) ? farthest_down_d[left[parent[v]]] + 2 : 0;

			if(dist_p >= dist_s) {
				farthest_up_d[v] = dist_p;
				farthest_up_v[v] = farthest_up_v[parent[v]];
			} else {
				farthest_up_d[v] = dist_s;
				farthest_up_v[v] = (left[parent[v]] == v) ? farthest_down_v[right[parent[v]]] : 
												             farthest_down_v[left[parent[v]]];
			}
		}
		far_up(right[v]);
		far_up(left[v]);
	}
}

long count_depth(long v) {
	if(depth[v] == - 1)
		depth[v] = (parent[v] == -1) ? 0 : count_depth(parent[v]) + 1;

	return depth[v];
}

long vertex(long v, long d) {
	long d_max = farthest_d[v];
	if(d > d_max)
		return -1;
	long u_max = farthest_v[v];
	long l = lca(v, u_max);
	long d1 = depth[v] - depth[l];
	if(d <= d1)
		return ancestor(v, d);
	else
		return ancestor(u_max, d_max - d);
}

int main() {

	long n;
	scanf("%ld\n", &n);
	for(long i = 1; i <= n; i++) {
		long a, b;
		scanf("%ld %ld\n", &a, &b);
		left[i] = a;
		right[i] = b;
		parent[a] = i;
		parent[b] = i;

		depth[i] = -1;
	}
	parent[1] = -1;

	for(long i = 1; i <= n; i++)
		count_depth(i);

	long M = 1;
	while(M <= n) {
		M *= 2;
		log_n += 1;
	}

	for(int k = 0; k <= log_n; k++) {
		for(long i = 0; i <= n; i++) {
			ancestors[i][k] = (k == 0) ? parent[i] : 
			                  (ancestors[i][k - 1] <= 0) ? -1 :
			                   ancestors[ancestors[i][k - 1]][k - 1];
		}
	}


	long dist;
	far_down(1, dist);
	far_up(1);
	for(long i = 1; i <= n; i++) {
		long d_up = farthest_up_d[i];
		long d_down = farthest_down_d[i];

		if(d_up >= d_down) {
			farthest_d[i] = d_up;
			farthest_v[i] = farthest_up_v[i];
		} else {
			farthest_d[i] = d_down;
			farthest_v[i] = farthest_down_v[i];
		}
	}

	long m;
	scanf("%ld\n", &m);
	for(long i = 0; i < m; i++) {
		long v, d;
		scanf("%ld %ld\n", &v, &d);
		quest_v[i] = v;
		quest_d[i] = d;
	}
	for(long i = 0; i < m; i++) {
		printf("%ld\n", vertex(quest_v[i], quest_d[i]));
	}
}
