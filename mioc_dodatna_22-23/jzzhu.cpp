#include <bits/stdc++.h> 

#define X first
#define Y second
#define pb push_back

using namespace std; 

typedef pair<int, int> pii;
typedef long long ll;

const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

int phi[N], gcdsum[N];
int f[N], d[N], k[N];

vector<int> v[N];

int add(int a, int b){
	if(a + b < MOD) return a + b;
	return a + b - MOD;
}

int sub(int a, int b){
	if(a < b) return a - b + MOD;
	return a - b;	
}

int mult(int a, int b){
	return (ll) a * b % MOD;
}

void euler(){
	phi[1] = 1;
	for(int i = 2; i < N; i++) phi[i] = i - 1;
	for(int i = 2; i < N; i++)
		for(int j = i * 2; j < N; j += i) phi[j] -= phi[i];
} 

void gcds(){
	euler();
	for(int i = 1; i < N; i++)
		for(int j = i; j < N; j += i) v[j].pb(i); 
	gcdsum[1] = 1;
	for(int i = 2; i < N; i++)
		for(int x : v[i]) gcdsum[i] = add(gcdsum[i], mult(x, phi[i / x])); 
}

void init(){
	gcds();
	ll sumi = 0, sumi2 = 0;
	for(int n = 1; n < N; n++){
		f[n] = add(sub(mult(n, mult(n, n)), mult(4, mult(n, sumi))), mult(4, sumi2));
		//trokut
		f[n] = add(f[n], mult(2, mult(n, sumi)));
		f[n] = sub(f[n], mult(2, sumi2));
		f[n] = sub(f[n], mult(2, mult(n, n)));
		f[n] = add(f[n], mult(2, gcdsum[n]));
		//sum
		sumi = add(sumi, n);
		sumi2 = add(sumi2, mult(n, n));
	}
	ll sumf = 0;
	for(int i = 1; i < N; i++){
		sumf = add(sumf, f[i]);
		d[i] = add(d[i - 1], sumf);
	}
	for(int i = 1; i < N; i++){
		k[i] = add(add(d[i], d[i - 1]), k[i - 1]);
	}
}	

int main(){
	init();
	
	int t, n, m;
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &m);
		if(n > m) swap(n, m);
		printf("%d\n", add(mult(sub(m, n), d[n]), k[n]));
	}
	return 0;
}
