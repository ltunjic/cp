#include <bits/stdc++.h> 

#define ll long long

using namespace std; 

const int N = 5e5 + 10;

int arr[N];

int main(){
	int n, k, l;
	scanf("%d%d%d", &n, &k, &l);
	printf("%lld\n", ((ll) k * l + n - 1) / n);
	for(int i = 0; i < n; i++){
		if(i < k) printf("1");
		else printf("0");
	}
	printf("\n");
	int ind = 0;
	for(int i = 0; i < l; i++){
		arr[ind] = true;
		ind = (ind + k) % n;
		if(arr[ind]) ind = (ind + 1) % n;
	}
	for(int i = 0; i < n; i++){
		printf("%d", arr[i]);
	}
	return 0;
}
