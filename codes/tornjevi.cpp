#include <bits/stdc++.h> 

#define X first
#define Y second
#define pii pair<int, int>
#define pb push_back
#define ll long long

using namespace std; 

const int N = 110;
const int M = 1e5 + 10;
const int out[2][2] = {{2,1}, 
		       {3,4}}; 
int n, m, cnt;
int mat[N][N], hor[N][N], ver[N][N];
int sol[M], bio[M], comp[M];

vector<int> g[M], r[M];
vector<int> s, solvd;

int notx(int x){
	if(x & 1) return x - 1;
	return x + 1;
}

void rec(int u){
	if(bio[u]) return;
	bio[u] = 1;
	for(int v : g[u]){
		rec(v);
	}
	s.pb(u);
}

void cer(int u, int c){
	if(bio[u]) return;
	bio[u] = 1;
	comp[u] = c;
	for(int v : r[u]){
		cer(v, c);
	}
}

void mark(int u, bool flag){
	if(sol[u] != -1){
		if(sol[u] != flag){
			printf("%d!!!!!\n", u);
			assert(0); 
		}
		return;
	} 
	sol[u] = flag;
	if(flag){
		for(int v : g[u]) mark(v, flag);
		mark(notx(u), !flag);	
	} else {
		for(int v : r[u]) mark(v, flag);
		mark(notx(u), !flag);
	}
}

void kosaraju(){
	for(int i = 0; i < cnt; i++) rec(i);
	
	reverse(s.begin(), s.end());
	
	int c = 0;
	memset(bio, 0, sizeof(bio));
	memset(comp, -1, sizeof(comp));
	
	for(int x : s){ 
		if(bio[x]) continue;
		c++;
		cer(x, c);
	}
	
	memset(sol, -1, sizeof(sol));
	
	for(int x : solvd) mark(x, true);
	for(int i = 0; i < cnt; i += 2){
		if(sol[i] == -1 && sol[i + 1] == -1){
			if(comp[i] > comp[i + 1]) mark(i, true);
			else mark(i + 1, true);
		} 
	}
}

int findver(int x, int y, int d){
	int nx = x;
	while(nx >= 0 && nx < n){
		if(mat[nx][y] == 2) break; 
		if(mat[nx][y] == 1) return ver[nx][y] + max(0, d);
		nx += d;
	}
	return -1;
}

int findhor(int x, int y, int d){
	int ny = y;
	while(ny >= 0 && ny < m){
		if(mat[x][ny] == 2) break; 
		if(mat[x][ny] == 1) return hor[x][ny] + max(0, d);
		ny += d;
	}
	return -1;
}

int main(){
	scanf("%d%d", &n, &m);
	
	for(int i = 0; i < n; i++){
		string str;
		cin >> str;
		for(int j = 0; j < m; j++){
			char c = str[j];
			if(c == 'T'){ 
				mat[i][j] = 1;
				hor[i][j] = cnt;
				ver[i][j] = cnt + 2;
				cnt += 4;
			}
			if(c == '#') mat[i][j] = 2;
			if(c == 'n') mat[i][j] = 3;
		}
	}
	
	for(int i = 0; i < n; i++){
		int pos, flag = false;
		for(int j = 0; j < m; j++){
			if(mat[i][j] == 1){
				if(flag){
					int ind1 = hor[i][pos];
					int ind2 = hor[i][j];
					solvd.pb(ind1 + 1);
					solvd.pb(ind2);
				}
				flag = true;
				pos = j;
			} else if (mat[i][j] == 2){
				flag = false;
			}
		}
	}
	
	for(int j = 0; j < m; j++){
		int pos, flag = false;
		for(int i = 0; i < n; i++){
			if(mat[i][j] == 1){
				if(flag){
					int ind1 = ver[pos][j];
					int ind2 = ver[i][j];
					solvd.pb(ind1 + 1);
					solvd.pb(ind2);
				}
				flag = true;
				pos = i;
			} else if (mat[i][j] == 2){
				flag = false;
			}
		}
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(mat[i][j] == 3){
				int ind11 = findhor(i, j, -1);
				int ind12 = findhor(i, j, 1);
				int ind21 = findver(i, j, -1);
				int ind22 = findver(i, j, 1);
				
				int mi1 = max(ind11, ind12);
				int mi2 = max(ind21, ind22);
				
				if(mi1 == -1){
					if(ind21 != -1) solvd.pb(ind21);
					if(ind22 != -1) solvd.pb(ind22);
				} else if(mi2 == -1){
					if(ind11 != -1) solvd.pb(ind11);
					if(ind12 != -1) solvd.pb(ind12);
				} else {
					if(ind11 != -1 && ind21 != -1){
						g[notx(ind11)].pb(ind21);
						g[notx(ind21)].pb(ind11);
						r[ind21].pb(notx(ind11));
						r[ind11].pb(notx(ind21));
					}
					if(ind11 != -1 && ind22 != -1){
						g[notx(ind11)].pb(ind22);
						g[notx(ind22)].pb(ind11);
						r[ind22].pb(notx(ind11));
						r[ind11].pb(notx(ind22));
					}
					if(ind12 != -1 && ind21 != -1){
						g[notx(ind12)].pb(ind21);
						g[notx(ind21)].pb(ind12);
						r[ind21].pb(notx(ind12));
						r[ind12].pb(notx(ind21));
					}
					if(ind12 != -1 && ind22 != -1){
						g[notx(ind12)].pb(ind22);
						g[notx(ind22)].pb(ind12);
						r[ind22].pb(notx(ind12));
						r[ind12].pb(notx(ind22));	
					}
				}				
			}
		}	
	}
		
	kosaraju();
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(mat[i][j] == 1) printf("%d", out[sol[ver[i][j] + 1]][sol[hor[i][j] + 1]]);
			else if(mat[i][j] == 2) printf("#");
			else if(mat[i][j] == 3) printf("n");
			else printf(".");		
		}	
		printf("\n");
	}
	return 0;
}
