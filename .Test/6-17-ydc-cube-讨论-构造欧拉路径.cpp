#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

int main() {
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);

	int x, y, z, cas = 0;
	while (scanf("%d %d %d", &x, &y, &z) != EOF) {
		++cas;

		if (y < x) swap(x, y);
		if (z < x) swap(z, x);
		if (z < y) swap(y, z);

		printf("Case #%d: ", cas);
		if (x == 1 && y == 1) {
			printf("%d\n", z-1);
		} else if (x == 1) {
			int ans = (y - 1) * z + (z - 1) * y;
			y -= 2, z -= 2;
			if ((y & 1) || (z & 1)) {
				if ((y & 1) && (z & 1)) {
					--y, --z;
					ans += 2;
				}
				if (y & 1) {
					--y;
				}
				if (z & 1) {
					--z;
				}
				ans += y + z;
			} else {
				ans += y;
				ans += max(0, z - 1);
			}
			printf("%d\n", ans);
		} else {
			LL ans = (y - 1LL) * x * z + y * (x - 1LL) * z + y * x * (z - 1LL);

			if (x == 2) {
				ans += 3;
				x -= 2, y -= 2, z -= 2;

				LL t = y * z;
				ans += t;
				printf("%lld\n", ans);
				
				continue;
			}

			int ep = 8;

			x -= 2, y -= 2, z -= 2;
			LL t = x * y;

			if (t & 1) {
				ep -= 2;
				ans += 4;
				--t;
			}
			ans += t;

			t = x * z;

			if (t & 1) {
				ep -= 2;
				ans += 4;
				--t;
			}
			ans += t;

			t = y * z;

			if (t & 1) {
				ep -= 2;
				ans += 4;
				--t;
			}
			ans += t;

			ep -= 2;

			int add = ep * 2 - ep / 2;

			if (x == 1) {
				add = min(add, ep);
			}
		
			ans += add;

			printf("%lld\n", ans);
		}
	}

	return 0;
}
	
