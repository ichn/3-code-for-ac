#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
struct P {
	LL x, y;
	void read() {
		cin >> x >> y;
	}
} p[2111];
	
LL len(P a, P b) {
	return 1LL * (a.x-b.x)*(a.x-b.x) + 1LL*(a.y-b.y)*(a.y-b.y);
}
bool ok(P a, P b, P c) {
	LL x = len(a, b), y = len(b, c), z = len(a, c);
	if (y > x) swap(x, y);
	if (z > x) swap(x, z);
	return y + z > x;
}

int main() {
	freopen("1004.in", "r", stdin);
	freopen("bf.out", "w", stdout);

	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			p[i].read();
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				for (int k = j + 1; k <= n; ++k)
					ans += ok(p[i], p[j], p[k]);
		printf("%d\n", ans);
	}

	return 0;
}
