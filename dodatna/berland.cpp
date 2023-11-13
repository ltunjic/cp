#include <bits/stdc++.h> 

#define X first
#define Y second
#define pb push_back

using namespace std; 

typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;

const ld INF = 1e9;
const ld DIF = 1e-9;
const int N = 4010;

int n, m;
bool change;
pair<pii, ld> edge[N];
ld o[N], d[N], d2[N];

vector<pair<pii, ld>> g;

void bf(){
	for(pair<pii, ld> p : g){
		d[p.X.Y] = min(d[p.X.Y], d[p.X.X] + p.Y);
	}
}

bool tw(ld t){
	g.clear();
	d[0] = 0;
	for(int i = 1; i <= n; i++) d[i] = INF;
	for(int i = 0; i < m; i++) g.pb({{edge[i].X.Y, edge[i].X.X}, t - edge[i].Y});
	for(int i = 1; i <= n; i++){
		if(o[i] == INF) continue;
		g.pb({{0, i}, o[i]});
		g.pb({{i, 0}, -o[i]});
	}
	for(int i = 0; i < n; i++) bf();
	for(int i = 0; i <= n; i++) d2[i] = d[i];
	bf();
	for(int i = 0; i <= n; i++) if(d2[i] < d[i] - DIF || d[i] < d2[i] - DIF) return true;
	return false;
}

void task(){
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		if(s == "?") o[i] = INF;
		else o[i] = stoi(s);
	}
	for(int i = 0; i < m; i++){
		int u, v, a;
		cin >> u >> v >> a;
		edge[i] = {{u, v}, a};
	}
	
	ld lo = 0, hi = 1e9;
	while(hi - lo > 1e-8){
		ld mi = (lo + hi) / 2;
		if(tw(mi)) lo = mi;
		else hi = mi;
	}
	printf("%.6Lf\n", hi);
	assert(!tw(hi));
	for(int i = 1; i <= n; i++){ 
		printf("%.6Lf ", d[i]);
	}
	printf("\n");
}

int main(){
	ios_base::sync_with_stdio(false);
	while(cin >> n >> m){
		task();
	}
	return 0;
}
