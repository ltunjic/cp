#include <bits/stdc++.h>

#define X first
#define Y second
#define pii pair<int, int>
#define pb push_back 

using namespace std;

const int N = 3 * 1e5 + 10;
const int INF = 1e9 + 10;

int ans[N], comp[N];
int in[N], diff[N], t;

bool vis[N], cvis[N], isol[N]; 

vector<pii> tout, start;
vector<int> g[2][N], topo[N], fin;

void visAll(int u){
	vis[u] = true;
	for(int v : g[1][u]){
		if(!vis[v]) visAll(v); 
	}
}

void timer(int u){
	vis[u] = true;
	for(int v : g[0][u]){
		if(vis[v]) continue;
		timer(v);
	}	
	tout.pb({t, u});
	t++;
}

void scc(int u, int p){ 
	vis[u] = true;
	comp[u] = p;
//	printf("%d\n", u);
	for(int v : g[1][u]){
		if(vis[v]){
			if(comp[v] != p) topo[comp[v]].pb(p);
			continue;
		}
		scc(v, p);
	}
} 

int rec(int u){
	if(vis[u]) return 0;
	vis[u] = true;
	int ret = in[u];
	for(int v : topo[u]){
		ret += rec(v);
	} 
//	printf("%d, ret = %d\n", u, ret);
	return ret;
}

int main(){
	int n, m, A, B;
	scanf("%d%d%d%d", &n, &m, &A, &B);
	
	for(int i = 1; i <= n; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		if(x == 0) start.pb({y, i});
		if(x == A) fin.pb(i);
	}
	
	sort(start.begin(), start.end(), [](pii a, pii b) -> bool {return a.X > b.X;});
	
//	for(pii p : start) printf("x = %d y = %d\n", p.X, p.Y);
	
	for(int i = 0; i < m; i++){
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		if(t == 1){
			g[0][u].pb(v);
			g[1][v].pb(u);
		} else {
			g[0][u].pb(v);
			g[1][v].pb(u);
			g[0][v].pb(u);
			g[1][u].pb(v);
		}
	}
	
	for(int u : fin){
		if(vis[u]) continue;
		visAll(u);
	}
	
	for(pii p : start){
		if(!vis[p.Y]) isol[p.Y] = true;
	}
	
	memset(vis, 0, sizeof(vis));
	
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		timer(i);
	}
		
	sort(tout.begin(), tout.end(), [](pii a, pii b) -> bool {return a.X > b.X;});
	
	memset(vis, 0, sizeof(vis));	
		
	int cnt = 0; 
	for(pii p : tout){
		if(vis[p.Y]) continue;
		cnt++;
//		printf("new head: %d\n", cnt);
		scc(p.Y, cnt);
	}
		
	for(int i = 1; i <= cnt; i++) topo[i].erase(unique(topo[i].begin(), topo[i].end()), topo[i].end());
	
	for(int u : fin) in[comp[u]]++;
	
	memset(vis, 0, sizeof(vis));	
			
	for(int i = start.size() - 1; i >= 0; i--){
		int u = start[i].Y;
		if(isol[u]) continue;
		diff[u] = rec(comp[u]);	
//		printf("u = %d diff = %d\n", comp[u], diff[u]);
	}	
	
	memset(vis, 0, sizeof(vis));
	
	int res = 0;
	for(pii p : start){
		int u = p.Y;
		if(isol[u]){
			printf("0\n");
			continue;
		}
		res += rec(comp[u]);
		printf("%d\n", res);
		res -= diff[u];
	}
	return 0;
}
