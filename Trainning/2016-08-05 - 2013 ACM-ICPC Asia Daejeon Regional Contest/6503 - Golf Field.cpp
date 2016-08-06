#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

const DB eps = 1e-8;
int sgn(DB x) {
	return x < -eps ? -1 : eps < x;
}

struct P {
	DB x, y;
	P() {}
	P(DB x, DB y):x(x), y(y) {}
	void read() {
		scanf("%lf %lf", &x, &y);
	}
};

P operator - (P a, P b) {
	return P(a.x - b.x, a.y - b.y);
}

DB C(P a, P b) {
	return a.x * b.y - a.y * b.x;
}

DB D(P a, P b) {
	return a.x * b.x + a.y * b.y;
}

bool operator < (P a, P b) {
	return a.x < b.x || (sgn(a.x - b.x) == 0 && a.y < b.y);
}

const int maxN = 63333;
int n;
P p[maxN];
P p2[maxN];
P p3[maxN];
P cv[maxN];
int m;

bool cmp(P a, P b) {
	a = a - cv[0];
	b = b - cv[0];
	return atan2(a.y, a.x) < atan2(b.y, b.x);
}

DB ans;


DB dist(P a, P b) {
	return sqrt(D(a-b, a-b));
}

DB area(P a, P b, P c) {
	return fabs(C(b - a, c - a) / 2);
}

int main() {
#ifdef lol
	freopen("hd.in", "r", stdin);
	freopen("hd.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			p[i].read();
		sort(p + 1, p + n + 1);
		m = 0;
		for (int i = 1; i <= n; ++i) {
			while (m > 1 && sgn(C(cv[m-1] - cv[m-2], p[i]-cv[m-2])) < 0) m--;
			cv[m++] = p[i];
		}
		int k = m;
		for (int i = n-1; 0 < i; --i) {
			while (m > k && sgn(C(cv[m-1]-cv[m-2], p[i] - cv[m-2])) < 0) --m;
			cv[m++] = p[i];
		}
		if (n > 1) m--;
		for (int i = 0; i < m; ++i)
			cv[m+i] = cv[i];
		ans = 0.0;
		int i = 0, j = 0;
		int t = 0, s = 0;
		for (; i < m; ++i)
			for (j = i + 1; j < m; ++j)
				for (t = i; t <= j; ++t)
					for (s = j; s <= i+m; ++s)
						ans = max(ans, area(cv[s], cv[i], cv[j]) + area(cv[t], cv[i], cv[j]));

		printf("%.1lf\n", ans);
	}

	return 0;
}
