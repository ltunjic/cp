#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

#define pb push_back

using namespace std;

typedef long long ll; 

const int N = 1510; 
const int MOD = 998244353;

inline int add(int a, int b) {
	return (ll) (a + b) % MOD;
}

inline int mult(int a, int b) {
	return (ll) a * b % MOD; 
}

int n, COST[N][N], last = 1; 
int dp[N][N], H[N], MX[N], newdp[N]; 

vector<int> C[N];
vector<pair<int, pii>> E; 

set<int> MN[N];

int Find(int u) {
	if(H[u] == u) return u; 
	return H[u] = Find(H[u]); 
} 

void Union(int u, int v) {
	u = Find(u); 
	v = Find(v); 
	if(u == v) return; 

	if((int) C[u].size() < (int) C[v].size()) swap(u, v); 
	
	H[v] = u; 
	MX[u] = max(MX[u], MX[v]); 
	memset(newdp, 0, sizeof(newdp)); 

	for(int i = 0; i <= (int) C[u].size(); i++)
		for(int j = 0; j <= (int) C[v].size(); j++) {
			newdp[i + j] = add(newdp[i + j], mult(dp[u][i], dp[v][j])); 
			if(i < (int) C[u].size() && j < (int) C[v].size()) {
				int a = C[u][i], b = C[v][j]; 
				MN[a].erase(COST[a][b]);
				MN[b].erase(COST[b][a]);  
				MX[u] = max(MX[u], COST[a][b]); 
			}
		}
	for(int w : C[v]) C[u].pb(w); 
	int mn = MOD; 
	for(int i = 0; i <= (int) C[u].size(); i++) {
		dp[u][i] = newdp[i]; 
		if(i < (int) C[u].size()) {
			int w = C[u][i]; 
			if(!MN[w].empty()) mn = min(mn, *(MN[w].begin()));
		}
	}
	if(mn > MX[u]) dp[u][1] = add(dp[u][1], 1); 
	last = u; 
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%d", &COST[i][j]);
			if(i != j) {
				MN[i].insert(COST[i][j]); 
				E.pb({COST[i][j], {i, j}}); 
			}
		}
		dp[i][1] = 1;
		dp[i][0] = 0;
		H[i] = i;
		C[i].pb(i); 
	}
	sort(E.begin(), E.end());
	for(pair<int, pii> p : E) Union(p.Y.X, p.Y.Y); 
	for(int i = 1; i <= n; i++)
		printf("%d ", dp[last][i]);
	printf("\n");
	return 0;
}
