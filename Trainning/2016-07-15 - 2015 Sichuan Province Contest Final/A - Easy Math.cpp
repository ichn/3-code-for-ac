#include <bits/stdc++.h>
using namespace std;

int n;

set<int> sq;

int num[100000 + 100];

void solve() {
	for (int i = 1; i <= n; ++i) {
		if (sq.find(num[i]) == sq.end()) {
			puts("No");
			return ;
		}
	}
	puts("Yes");
}


int main() {
#ifdef lol
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	for (int i = 0; i < 1e5; ++i) {
		sq.insert(i*i);
	}
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d", &num[i]);
		solve();
	}
}
