#include <bits/stdc++.h>
#define Mo 110119
#define M 2000
typedef long long LL;
using namespace std;
LL c[200000], h[200000], T, n;
int a[200000], b[200000];

int lb(int x){
	return x & (-x);
}

void add(int x, int p){
	while (x > 0) {
		c[x] += p, x = x-lb(x);
	}
}

int ask(int x){
	int ret = 0;
	while (x <= n){
		ret += c[x], x = x+lb(x);
	}
	return ret;
}

int main(){
	cin >> T;
	while (T--) {
		cin >> n;
		for(int i = 1; i <= n; i++) c[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for(int i = 1; i <= n; i++) h[b[i]] = i;
		LL ans = 0;
		for(int i = 1; i <= n; i++){
			ans = ans+ask(h[a[i]]+1);
			add(h[a[i]],1);
		}
		cout << ans << endl;
	}
}
