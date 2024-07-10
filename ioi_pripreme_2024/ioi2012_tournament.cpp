#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm> 
#include <set>

#define X first
#define Y second
#define PB push_back

using namespace std; 

typedef pair<int, int> pii;

const int LOG = 17;
const int N = 1 << LOG;

int n, m, s, K[N], L[N], R[N];

int MAX[2 * N];

void update(int x, int w) { 
	x += N;
	MAX[x] = w;
	for(x >>= 1; x; x >>= 1) { 
		MAX[x] = max(MAX[2 * x], MAX[2 * x + 1]);
	}
}

int query(int l, int r, int x = 1, int lo = 0, int hi = N) {
	if(r <= lo || hi <= l) { return -1; }
	if(l <= lo && hi <= r) { return MAX[x]; }
	int mi = (lo + hi) / 2;
	return max(query(l, r, 2 * x, lo, mi), query(l, r, 2 * x + 1, mi, hi));
}

set<pii> S;
vector<int> swp[N][2];

int G[N], T[2 * N], P[2 * N];

void propagate(int u) { 
	if(P[u] == 0) { return; }
	T[2 * u] = T[2 * u + 1] = 0;
	P[2 * u] = P[2 * u + 1] = 1;
	P[u] = 0;
}

void update2(int x, int w, int u = 1, int lo = 0, int hi = N) { 
	if(lo + 1 == hi) { 
		T[u] = 1;
		G[x] = w;
		P[u] = 0;
		return;
	}

	propagate(u);
	int mi = (lo + hi) / 2;
	if(x < mi) { update2(x, w, 2 * u, lo, mi); }
	else { update2(x, w, 2 * u + 1, mi, hi); }
	
	T[u] = T[2 * u] + T[2 * u + 1];
}

void update3(int l, int r, int u = 1, int lo = 0, int hi = N) {
	if(r <= lo || hi <= l) { return; }
	if(l <= lo && hi <= r) { 
		T[u] = 0;
		P[u] = 1;
		return;
	}
	propagate(u);
	int mi = (lo + hi) / 2;
	update3(l, r, 2 * u, lo, mi);
	update3(l, r, 2 * u + 1, mi, hi);
	T[u] = T[2 * u] + T[2 * u + 1];
}

int get(int x, int u = 1, int lo = 0, int hi = N) { 
	if(lo + 1 == hi) { return u - N; }
	propagate(u);
	int mi = (lo + hi) / 2;
	
	if(x < T[2 * u]) { return get(x, 2 * u, lo, mi); }
	return get(x - T[2 * u], 2 * u + 1, mi, hi);
}

int GetBestPosition(int nn, int cc, int rr, int *kk, int *ss, int *ee) {
	memset(T, 0, sizeof(T));
	memset(P, 0, sizeof(P));

	n = nn;		
	m = cc;
	s = rr;
	for(int i = 0; i < n - 1; ++i) { 
		K[i] = kk[i]; 
		update(i, K[i]);

		S.insert({i, i});
		update2(i, i);
	}
	S.insert({n - 1, n - 1});
	update2(n - 1, n - 1);

	for(int i = 0; i < m; ++i) { 
		int l = ss[i], r = ee[i];

		int lb = get(l); 
		auto it = S.lower_bound({lb, G[lb]});
		for(int j = l; j <= r; ++j) { 
			assert(it != S.end());
			auto it_ = next(it);
			if(j == l) { L[i] = it->X; }
			if(j == r) { R[i] = it->Y; }
			S.erase(it);
			it = it_;
		}

		update3(L[i], R[i] + 1);
		update2(L[i], R[i]);

//		printf("%d %d %d %d\n", L[i], R[i], l, r);
		swp[L[i]][0].PB(i);
		swp[R[i]][1].PB(i);
		S.insert({L[i], R[i]});
	} 

	int ans = -1, ind = 0, cnt = 0;
	for(int i = 0; i < n; ++i) { 
		for(int x : swp[i][0]) {
			if(query(L[x], R[x]) < s) { ++cnt; /*printf("%d %d %d\n", L[x], R[x], query(L[x], R[x]));*/ }
		}
		
		if(ans < cnt) { 
			ans = cnt;
			ind = i;
		}

		for(int x : swp[i][1]) {
			if(query(L[x], R[x]) < s) { --cnt; }
		}
	}
//	printf("%d\n", ans);
 	return ind;
}
