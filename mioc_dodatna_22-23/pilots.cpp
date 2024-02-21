#include <bits/stdc++.h> 

using namespace std; 

const int N = 3 * 1e6 + 10;

int n, arr[N], t;

deque<int> maxi, mini;

bool lessp(int a, int b, bool c){
	return (a < b) ^ c;
}

void update(deque<int> &d, int val, bool c){
	while(!d.empty() && d.back() != val && lessp(d.back(), val, c)){
		d.pop_back();
	}
	d.push_back(val);
}	

void pop(deque<int> &d, int val){
	if(d.front() == val) d.pop_front();
	return;
}

int main(){
	scanf("%d%d", &t, &n);
	
	int ind = 0;
	int ans = 1;
	for(int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
		update(mini, arr[i], 1);
		update(maxi, arr[i], 0);
		
		//printf("diff = %d - %d = %d\n", maxi.front(), mini.front(), maxi.front() - mini.front());
		
		while(maxi.front() - mini.front() > t){
			pop(maxi, arr[ind]);
			pop(mini, arr[ind]);
			ind++;
		}
		ans = max(ans, i - ind + 1);
	}
	printf("%d\n", ans);
	return 0;
}
