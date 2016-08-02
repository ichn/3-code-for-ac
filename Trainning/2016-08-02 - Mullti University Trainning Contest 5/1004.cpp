#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const double pi = 3.1415926535897932;

struct PP {
	int x, y;
	PP () {}
	PP(int x, int y):x(x), y(y) {}
	void read() {
		scanf("%d %d", &x, &y);
	}
} p[2222];
int n;

long long ans;

const double eps = 1e-7;
int sgn(double x) {
	return x < -eps ? -1 : eps < x;
}

double a[2222];
int id[4222];

bool cmp(int x, int y) {
	return a[x] < a[y];
}

int flg;
long long dot(int x, int y) {
	return (LL)(0LL + p[x].x - p[flg].x) * (p[y].x - p[flg].x) + (LL)(0LL + p[x].y - p[flg].y) * (p[y].y - p[flg].y);
}

long long cross(int x, int y) {
	return (LL)(0LL + p[x].x - p[flg].x) * (p[y].y - p[flg].y) - (LL)(0LL + p[x].y - p[flg].y) * (p[y].x - p[flg].x);
}


int main() {
#ifdef lol
	freopen("1004.in", "r", stdin);
	freopen("1004.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			p[i].read();
		ans = 1LL * n * (n - 1LL) * (n - 2LL) / 6;
		long long sub = 0;
		for (int i = 1; i <= n; ++i) {
			int tp = 0;
			for (int j = 1; j <= n; ++j) {
				if (j != i) {
					++tp;
					id[tp] = j;
					a[j] = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
					a[j] += pi;
				}
			}
			sort(id + 1, id + tp + 1, cmp);
			for (int j = 1; j <= tp; ++j)
				id[tp+j] = id[j];
			flg = i;
			int k = 1, t = 1;
			for (int j = 1; j <= tp; ++j) {
				while (k <= j + tp && dot(id[k], id[j]) > 0 && cross(id[k], id[j]) <= 0) 
					++k;
				if (t < k) t = k;
				while (t <= j + tp && dot(id[t], id[j]) <= 0) 
					++t;
				sub += t - k;
			}
		}
		sub /= 2;
		cout << ans - sub << endl;
	}
	return 0;
}

