#include <bits/stdc++.h> 

#define X first
#define Y second
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const int LOG = 17;
const int OFF = 1 << LOG;
const int END = OFF - 1;
const int INF = 2e9;

int n, A[OFF], B[OFF];
int tour[OFF << 1]; 

ll cnt = 0, gr[OFF];
map<ll, ll> mp[OFF];

vector<ll> v;

int merge(int a, int b){
	if(B[a] > B[b]) return a;
	return b;
}

void update(int x, int val){
	x += OFF;
	tour[x] = val;
	x >>= 1;
	while(x){
		tour[x] = merge(tour[x << 1], tour[(x << 1) + 1]);
		x >>= 1;
	}	
}

int query(int x, int l, int r, int lo, int hi){
	if(r <= lo || hi <= l) return END;
	if(l <= lo && hi <= r) return tour[x];
	int mi = (lo + hi) >> 1;
	return merge(query(x << 1, l, r, lo, mi), query((x << 1) + 1, l, r, mi, hi));
}

void debug(int x){
	int val = gr[x];
	printf("1: %d\n", val);
	for(pll p : mp[x]){
		val -= p.Y;
		printf("%lld: %d\n", p.X, val);
	}
}

void divcon(int l, int r, int x){
	if(l > r) return;
	
	int m = query(1, l, r + 1, 0, OFF), y = ++cnt;
		
	if(m - l > r - m){
		divcon(l, m - 1, x);
		divcon(m + 1, r, y);
	} else {
		divcon(l, m - 1, y);
		divcon(m + 1, r, x); 	
	}

	gr[x] += gr[y];
	for(pll p : mp[y]) mp[x][p.X] += p.Y;
	
	ll maxh = A[m] + 1;
	
	while(!mp[x].empty()){
		auto it = mp[x].begin();
		if(it -> X > A[m] + 1 && gr[x] < B[m]) break;
		gr[x] -= it -> Y;
		maxh = max(maxh, it -> X);
		//if(l == 0 && r == 2) 
		//printf("gr %lld, X %lld, Y %lld\n", gr[x], it -> X, it -> Y);
		mp[x].erase(it);
	}
	
	mp[x][maxh] = B[m] - gr[x];
	gr[x] = B[m];	
	//printf("%d - %d - %d\n", l, m, r); debug(x);
}

int main(){
	B[END] = -INF;
	update(END, END);	
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", A + i);
		v.pb(A[i]);
	}	
	
	sort(v.begin(), v.end());
	
	for(int i = 0; i < n; i++){
		scanf("%d", B + i);
		update(i, i);	
	}	
	
	divcon(0, n - 1, 0);
	
	ll h = 1, val = gr[0];
	ll sol = 0;
	
	for(pll p : mp[0]){
		sol += (ll) val * (p.X - h);
		h = p.X;
		val -= p.Y;
	}
	printf("%lld\n", sol);
	return 0;	
}
