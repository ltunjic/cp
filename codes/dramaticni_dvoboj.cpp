#include <bits/stdc++.h> 

#define Y first
#define X second
#define pb push_back

using namespace std; 

typedef pair<int, int> pii;

const int LOG = 17;
const int OFF = 1 << LOG;

int n, k, S[OFF << 1], D[OFF << 1], use[OFF];
int grundy[OFF << 1], tour[OFF << 1], base[LOG];  

vector<int> srt;
vector<int> space;
vector<int> g[OFF]; 

void update(int x, int val){
	x += OFF;
	tour[x] = val;
	x >>= 1; 
	while(x){
		tour[x] = max(tour[x << 1], tour[(x << 1) + 1]);
		x >>= 1;
	}
}

int query(int x, int a, int b, int l = 0, int r = OFF){
	if(b <= l || r <= a) return -1;
	if(a <= l && r <= b) return tour[x];
	int mid = (l + r) >> 1;
	return max(query(x << 1, a, b, l, mid), query((x << 1) + 1, a, b, mid, r));
}

bool comp(int a, int b){
	return (S[a] < S[b] || (S[a] == S[b] && D[a] > D[b]) || (S[a] == S[b] && D[a] == D[b] && a < b));
}

void rec(int u){
	use[u]++;
	for(int v : g[u]) rec(v); 
}

void add(int ind, int a){
	while(a && base[__lg(a)] != -1){
		g[ind].pb(base[__lg(a)]);	
		a ^= space[base[__lg(a)]];
	}
	if(a) base[__lg(a)] = ind; 
	space.pb(a);
}

int main(){
	memset(tour, -1, sizeof(tour));
	memset(base, -1, sizeof(base));
	
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &S[i], &D[i]);
		S[i + n] = D[i];
		D[i + n] = S[i];
		srt.pb(i);
		srt.pb(i + n); 
	}
	sort(srt.begin(), srt.end(), comp);
	for(int a : srt){
		grundy[a] = query(1, 0, D[a]) + 1;
		if(a < n)
			update(D[a], grundy[a]);
	}
	
	int xr = 0, a;
	for(int i = 0; i < k; i++){ 
		scanf("%d", &a);
		xr ^= grundy[a - 1];
		add(i, grundy[a - 1] ^ grundy[a - 1 + n]);
	}
	add(k, xr);
	
	if(space.back() != 0) printf("nemoguce\n");
	else{
		rec(k);
		for(int i = 0; i < k; i++) printf("%d", use[i] & 1);
		printf("\n");
	}
	return 0;
}	
