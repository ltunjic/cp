#include <bits/stdc++.h>

#define X first
#define Y second
#define pii pair<int, int>
#define ll long long
#define pb push_back

using namespace std;

const int N = 2010;

int n, m, cnt;

bool bio[N][2], bioE[N];

vector<pii> g[N][2];
vector<int> all[N];

void rec(int u, bool flag){
	if(bio[u][flag]) return;
	bio[u][flag] = true;
	
	//printf("%d(col = %d) | %d\n", u, flag, cnt);
	
	for(pii p : g[u][flag]){
		int v = p.X, e = p.Y;
		if(!bioE[e]){
			cnt++;
			bioE[e] = true;
		}
		rec(v, !flag);
	}
	
	if(bio[u][flag] && bio[u][!flag]){
		for(int v : all[u]){
			rec(v, true);
			rec(v, false);
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);

	for(int i = 0; i < m; i++){
		int a, b;
		char c;

		scanf("%d %d %c", &a, &b, &c);
		
		bool flag = c == 'r';
		
		g[a][flag].pb({b, i});
		g[b][flag].pb({a, i});
		all[a].pb(b);
		all[b].pb(a);
	}
	
	for(int i = 1; i <= n;  i++){
		rec(i, true);
		if(cnt == m){
			printf("Yes\n");
			return 0;
		}		
		memset(bio, 0, sizeof(bio));
		memset(bioE, 0, sizeof(bioE));
		cnt = 0;
		rec(i, false);
		if(cnt == m){
			printf("Yes\n");
			return 0;
		}	
		memset(bio, 0, sizeof(bio));
		memset(bioE, 0, sizeof(bioE));
		cnt = 0;
	}
	printf("No\n");
	return 0;
}
