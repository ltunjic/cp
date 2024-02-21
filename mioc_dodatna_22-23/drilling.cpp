#include <bits/stdc++.h> 
#include <unistd.h>
 
#define X first
#define Y second
#define ll long long
#define pii pair<int, int>
#define pb push_back
#define vec vector
#define pri(i, poc, n, pov) for(int i = (int) poc; i < (int) n; i += (int) pov)
#define od(i, poc, n, pov) for(int i = (int) poc; i > (int) n; i -= (int) pov)
 
using namespace std;
 
const int INF = 2 * 1e9 + 10;                              
const int N = 2010;
 
int abs(int x){ 
	if(x < 0)
		return -x;
	return x;
}
 
int cost[N], n, dp[N][N], poi[N][2];
deque<pii> slide[N][2];
 
int na(int x){ 
	if(x < 0 || x >= n) return 0;
	return cost[x];
}
 
int DP(int l, int r){ 
	return (r < l ? 0 : dp[l][r]);
}
 
void deqAdd(int x, int s, int y){ 
	int c = dp[x][y] + (s ? na(y + 1) : na(y - 1)); 
	while(!slide[x][s].empty() && slide[x][s].back().X >= c)
		slide[x][s].pop_back();
	slide[x][s].push_back({c, y});
}
 
void deqPop(int x, int s, int val){ 
	if(!slide[x][s].empty() && slide[x][s].front().Y == val)
		slide[x][s].pop_front();
}
 
void deqClear(int l, int r){ 
	while(poi[l][1] < r && DP(l, poi[l][1]) < DP(poi[l][1] + 2, r)){ 
		deqPop(l, 1, poi[l][1]);
		poi[l][1]++;
	}
 
	while(poi[r][0] > l && DP(poi[r][0], r) < DP(l, poi[r][0] - 2)){ 
		deqPop(r, 0, poi[r][0]);
		poi[r][0]--;
	}
}
 
int deqMin(int l, int r){ 
	int ret = INF;
	if(!slide[l][1].empty())
		ret = min(ret, slide[l][1].front().X);
	if(!slide[r][1].empty())
		ret = min(ret, slide[r][0].front().X);
	return ret;
}
 
int main(){ 
	ios_base::sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
 
	pri(i, 0, N, 1) poi[i][0] = poi[i][1] = i;
 
	cin >> n;
 
	pri(i, 0, n, 1) cin >> cost[i];
 
	pri(i, 0, n, 1){ 
		od(j, i, -1, 1){ 
			if(j == i){ 
				dp[j][i] = cost[i];
				deqAdd(i, 0, j);
				deqAdd(i, 1, j);
			} else if(j + 1 == i){ 
				dp[j][i] = dp[i][j] = cost[i] + cost[j];
				deqAdd(i, 0, j);
				deqAdd(j, 1, i);
			} else { 
				deqClear(j, i);
				dp[j][i] = dp[i][j] = deqMin(j, i);
				deqAdd(i, 0, j);
				deqAdd(j, 1, i);
			}
			//cout << j << " " << i << " : " << dp[j][i] << "\n";
 
		}
	}
 
	cout << dp[0][n - 1] << "\n";
	return 0;
} 
