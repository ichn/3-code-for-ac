#include <bits/stdc++.h>
using namespace std;
#define i a[0]
#define j a[1]
#define k a[2]
#define w a[3]

typedef long long LL;
const int maxN = 1e5 + 100;
int n, a[4];
struct Point {
	LL x[3];
	Point() {}
	void read() {
		for (j = 0; j < 3; ++j)
			cin >> x[j];
	}
} p[maxN];

LL dis(Point x) {
	LL ret = 0;
	for (int a = 0; a < n; ++a) {
		ret = max(ret, abs(p[a].x[0] - x.x[0]) + abs(p[a].x[1] - x.x[1]) + abs(p[a].x[2] - x.x[2]));
	}
	return ret;
}



int main() {
#ifdef love_lwd
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif


	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tCase;
	cin >> tCase;
	while (tCase--) {
		cin >> n;
		for (i = 0; i < n; ++i)
			p[i].read();
		if (n == 1) {
			for (j = 0; j < 3; ++j)
				cout << p[0].x[j] << ' ';
			cout << endl;
			continue;
		}
		Point tp;
		LL maxDis = dis(tp);
		LL stp = (LL)1e18+514;
		while (stp) {
			bool chg = false;
			a[0] = a[1] = a[2] = 0;
			Point dp;
			for (i = -1; i <= 1 && !chg; ++i) {
				dp.x[0] = tp.x[0] + i * stp;
				for (j = -1; j <= 1 && !chg; ++j) {
					dp.x[1] = tp.x[1] + j * stp;
					for (k = -1; k <= 1 && !chg; ++k) {
						dp.x[2] = tp.x[2] + k * stp;
						LL dd = dis(dp);
						if (dd < maxDis) {
							maxDis = dd;
							tp = dp;
							chg = true;
						}
					}
				}
			}
			if (!chg) stp /= 2;
		}
		for (j = 0; j < 3; ++j)
			cout << tp.x[j] << ' ';
		cout << endl;
	}


	return 0;
}
