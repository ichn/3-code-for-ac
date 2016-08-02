#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 500 + 10;
const int INF = 0x3f3f3f3f;
const DB eps = 1e-10;

int dcmp(DB x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

struct Point {
	DB x, y;
	Point() {}
	Point(DB x, DB y):x(x), y(y) {}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};
typedef Point Vector;
Vector operator - (const Point &a, const Point &b) {
	return Vector(a.x - b.x, a.y - b.y);
}
DB cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}
DB dot(Point a, Point b) {
	return a.x*b.x + a.y*b.y;
}
bool on(Point p, Point a, Point b) {
	return dcmp(cross(a - p, b - p)) == 0 && dcmp(dot(a - p, b - p)) <= 0;
}
bool onleft(Point p, Point a, Point b) {
	return cross(p - a, b - a) > 0;
}

Point Akane[maxn], Ranma[maxn];
int G[maxn][maxn], n, m;

bool ok(Point a, Point b) {
	for(int i = 1; i <= m; ++i) {
		if(!(on(Ranma[i], a, b) || onleft(Ranma[i], a, b)))
			return false;
	}
	return true;
}
bool same_pos(int i) {
	for(int j = 1; j <= m; ++j) {
		if(Akane[i].x != Ranma[j].x || Akane[i].y != Ranma[j].y) {
			return false;
		}
	}
	return true;
}

void solve() {
	if(m == 0) {
		puts("0");
		return ;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) if(j != i) {
			if(ok(Akane[i], Akane[j])) {
				G[i][j] = 1;
			}
		}
	}
	for(int i = 1; i <= n; ++i) {
		if(same_pos(i)) {
			puts("1");
			return ;
		}
	}
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
	int ans = INF;
	for(int i = 1; i <= n; ++i) ans = min(ans, G[i][i]);
	if(ans == INF) puts("-1");
	else printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1027.in", "r", stdin),	freopen("1027.out", "w", stdout);
#endif

	DB tmp;
	while(scanf("%d%d", &n, &m) != EOF) {
		for(int i = 1; i <= n; scanf("%lf", &tmp), ++i) Akane[i].read();
		for(int i = 1; i <= m; scanf("%lf", &tmp), ++i) Ranma[i].read();
		memset(G, INF, sizeof G);
		solve();
	}

	return 0;
}
