#include "simurgh.h"
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair<int, int> pii;

const int N = 510;
const int M = N * N;

int n, m, uu[M], vv[M];
vector<pii> g[N];

bool isb[M];
vector<pii> mst;

int dep[N], mind[N]; // memset(dep)

int dfstree(int u, int p, int pi) { 
	mind[u] = dep[u];
	for(pii e : g[u]) { 
		int v = e.X, i = e.Y;

		if(v != p) { 
			if(dep[v] == -1) { 
				dep[v] = dep[u] + 1;
				mind[u] = min(mind[u], dfstree(v, u, i));
			} else if( dep[v] < dep[u]) { 
				mind[u] = min(mind[u], dep[v]);
			}
		}
	}
	
	if(pi != -1 && mind[u] >= dep[u]) { 
		mst.PB({pi, 1});
		isb[pi] = 1;
	}

	return mind[u];
}

void bridge() { 
	memset(dep, -1, sizeof(dep));
	dep[0] = 0;
	dfstree(0, -1, -1);
}

int un[N], siz[N];

void clear() { 
	memset(un, -1, sizeof(un));
	for(int i = 0; i < n; ++i) { 
		siz[i] = 1;
	}
}

int trazi(int u) { return un[u] == -1 ? u : un[u] = trazi(un[u]); }
bool unija(int u, int v) { 
	u = trazi(u);
	v = trazi(v);
	if(u == v) { return 0; }

	if(siz[u] < siz[v]) { swap(u, v); }
	un[v] = u;
	siz[u] += siz[v];
	return 1;
}

vector<int> qry;

int fillup(vector<int> &e, bool f) { 
	clear();
	qry.clear();
	int ret = 0;

	for(int i : e) { 
		unija(uu[i], vv[i]);
		qry.PB(i);
	}

	if(f == 0) { 
		for(int i = 0; i < m; ++i) { 
			if(unija(uu[i], vv[i])) { 
				qry.PB(i);
			}
		}
	} else { 
		for(pii i : mst) { 
			if(unija(uu[i.X], vv[i.X])) { 
				qry.PB(i.X);
				ret += i.Y;
			}
		}
	}
	return ret;
}

int bio[N], bioe[M], val[M];
vector<int> tmp, cp, pth;

void comp(int u) { 
	if(bio[u] != -1) { return; }
	bio[u] = 0;
	cp.PB(u);

	for(pii e : g[u]) { 
		if(!isb[e.Y]) { 
			comp(e.X);
		}
	}
}

bool tried[N];
int spec[2], sp;

bool dfs(int u) {
	bio[u] = 1;
	tried[u] = 1;
	for(pii e : g[u]) { 
		int v = e.X, i = e.Y;
		if(!isb[i] && !bioe[i] && bio[v] != 1 && !tried[v]) { 
			tmp.PB(i);
			bioe[i] = 1;
			if(bio[v] == 2) { 
				spec[sp] = v;
				return 1;
			} else {
				if(dfs(v)) { 
					return 1; 
				}
				bioe[i] = 0;
				tmp.pop_back();
			}
		}
	}
	bio[u] = 0;
	return 0;
}

bool path(int u, int t, int pr = -1) { 
	if(u == t) { return 1; }
	bool ret = 0;
	for(pii p : g[u]) { 
		int v = p.X, ind = p.Y;
		if(v != pr && !isb[ind] && bioe[ind] == 1 && bio[v] == 2) { 
			if(path(v, t, u)) { 
				pth.PB(ind);
				return 1;
			}
		}
	}
	return 0;
}

void cycle(vector<int> &e) {
	pth.clear();
	path(spec[0], spec[1]);
	int f = -1;
	for(int i = 0; i < pth.size(); ++i) {
		if(val[pth[i]] == 0) { 
			f = i;
		}
	}

	int xam = -1;
	if(f != -1) { 
		vector<int> fu;
		for(int i = 0; i < pth.size(); ++i) { 
			if(i != f) {
				fu.PB(pth[i]);
			}
		}
		for(int i : e) { 
			fu.PB(i);
		}
		fillup(fu, 0);

		xam = count_common_roads(qry);
	}

	vector<pii> res;
	for(int i = 0; i < e.size(); ++i) { 
		vector<int> fu;
		for(int j : pth) {
			fu.PB(j);
		}
		for(int j = 0; j < e.size(); ++j) { 
			if(j != i) {
				fu.PB(e[j]);
			}
		}
		
		fillup(fu, 0);
		res.PB({e[i], count_common_roads(qry)});
		xam = max(xam, res.back().Y);
	}

	for(int i = 0; i < (int) res.size() - 1; ++i) { 
		mst.PB({res[i].X, xam - res[i].Y});
		val[res[i].X] = xam - res[i].Y;
	}
	bioe[res.back().X] = 0;
}

void ear() {
	memset(bio, -1, sizeof(bio));

	for(int i = 0; i < n; ++i) { 
		if(bio[i] == -1) { 
			cp.clear();
			comp(i);
			bio[i] = 2;

			for(int j : cp) { 
				if(bio[j] != 2) {
					tmp.clear();
					memset(tried, 0, sizeof(tried));
					sp = 0; dfs(j); 
					memset(tried, 0, sizeof(tried));
					sp = 1; dfs(j);
					
					cycle(tmp);

					for(int k : tmp) { 
						bio[uu[k]] = 2;
						bio[vv[k]] = 2;
					}
				}
			}
		}
	}
}

bool ans[M];
int deg[N], cnt = 0;

int query(vector<int> &q) {
	int d = fillup(q, 1);
	return count_common_roads(qry) - d;
}

int leaf(int u) { 
	vector<int> ng;	
	for(pii e : g[u]) { 
		if(!ans[e.Y]) { 
			ng.PB(e.Y); 
		}
	}

	for(; ng.size() > 1; ) {
		vector<int> q;
		
		int k = (ng.size() + 1) / 2;
		for(int i = 0; i < k; ++i) { 
			q.PB(ng[i]);
		}

		if(query(q)) { 
			ng.erase(ng.begin() + k, ng.end());
		} else {
			ng.erase(ng.begin(), ng.begin() + k);
		}
	}

	return ng[0];
}

vector<int> find_roads(int nn, vector<int> A, vector<int> B) {
	n = nn;
	m = A.size();
	for(int i = 0; i < m; ++i) { 
		uu[i] = A[i];
		vv[i] = B[i];
		g[uu[i]].PB({vv[i], i});	
		g[vv[i]].PB({uu[i], i});	
	}

	bridge();
	ear();

	for(int i = 0; i < n; ++i) { 
		vector<int> q;
		for(pii i : g[i]) { 
			q.PB(i.Y);
		}
	
		deg[i] = query(q);
	}

	for(; cnt < n - 1; ) { 
		for(int i = 0; i < n; ++i) { 
			if(deg[i] == 1) { 
				++cnt;
				int ind = leaf(i);
				ans[ind] = 1;
				--deg[uu[ind]];
				--deg[vv[ind]];
			}
		}
	}
	
	vector<int> ret;
	for(int i = 0; i < m; ++i) { 
		if(ans[i]) { 
			ret.PB(i);
		}
	}
	return ret;
}
