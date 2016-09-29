#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int main() {
	freopen("C.in", "r", stdin);
	int n;
	scanf("%d", &n);
	freopen("C.out", "r", stdin);

	LL x = 2;
	for (int i = 1; i <= n; ++i) {
		LL t;
		cin >> t;
		x += t * i;
		int res = (int)sqrt(1.0 * x);
		if (1LL * res * res != x) {
			puts("ERR");
			exit(0);
		} else {
			x = res;
		}
	}


	return 0;
}
