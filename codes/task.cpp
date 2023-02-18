#include <cstdio>
#include <vector>
#include <algorithm>

#define X first
#define Y second 
#define pb push_back 

using namespace std; 

typedef pair<int, int> pii; 
typedef long long ll; 

const int N = 5e4 + 10; 
const int INF = 1e9; 

struct point {
	ll x, y;
	point () : x(0), y(0) {}
	bool operator< (const point &a) const {return x < a.x || x == a.x && y > a.y;}
	bool operator== (const point &a) const {return x == a.x && y == a.y;}
};

bool ccw(point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) >= 0;
}

int n, m; 

vector<pii> g[N]; 
vector<point> ch[N], cur; 

// void debug(vector<point> &v) {
// 	for(point p : v) printf("(%lld, %lld) ", p.x, p.y);
// 	printf("\n"); 
// }

void construct() { 
	ch[1].pb(point()); 
	for(int u = 2; u <= n; u++) {
		cur.clear(); 
		for(pii e : g[u]) {
			int w = e.X;
			int b = e.Y; 
			for(point p : ch[w]) {
				if(b) p.y++; 
				else p.x++; 
				cur.pb(p); 
			}
		}
		sort(cur.begin(), cur.end()); 
		//if(u == 5) debug(cur);
		for(point p : cur) {
			//if(u == 5 && p.x == 2) printf("%d\n", ccw(ch[u].end()[-2], p, ch[u].end()[-1]));
			while((int) ch[u].size() >= 2 && ccw(ch[u].end()[-2], p, ch[u].end()[-1])) 
				ch[u].erase(ch[u].end() - 1); 
			ch[u].pb(p); 
		}
		//debug(ch[u]);
	}
}

ll eval(ll a, ll b, point p) {
	return a * p.x + b * p.y; 
}

ll solve(ll a, ll b, int u) {
	int lo = 0, hi = ch[u].size(); 
	while(hi - lo > 1) { 
		int mi = (lo + hi) / 2;
		if(eval(a, b, ch[u][mi]) > eval(a, b, ch[u][mi - 1])) 
			hi = mi; 
		else 
			lo = mi; 
	}
	return eval(a, b, ch[u][lo]); 
}

int main() {
	scanf("%d%d", &n, &m); 
	for(int i = 0; i < m; i++) { 
		int a, b, c; 
		scanf("%d%d%d", &a, &b, &c); 
		g[b].pb({a, c});
	}

	construct(); 

	int q; 
	scanf("%d", &q); 
	for(int i = 0; i < q; i++) {
		ll a, b; 
		int x;
		scanf("%lld%lld%d", &a, &b, &x); 
		printf("%lld\n", solve(a, b, x));  
	}
	return 0; 
}