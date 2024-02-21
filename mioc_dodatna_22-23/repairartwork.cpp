#include <bits/stdc++.h>

#define X first
#define Y second
#define pb push_back

using namespace std;

typedef long long ll; 

const int N = 105; 
const int MOD = 1e9 + 7; 

inline int add(int a, int b) {
	if(a + b < MOD) return a + b;
	return a + b - MOD;
}

inline int mult(int a, int b) {
	return (ll) a * b % MOD;
}

int pot(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = mult(ret, a); 
		a = mult(a, a); 
		b >>= 1;
	} 
	return ret;
}

int n, m, A[N], dp[2][N][N * N / 2];

void task() {
	memset(dp, 0, sizeof(dp)); 
	
	scanf("%d%d", &n, &m);

	for(int i = 0; i < n; i++) {
		scanf("%d", A + i); 
		dp[1][i][0] = 1;
	}
	dp[1][n][0] = 1;
	int ans = 0; 
	bool f = false;
	for(int i = n - 1; i >= 0; i--) {
		for(int j = 0; j <= i; j++)
			for(int s = 0; s <= (n + 1) * n / 2; s++) {
				dp[f][j][s] = 0; 
				if(A[i] != 1 && s >= i - j + 1) dp[f][j][s] = dp[!f][j][s - i + j - 1]; 
				if(A[i] == 1) dp[f][j][s] = dp[!f][i + 1][s]; 
				if(A[i] == 2) dp[f][j][s] = add(dp[f][j][s], MOD - dp[!f][i + 1][s]);
			}
		f ^= 1; 
	}
	for(int i = 0; i <= n * (n + 1) / 2; i++) {
		ans = add(ans, mult(dp[!f][0][i], pot(i, m)));
	}
	printf("%d\n", ans);
}

int main() {
	int t;
	scanf("%d", &t); 
	for(t; t; t--) task(); 
	return 0; 
}
