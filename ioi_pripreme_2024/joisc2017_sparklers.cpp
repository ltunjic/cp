#include <cstdio> 
#include <algorithm>
#include <cstring>
 
using namespace std; 
 
typedef long long ll;
 
const int N = 1e5 + 10;
const int OO = 1e9 + 10;
 
int n, t, k, A[N];
 
ll B[N];
 
bool out(int l, int r, int lo, int hi) { // lo <= l | r <= hi
	int l_ = l, r_ = r;
 
	for(; lo >= 0 && B[lo] >= B[r]; --lo) {
		if(B[lo] > B[l_]) {
			l_ = lo; 
		}
	}
 
	for(; hi < n && B[hi] <= B[l]; ++hi) {
		if(B[hi] < B[r_]) { 
			r_ = hi;
		}
	}
 
	if(lo < 0 && hi >= n) { return 1; }
	if(l == l_ && r == r_) { return 0; }
	return out(l_, r_, lo, hi); 
}
 
bool in(int l, int r, int lo, int hi) { // lo <= l | r <= hi
	int l_ = l, r_ = r;
 
	for(; lo < k && B[lo] >= B[r]; ++lo) {
		if(B[lo] > B[l_]) {
			l_ = lo; 
		}
	}
 
	for(; hi > k - 2 && B[hi] <= B[l]; --hi) {
		if(B[hi] < B[r_]) { 
			r_ = hi;
		}
	}
 
	if(lo >= k && hi <= k - 2) { return 1; }
	if(l == l_ && r == r_) { return 0; }
	return in(l_, r_, lo, hi); 
}
 
bool loop(int mi) {
	for(int i = 0; i < n; ++i) {
		B[i] = (ll) A[i] - (ll) 2 * mi * t * i;
	}	
 
	return out(k - 1, k - 1, k - 2, k) & in(0, n - 1, 1, n - 2);
}
 
int main() { 
	scanf("%d%d%d", &n, &k, &t);
	for(int i = 0; i < n; ++i) { scanf("%d", A + i); }
 
	int lo = -1, hi = OO / t + 100;
	for(int mi = (lo + hi) / 2; hi - lo > 1; mi = (lo + hi) / 2) {
		bool res = loop(mi);
//		printf("[%d %d %d] = %d\n", lo, mi, hi, res);
		if(res) { hi = mi; }
		else { lo = mi; }
	}
 
	printf("%d\n", hi);
	return 0;
}
