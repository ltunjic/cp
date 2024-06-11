#include <cstdio> 
#include <vector>
#include <cstring>
#include <algorithm> 

#define PB push_back

using namespace std;

const int MOD = 1e9 + 7;
const int LOG = 21;
const int N = 1 << LOG; 
const int OO = 2e9;

int T[2 * N][2]; 

void reset() {
	for(int i = 0; i < 2 * N; ++i) { 
		T[i][0] = OO;
		T[i][1] = -OO;
	}
}

void update(int u, int w) {
	u += N; 
	T[u][0] = T[u][1] = w;
	if(w == -1) { T[u][0] = OO; T[u][1] = -OO; }
	for(u >>= 1; u; u >>= 1) {
		T[u][0] = min(T[2 * u][0], T[2 * u + 1][0]);
		T[u][1] = max(T[2 * u][1], T[2 * u + 1][1]);
	}
}

int qmax(int l, int r, int u = 1, int lo = 0, int hi = N) { 
	if(r <= lo || hi <= l) { return -OO; }
	if(l <= lo && hi <= r) { return T[u][1]; }
	int mi = (lo + hi) / 2;
	return max(qmax(l, r, 2 * u, lo, mi), qmax(l, r, 2 * u + 1, mi, hi));
}

int qmin(int l, int r, int u = 1, int lo = 0, int hi = N) { 
	if(r <= lo || hi <= l) { return OO; }
	if(l <= lo && hi <= r) { return T[u][0]; }
	int mi = (lo + hi) / 2;
	return min(qmin(l, r, 2 * u, lo, mi), qmin(l, r, 2 * u + 1, mi, hi));
}

int L[N], R[N], C[N], O[N];
vector<int> V[2]; 

void dfs(int u) {
	V[C[u]].PB(u);
	update(L[u], -1);
	update(R[u], -1);
	for(int v = qmax(L[u] + 1, R[u]); v > R[u]; v = qmax(L[u] + 1, R[u])) { 
		v = O[v];
//		printf("max %d %d\n", u, v);
		C[v] = !C[u]; 
		dfs(v);
	}

	for(int v = qmin(L[u] + 1, R[u]); v < L[u]; v = qmin(L[u] + 1, R[u])) { 
		v = O[v];
//		printf("min %d %d\n", u, v);
		C[v] = !C[u]; 
		dfs(v);
	}
}

int main() {
	memset(C, -1, sizeof(C));
	reset();	

	int n; scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", L + i, R + i);
		update(L[i], R[i]);
		update(R[i], L[i]);
		O[L[i]] = O[R[i]] = i;
	}

	int ans = 1;

	for(int i = 0; i < n; ++i) {
		if(C[i] == -1) { 
			C[i] = 0;
			ans = (ans * 2) % (MOD);
			dfs(i);
		}
	}

	reset();
	for(int i : V[1]) { 
		update(L[i], R[i]);
		update(R[i], L[i]);
	}

	for(int i : V[1]) { 
		int nim = qmin(L[i] + 1, R[i]), xam = qmax(L[i] + 1, R[i]);
		if(nim < L[i] || xam > R[i]) { ans = 0; }
	}

	reset();
	for(int i : V[0]) { 
		update(L[i], R[i]);
		update(R[i], L[i]);
	}

	for(int i : V[0]) { 
		int nim = qmin(L[i] + 1, R[i]), xam = qmax(L[i] + 1, R[i]);
		if(nim < L[i] || xam > R[i]) { ans = 0; }
	}

	printf("%d\n", ans);
	return 0;
}
