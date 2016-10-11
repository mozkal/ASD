/*
 * prj.cc
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
#include <queue>

#define MAX_PROJECTS 100000

class Vertex {
	public:
		long inc_deg() {
			return ++deg;
		}
		
		long dec_deg() {
			return --deg;
		}
		
		Vertex(long progs) : progs(progs) {
			deg = 0;
		}
		
		void depend(Vertex *v) {
			v->inc_deg();
			neigh.push_back(v);
		}
		
		long get_deg() const {
			return deg;
		} 
		
		long get_progs() const {
			return progs;
		}
		
		std::vector<Vertex *> rm() {
			std::vector<Vertex *> ret;
			
			for(Vertex *v : neigh) {
				if(v->dec_deg() == 0)
					ret.push_back(v);
			}
			
			return ret;
		}
		
	private:
		long deg;
		long progs;
		std::vector<Vertex *> neigh;
};	

struct CompareVertex {
    bool operator()(Vertex const &lhs, Vertex const &rhs) {
        return lhs.get_progs() > rhs.get_progs();
    }
};

typedef std::priority_queue<Vertex,std::vector<Vertex>, CompareVertex> mypq_type;

int main() {
	mypq_type q;
	std::vector<Vertex> projects;
	long n, m, k, max_p = 0, count = 0;
	
	scanf("%ld %ld %ld", &n, &m, &k);
	
	for(long i = 0; i < n; i++) {
		long p;
		scanf("%lu", &p);
		projects.emplace_back(p);
	}
	
	for(long i = 0; i < m; i++) {
		long a, b;
		scanf("%lu %lu", &a, &b);
		Vertex &v = projects.at(a - 1);
		Vertex &u = projects.at(b - 1);
		u.depend(&v);
	}
	
	for(Vertex &v : projects)
		if(v.get_deg() == 0)
			q.push(v);

	while(count < k && q.size() > 0) {
		Vertex v = q.top();
		q.pop();
		++count;
		long progs = v.get_progs();
		if(progs > max_p)
			max_p = progs;
		std::vector<Vertex *> ret;
		ret = v.rm();
		for(Vertex *v : ret)
			q.push(*v);
	}
	
	std::cout << max_p;
	
	return 0;
}

