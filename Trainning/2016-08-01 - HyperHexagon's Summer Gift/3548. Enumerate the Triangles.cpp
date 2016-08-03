#include <bits/stdc++.h>
using namespace std;

struct pp {
	int x, y;
	pp() {}
	pp(int x, int y):x(x), y(y) {}
} p[1111];
int n;

int cross(pp a, pp b) {
	return a.x * b.y - a.y * b.x;
}

pp operator - (pp a, pp b) {
	return pp(a.x - b.x, a.y - b.y);
}

double len(pp a, pp b) {
	return sqrt(0.0 + (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double ppp(pp a, pp b, pp c) {
	pp d = a - b, e = a - c;
	if (cross(d, e) == 0)
		return 1000000001;
	return len(a, b) + len(b, c) + len(c, a);
}

int main() {
#ifdef lol
	freopen("1004.in", "r", stdin);
	freopen("std.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; ++tt) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d %d", &p[i].x, &p[i].y);
		random_shuffle(p + 1, p + n + 1);
		pp d = p[1] - p[2];
		bool na = true;
		for (int i = 3; i <= n; ++i) {
			if (cross(d, p[i] - p[1]) != 0) {
				na = false;
				break;
			}
		}
		if (na) {
			printf("Case %d: No Solution\n", tt);
			continue;
		}
		double ans = 1000000001;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j) {
				if (len(p[i], p[j]) > ans) continue;
				for (int k = j + 1; k <= n; ++k) {
					ans = min(ans, ppp(p[i], p[j], p[k]));
				}
			}
		if (ans > 1000000000) {
			printf("Case %d: No Solution\n", tt);
		} else {
			printf("Case %d: %.3lf\n", tt, ans);
		}
	}
	return 0;
}
