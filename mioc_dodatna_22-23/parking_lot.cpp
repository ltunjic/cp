#include <bits/stdc++.h>

#define X first
#define Y second
#define pb push_back

using namespace std; //volim te seka

typedef pair<int, int> pii;

const int N = 2010;

int CNT;
int n, m, k, mat[N][N];
int up[N][N], dw[N][N];

deque<int> u, d;
vector<int> sol;
vector<pii> hist;

void izbrisi(deque<int> &x, int val){
	if(x.empty() || x.front() != val) return;
	x.pop_front();
}

void dodaj(deque<int> &x, int val){
	while(!x.empty() && x.back() > val) x.pop_back();
	x.push_back(val);
}

int minum(deque<int> &x){
	if(x.empty()) return N;
	return x.front();
}	

void update(int x, int y){
	if(mat[x][y]) CNT--;
	else CNT++;
	
	mat[x][y] ^= 1;
	
	int len = 0;
	for(int i = 1; i <= n; i++){
		len++;
		if(mat[i][y]) len = 0;
		up[i][y] = len;
	}
	len = 0;
	for(int i = n; i >= 1; i--){
		len++;
		if(mat[i][y]) len = 0;
		dw[i][y] = len;
	}
}

int query(int x){
	u.clear();
	d.clear();
		
	int tp = 0, ret = 0;
	for(int i = 1; i <= m; i++){
		tp = max(tp, i - 1);
	
		izbrisi(u, up[x][i - 1]);
		izbrisi(d, dw[x][i - 1]);
		
		while(tp + 1 <= m && tp - i + 2 <= min(minum(u), up[x][tp + 1]) + min(minum(d), dw[x][tp + 1]) - 1){
			dodaj(u, up[x][tp + 1]);
			dodaj(d, dw[x][tp + 1]);
			tp++;
		}
		ret = max(ret, tp - i + 1); 
	}
	//printf("%d = %d\n", x, ret);
	return ret;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
		
	int t = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			char c;
			scanf(" %c", &c);
			if(c == 'X'){ 
				CNT++;
				mat[i][j] = 1;
			}
		}
	
	for(int j = 1; j <= m; j++){
		update(0, j);
		CNT--;
	}	
	
	for(int i = 0; i < k; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		update(x, y);
		hist.pb({x, y});
	}
		
	int ans = CNT != n * m;
	for(int i = 1; i <= n; i++) 
		ans = max(ans, query(i));
	sol.pb(ans);
		
	for(int i = k - 1; i >= 0; i--){
		pii p = hist[i];
		update(p.X, p.Y);
		ans = max(ans, query(p.X));
		sol.pb(ans);
	}
	
	for(int i = k - 1; i >= 0; i--) printf("%d\n", sol[i]);
	return 0;
}
