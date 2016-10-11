/*
 * lex.cc
 * 
 * Copyright 2016 Michał Moskal <michal@Michas-MacBook-Air.local>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <string>

#define MAX_N 	300004
#define P		101
#define Q		50331653

long long h[MAX_N];
long long p[MAX_N];
long n, m;

long long hash(long a, long b) {
	long long tmp = (h[b + 1] * p[b - a + 1]) % Q;
	long long ret = (h[a] - tmp) % Q;

	return ret < 0 ? ret + Q : ret;
}

long find_first(long a, long b, long c, long d) {
//	printf("FIND FIRST %ld %ld %ld %ld\n", a, b, c, d);
	long l = 0;
	long p = b - a <= d - c ? b - a : d - c;
	long s;
	
	while(l != p) {
		s = (l + p) / 2;
		if(hash(a + l, a + s) == hash(c + l, c + s))
			l = s + 1;
		else
			p = s;
	}
	
	//while((a + i <= b) && (c + i <= d) && (((long long) hash(a, a + i)) == ((long long) hash(c, c + i))))
	//	++i;
	if(hash(a + l, a + p) == hash(c + l, c + p))
		return l + 1;
	else
		return l;
}
	
int main() {
	char s_temp[MAX_N];

	std::string s;
	
	scanf("%ld %ld", &n, &m);
	scanf("%s", s_temp);
	s = std::string(s_temp);
	
	for(long i = 0; i < MAX_N; i++) {
		p[i] = 0;
		h[i] = 0;
	}
	
	h[n - 1] = s.at(n - 1);
	p[0] = 1;
	for(long i = n - 2; i >= 0; i--) {
		long long tmp;
		
		tmp = (p[n - 1 - i - 1] * P) % Q;
		p[n - 1 - i] = (tmp < 0) ? tmp + Q : tmp;
		tmp = (P * h[i + 1] + s.at(i)) % Q;
		h[i] = (tmp < 0) ? tmp + Q : tmp;
	}
	//std::cout << s;
	for(long i = 0; i < m; i++) {
		long a, b, c, d;
		scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
		--a; --b; --c; --d;
		long f = find_first(a, b, c, d);
		//printf("FFF %ld\n", f);
		if(a + f > b && c + f > d)
			printf("=\n");
		else if(a + f > b)
			printf("<\n");
		else if(c + f > d)
			printf(">\n");
		else if(s.at(a + f) == s.at(c + f)) {
			printf("4=%ld_%ld_%ld_%ld_%ld:%lld_%lld_%s_%s:%c_%c\n", f, a, b, c, d, hash(a, a+f), hash(c, c+f), s.substr(a, f + 1).c_str(), s.substr(c, f + 1).c_str(), s.at(a+f), s.at(c+f));
		}
		else if(s.at(a + f) > s.at(c + f))
			printf(">\n");
		else if(s.at(a + f) < s.at(c + f))
			printf("<\n");
		else
			printf("NIE DZIALA\n");
	}	
	
	/*for(long i = 0; i <= n - 1; i++) {
		//printf("%lld\n", h[i]);
		printf("%c\n", (s.at(i)));
	}*/

	//printf("%lld_%lld\n", hash(13, 17), hash(4, 8));
	
	//printf("%lld", h[13]);	
	//std::cout << s.substr(13, 5) << " " << s.substr(4, 5);
	/*for(long i = 0; i < n; i++) {
		long x = s.at(i);
		printf("%ld %ld\n", x, i);
	}*/
	
	return 0;
}

