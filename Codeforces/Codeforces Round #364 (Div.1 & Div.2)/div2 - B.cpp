#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

LL ans = 0;
int n, m;

int mrk[2][100001];
int cnt[2];

int main() {

#ifdef lol
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif

	scanf("%d %d", &n, &m);
	ans = 1LL * n * n;
	for (int i = 1; i <= m; ++i) {
		int x,  y;
		scanf("%d %d", &x, &y);
		bool M1 = false;
		bool M2 = false;
		if (!mrk[0][x]) {
			M1 = true;
			ans += cnt[1];
			++cnt[0];
			mrk[0][x] = 1;
			ans -= n;
		//	ans += i;
		}
		if (!mrk[1][y]) {
			M2 = true;
			ans += cnt[0];
			mrk[1][y] = 1;
			ans -= n;
			++cnt[1];
		//	ans += i;
		}
		//if (M1 && M2) ++ans;
		cout << ans << ' ';
	}
	puts("");

	return 0;
}
