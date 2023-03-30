#include <cstdio> 
#include <cstring> 
#include <vector>
#include <algorithm>

#define X first
#define Y second
#define pb push_back

using namespace std; 

typedef long long ll; 
typedef pair<int, int> pii; 

const int LOG = 24; 
const int OFF = 1 << LOG; 

int n, adj[LOG], vis[OFF], ans[LOG];

void debug(int x) {
	for(int i = 0; i < n; i++) printf("%d", x & (1 << i) ? 1 : 0);
}

int main() { 
	scanf("%d", &n); 

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			char c; 
			scanf(" %c", &c); 
			adj[i] ^= (1 << j) * (c == '1'); 
		}
	}
	vis[1] = 1;
	for(int mask = 3; mask < OFF; mask += 2) {
		for(int i = 0; i < LOG; i++)
			if(mask & 1 << i && adj[i] & vis[mask ^ 1 << i]) vis[mask] ^= 1 << i; 
		// if(mask < (1 << n)) {debug(mask); printf(": "); debug(vis[mask]); printf("\n"); }
	}
	
	for(int mask = 1; mask < OFF; mask += 2) {
		int mask2 = 1; 
		for(int i = 1; i < n; i++) 
			if((mask & 1 << i) == 0) mask2 ^= 1 << i;
		for(int i = 0; i < LOG; i++) 
			if(vis[mask] & 1 << i) ans[i] |= vis[mask2]; 
		// if(mask < (1 << n)) { 
		// 	debug(mask); printf(", "); debug(mask2); printf(" : ");
		// 	debug(vis[mask]); printf(", "); debug(vis[mask2]); printf("\n");
		// }
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) printf("%d", ans[i] & (1 << j) ? 1 : 0); 
		printf("\n");
	}
	return 0; 
} 
