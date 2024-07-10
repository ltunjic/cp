#include <cstdio>
#include <set>
#include "assistant.h"
#include <algorithm>
#include <cassert>

using namespace std; 

typedef long long ll;
typedef pair<int, int> pii;

const int N = 2e5 + 10;

set<int> act[2];

void Assist(unsigned char *a, int n, int k, int r) {
	for(int i = 0; i < k; ++i) { 
		act[a[i]].insert(i);
	}

	for(int i = 0; i < n; ++i) { 
		int x = GetRequest();
		bool d = a[i + k];

		auto it = act[0].find(x);
		if(it != act[0].end()) { 
			act[0].erase(it);
		} else {
			int out = *act[1].begin();
			act[1].erase(act[1].begin());
			PutBack(out);
		}
		act[d].insert(x);
	}
}
