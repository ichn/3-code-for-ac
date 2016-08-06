#include <bits/stdc++.h>
using namespace std;


const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

const int maxN = 1000010;
int n, A, m;

struct P {
	int l, a, b;
	P () {}
	void read() {
		scanf("%d %d %d", &l, &a, &b);
	}
	bool operator < (const P&rhs) const {
		return l < rhs.l;
	}
} p[maxN];

int ans, pos;

int pp[maxN];

bool ok(int t) {
	memset(pp, 0, sizeof pp);
	for (int i = 1; i <= t; ++i)
		++pp[p[i].a];
	for (int i = 1; i <= pos; ++i) {
		--pp[p[i].b];
		if (pp[p[i].b] < 0)
			return false;
	}
	return true;
}

void solve() {
	if (pos > n) {
		ans = min(ans, (A - p[1].l) * 2);
		return ;
	}
	if (pos == 1) {
		ans = min(ans, (p[n].l - A) * 2);
		return ;
	}
	memset(pp, 0, sizeof pp);
	for (int i = 1; i < pos; ++i)
		++pp[p[i].a];
	int j = 1;
	while (j < pos && pp[p[j].b] > 0) {
		--pp[p[j].b];
		++j;
	}

	int ret = (p[n].l - p[1].l) * 2 + (j == pos ? 0 : (A - p[j].l) * 2);
	//printf("%d ", ret);

	for (int i = pos; i <= n; ++i) {
		++pp[p[i].a];
		while (j < pos && pp[p[j].b] > 0) {
			--pp[p[j].b];
			++j;
		}
		ret = min(ret, (p[n].l - p[1].l) * 2 + (j == pos ? (p[i].l - A) * 2 : (p[i].l - p[j].l) * 2));
	}
	ans = min(ans, ret);
}

int main() {
#ifdef lol
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		scanf("%d %d", &A, &m);
		for (int i = 1; i <= n; ++i) {
			p[i].read();
		}
		sort(p + 1, p + n + 1);

		pos = 1;
		for (; pos <= n; ++pos) {
			if (A <= p[pos].l)
				break;
		}
		ans = INF;
		solve();
	//	printf("%d ", ans);
		for (int i = 1; i <= n; ++i) {
			p[i].l = 1000001 - p[i].l;
		}
		A = 1000001 - A;
		sort(p + 1, p + n + 1);
		pos = 1;
		for (; pos <= n; ++pos) {
			if (A <= p[pos].l)
				break;
		}
		solve();
		printf("%d\n", ans);
	}

	return 0;
}
