#include <cstdio> 
#include <vector> 
#include <algorithm> 
#include <unordered_map> 

#define X first
#define Y second
#define PB push_back

using namespace std;	

typedef long long ll;
typedef pair<int, int> pii;

struct hsh {
	size_t operator () (const pii &p) const { return hash<ll>() ((ll) p.X) ^ ((ll) p.Y << 32); }
}; 

const int LOG = 17;
const int N = 1 << LOG;
const int MOD = 1e9;

unordered_map<pii, int, hsh> edg, cp;
vector<int> g[N];

ll ans;
ll sz[N], pod[N], sum;

ll dfs(int u, int p) { 
	pod[u] += sz[u];
	for(int v : g[u]) { 
		if(v != p) {
			pod[u] += dfs(v, u); 
		}
	}
	ans += (sum - pod[u]) * pod[u];
	return pod[u];
}

void edge(int u, int v) { 
	if(edg.count({u, v}) || edg.count({v, u})) {
		return;
	}
	edg[{u, v}] = 1;
	g[u].PB(v);
	g[v].PB(u);
//	printf("%d %d\n", u, v);
}

int n;
vector<int> V[N];

void solve(const vector<int> &X, const vector<int> &Y) {
	edg.clear();
	cp.clear();
	edg.reserve(N);
	cp.reserve(N);
	for(int i = 0; i < N; ++i) { 
		V[i].clear();
		g[i].clear();
		sz[i] = 0;
		pod[i] = 0;
	}

	for(int i = 0; i < n; ++i) {
		V[X[i]].PB(Y[i]);
	}

	int cnt = 0;
	for(int x = 0; x < N; ++x) { 
		sort(V[x].begin(), V[x].end());
		int lst = -5;
		for(int y : V[x]) { 
			if(lst + 1 != y) { 
				++cnt;
			}
			cp[{x, y}] = cnt;
//			printf("%d %d : %d\n", x, y, cnt);
			++sz[cnt];
			
			if(cp.count({x - 1, y})) { 
				edge(cnt, cp[{x - 1, y}]);
			}

			lst = y;
		}
	}

	sum = 0;
	for(int i = 1; i <= cnt; ++i) { 
		sum += sz[i];
	}

	dfs(1, 0);
}

vector<int> vx, vy;

int DistanceSum(int nn, int *xx, int *yy) { 
	n = nn;
	for(int i = 0; i < n; ++i) {
		vx.PB(xx[i]);
		vy.PB(yy[i]);
	}

	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	sort(vy.begin(), vy.end());
	vy.erase(unique(vy.begin(), vy.end()), vy.end());
	
	vector<int> x, y;
	for(int i = 0; i < n; ++i) { 
		x.PB(lower_bound(vx.begin(), vx.end(), xx[i]) - vx.begin());
		y.PB(lower_bound(vy.begin(), vy.end(), yy[i]) - vy.begin());
	}

	solve(x, y);
	solve(y, x);
	return ans % MOD;
}
