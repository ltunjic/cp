#include <cstdio>
#include <vector> 
#include <set>
#include <stack>
#include <algorithm>
#include "advisor.h"
#include <cstring> 
#include <cassert>

#define X first
#define Y second
#define PB push_back

using namespace std; 

typedef pair<int, int> pii;

const int N = 2e5 + 10;

int lst[N], dea[N];

stack<int> nxt[N];
set<pii> s;

void ComputeAdvice(int *c, int n, int k, int m) {
	memset(lst, -1, sizeof(lst));

	for(int i = 0; i < n; ++i) { 
		nxt[i].push(N);
	}

	for(int i = n - 1; i >= 0; --i) { 
		nxt[c[i]].push(i);
	}

	for(int i = 0; i < k; ++i) {
		lst[i] = i;
		s.insert({nxt[i].top(), i});
	}

	for(int i = 0; i < n; ++i) {
		auto it = s.find({nxt[c[i]].top(), c[i]}); 
		nxt[c[i]].pop();
		if(it != s.end()) { 
			s.erase(it);
		} else {
			int obr = prev(s.end())->Y;
			dea[lst[obr]] = 1;
			s.erase(prev(s.end()));
		}	
		s.insert({nxt[c[i]].top(), c[i]});
		lst[c[i]] = i + k;
	}

	for(auto i : s) { 
		dea[lst[i.Y]] = 1;
	}

	for(int i = 0; i < k + n; ++i) {
		WriteAdvice(dea[i]);
	}
}
