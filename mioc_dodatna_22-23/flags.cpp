#include <bits/stdc++.h> 

#define X first
#define Y second
#define pb push_back

using namespace std; 

typedef pair<int, int> pii;

const int LOG = 16; //all
const int OFF = 1 << LOG;
const int HALF = 1 << (LOG - 1);
const int INF = 1e9 + 10;

int n, m, bio[OFF], comp[OFF];
int pos[OFF], child[OFF][2];

vector<int> g[OFF], r[OFF];
vector<pii> line;
stack<int> s;

void rec(int u){
	if(bio[u] == 1) return;
	bio[u] = 1;
	for(int v : g[u]) rec(v);
	s.push(u);
}

void cer(int u, int c){
	if(bio[u] == 2) return;
	bio[u] = 2;
	comp[u] = c;
	for(int v : r[u]) cer(v, c);
}

bool kosaraju(){
	memset(bio, 0, sizeof(bio));
	memset(comp, -1, sizeof(comp));
	for(int i = 1; i < OFF; i++) rec(i);
	int c = 0;
	while(!s.empty()){
		int u = s.top();
		s.pop();
		if(bio[u] != 2) c++;
		cer(u, c);
	}
	for(int i = HALF; i < HALF + n * 2; i += 2){
		//printf("%d : %d %d\n", i, comp[i], comp[i + 1]);
		if(comp[i] == comp[i + 1]) return false;
	}
	return true;
}

void query(int x, int anc, int a, int b, int lo, int hi){
	if(b <= lo || hi <= a) return;
	if((a <= lo && hi <= b) || x >= HALF){
		g[anc].pb(x);
		r[x].pb(anc);
		//printf("%d -> %d\n", anc, x); 
		return;
	}
	int mi = (lo + hi) / 2;
	if(child[x][0] != -1) query(child[x][0], anc, a, b, lo, mi);
	if(child[x][1] != -1) query(child[x][1], anc, a, b, mi, hi);
}

int op(int x){
	return x ^ 1;
}

void buildgraph(int d){
	memset(child, -1, sizeof(child));
	for(int i = 1; i < OFF; i++){
		g[i].clear();
		r[i].clear();
	}
	for(int i = 1; i < OFF; i++){
		if(i < HALF / 2){
			child[i][0] = i * 2;
			child[i][1] = i * 2 + 1;
		} else if(i < HALF) { 
			if(i * 2 - HALF < 2 * n)
				child[i][0] = line[i * 2 - HALF].Y;
			if(i * 2 + 1 - HALF < 2 * n)
				child[i][1] = line[i * 2 + 1 - HALF].Y;		
		}
		if(child[i][0] != -1){
			g[i].pb(child[i][0]);
			r[child[i][0]].pb(i);
		}
		if(child[i][1] != -1){
			g[i].pb(child[i][1]);
			r[child[i][1]].pb(i);		
		}
	}
	for(int i = 0; i < 2 * n; i++){
		int node = op(line[i].Y);
		int a = upper_bound(line.begin(), line.end(), make_pair(pos[node] - d, INF)) - line.begin();
		int b = lower_bound(line.begin(), line.end(), make_pair(pos[node], op(node))) - line.begin();
		if(a < b) query(1, node, a, b, 0, HALF);
		//printf("%d -> (%d %d)\n", i, a, b);
		a = b + 1;
		b = upper_bound(line.begin(), line.end(), make_pair(pos[node] + d, -1)) - line.begin();
		if(a < b) query(1, node, a, b, 0, HALF);
		//printf("%d -> (%d %d)\n", i, a, b);
	}
	/*for(int i = 1; i < OFF; i++){
		printf("%d -> ", i);
		for(int v : g[i]) printf("%d ", v);
		printf("\n");
	}*/
}

int main(){
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		line.pb({a, HALF + i * 2 + 1});
		line.pb({b, HALF + i * 2});
		pos[HALF + i * 2] = a;
		pos[HALF + i * 2 + 1] = b;
	}
	
	sort(line.begin(), line.end());
	
	//for(pii p : line) printf("(%d, %d) ", p.X, p.Y);
	//printf("\n");
	
	//buildgraph(4);
	//printf("is true: %d\n", kosaraju());
//	return 0;
	
	int lo = 0, hi = INF; 
	while(hi - lo > 1){
		int mi = (lo + hi) / 2;
		
		buildgraph(mi);
		
		if(kosaraju()) lo = mi;
		else hi = mi;
	}
	printf("%d\n", lo);
	return 0;
}
