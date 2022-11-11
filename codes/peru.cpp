#include <bits/stdc++.h> 

#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 1e18;
const int N = 25e5 + 10;
const int MOD = 1e9 + 7;

struct obj{
	ll sum;
	int arr;
	int ind; 
};

int cntb = 0;

ll dp[N];
deque<obj> d;
stack<ll> l, r;

int add(ll a, ll b){
	return (a + b) % MOD;
}

int mult(ll a, ll b){
	return a * b % MOD;
}

ll opt(){
	ll ret = INF;
	if(!l.empty()) ret = min(ret, l.top());
	if(!r.empty()) ret = min(ret, r.top());
	return ret;
}

void push(stack<ll> &s, ll val){
	if(s.empty()) s.push(val);
	else s.push(min(val, s.top()));
}

void build(){
	while(!l.empty()) l.pop();
	while(!r.empty()) r.pop();
	int siz = d.size();
	int m = d.size() / 2;
	
	vector<obj> v;
	for(int i = 0; i < m; i++){
		v.push_back(d.front());
		d.pop_front();
	}
	while(!v.empty()){
		push(l, v.back().sum);
		d.push_front(v.back());
		v.pop_back();
	}
	for(int i = 0; i < siz - m; i++){
		v.push_back(d.back());
		d.pop_back();
	}
	while(!v.empty()){
		push(r, v.back().sum);
		d.push_back(v.back());
		v.pop_back();
	}
}	

obj getobj(ll sum, int arr, int ind){
	obj ret;
	ret.sum = sum;
	ret.arr = arr;
	ret.ind = ind;
	return ret;
}

int solve(int n, int k, int* arr){
	for(int i = 1; i <= n; i++){
		if(i == 1){
			dp[i] = arr[i - 1];
			d.push_back(getobj(dp[i - 1] + arr[i - 1], arr[i - 1], i));
			push(r, dp[i - 1] + arr[i - 1]);
		} else {		
			int dpind = i;
			while(!d.empty() && d.back().arr <= arr[i - 1]){
				dpind = d.back().ind;			
	
				d.pop_back();
				if(r.empty()) build();
				else r.pop();
			}
			d.push_back(getobj(dp[dpind - 1] + arr[i - 1], arr[i - 1], dpind));
			push(r, dp[dpind - 1] + arr[i - 1]);
			
			if(i > k){
				ll arrmax = d.front().arr;
				if(d.front().ind <= i - k){
					d.pop_front();
					if(l.empty()) build();
					else l.pop();
					
					if(d.empty()){
						d.push_front(getobj(dp[i - k] + arrmax, arrmax, i - k + 1));
						push(l, dp[i - k] + arrmax);
					} else if(d.front().ind > i - k + 1){
						d.push_front(getobj(dp[i - k] + arrmax, arrmax, i - k + 1));
						push(l, dp[i - k] + arrmax);
					}
				}
			}
			dp[i] = opt();
		}
	}
	
	for(int i = 1; i <= n; i++) dp[i] %= MOD;
		
	ll ans = 0, m = 1;
	for(int i = n; i > 0; i--){
		ans = add(ans, mult(dp[i], m));
		m = mult(m, 23);
	}
	return ans;
}

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	int arr[n];
	for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
	printf("%d\n", solve(n, k, arr));	
	return 0;
}
