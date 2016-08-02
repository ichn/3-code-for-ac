#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

int n, l, k;
DB v1, v2;

const DB eps = 1e-6;
int sgn(DB x) {
	return x < -eps ? -1 : eps < x;
}

bool ok(DB m) {
	int N = n;
	DB L = l;
	while (sgn(m) > 0 && N > 0) {
		N -= k;
		DB t = (v1 * m - L) / (v1 - v2);
		m -= t;
		L -= t * v1;
		if (N <= 0) break;
		DB t_p = (v2 - v1) * t / (v1 + v2);
		L -= t_p * v1;
		m -= t_p;
	}
	if (sgn(m) >= 0 && N <= 0) return true;
	return false;
}

int main() {

#ifdef lol
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif

	cin >> n >> l >> v1 >> v2 >> k;

	//printf("%d\n", ok(4.71458));
	//return 0;

	DB lt = (DB) l / v2, rt = (DB) l / v1;
	while (rt - lt > 1e-6) {
		DB m = (lt + rt) / 2.0;
		if (ok(m))
			rt = m;
		else lt = m;
	}
	printf("%.8lf\n", lt);

	return 0;
}
