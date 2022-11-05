#include <bits/stdc++.h> 

#define X first
#define Y second
#define pb push_back

using namespace std; 

typedef pair<int, int> pii;
typedef long long ll;

const int N = 5 * 1e5 + 10;

int n, m;
int t, deg[N];

bool ban[N], vis[N], timed[N], in[N];

vector<int> g[N], r[N], ans, comp, add;
vector<pii> timeout;
vector<vector<int>> scc;

queue<int> q;

void timer(int u){
	if(timed[u]) return;
	timed[u] = true;
	 
	for(int v : g[u]){
		timer(v);
	}
	timeout.pb({t++, u});
}

void compose(int u){
	if(in[u]) return;
	in[u] = true;
	comp.pb(u);
	for(int v : r[u]){
		compose(v);
	}
}

void kosaraju(){
	for(int i = 1; i <= n; i++) timer(i);
	sort(timeout.begin(), timeout.end(), [](pii a, pii b) -> bool {return a.X > b.X;});
	for(pii p : timeout){
		comp.clear();
		compose(p.Y);
		scc.pb(comp);
	}
}

void erase(int u, bool flag){
	ban[u] = true;
	for(int v : r[u]){
		deg[v]--;
		if(!ban[v] && deg[v] == 0 && flag == true) q.push(v);
	}
}

void include(int u, bool flag){
	ban[u] = true;
	ans.pb(u);
	for(int v : r[u]){
		if(!ban[v]) erase(v, flag);
	}
}

void clean(vector<int>  &comp){
	for(int u : comp){
		if(ban[u] || deg[u] != 0) continue;
		q.push(u);
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		if(!ban[u]) include(u, true);		
	}
}

void bipartite(int u, bool flag){
	if(ban[u] || vis[u]) return;
	if(!flag) add.pb(u);
	vis[u] = true;
	for(int v : g[u]) bipartite(v, !flag); 
}

int main(){
	scanf("%d%d", &n, &m);
	
	
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].pb(v);
		r[v].pb(u);
		deg[u]++;
	}
	
	kosaraju();
	
	for(vector<int> comp : scc){
		clean(comp);
		add.clear();
		for(int u : comp){
			bipartite(u, 0);
		}
		for(int u : add){
			include(u, false);
		}
	}	
	
	printf("%d\n", (int) ans.size());		
	for(int u : ans) printf("%d ", u);
	printf("\n"); 
	return 0;
}
