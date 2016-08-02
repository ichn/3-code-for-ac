#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int maxn = 1e5+10000;
const int maxm = maxn<<4;
const int INF = 0x3f3f3f3f;

struct Line {
	DB k, b;
} T[maxm], L[maxm];

struct Point {
	DB x, y;
} a[maxn];

int n, m, loc;
DB X[maxn];
int root[maxn], ls[maxm], rs[maxm];

DB cross_x(Line a, Line b) {
	return (a.b-b.b)/(b.k-a.k);
}
DB evaluate(DB x, Line c) {
	return c.k*x+c.b;
}

void add(int u, int&v, int l, int r, Line s) {
	v = ++loc;
	ls[v]=ls[u], rs[v]=rs[u];
	if (u) {
		T[v] = T[u];
	} else {
		ls[0] = rs[0] = 0;
		T[v].b=INF, T[v].k=-(1e-10);
	}
	DB x = cross_x(s, T[v]);
	if (x<=X[l] || X[r]<=x) {
		if (evaluate(X[l], s) < evaluate(X[l], T[v]))
			T[v] = s;
		return ;
	}
	int mid = (l+r)>>1;
	if (x <= X[mid]) {
		if (evaluate(X[l], s) > evaluate(X[l], T[v]))
			swap(s, T[v]);
		add(ls[u], ls[v], l, mid, s);
	} else {
		if (evaluate(X[r], s) > evaluate(X[r], T[v]))
			swap(s, T[v]);
		add(rs[u], rs[v], mid, r, s);
	}
}

DB find(int u, int l, int r, DB x) {
	if (!u)
		return INT_MAX;
	int mid = (l+r)>>1;
	if (x <= X[mid]) {
		return min(evaluate(x, T[u]), find(ls[u], l, mid, x));
	} else return min(evaluate(x, T[u]), find(rs[u], mid+1, r, x));
}

int main() {

	freopen("point.in", "r", stdin), freopen("point.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; ++i) {
		scanf("%lf %lf", &a[i].x, &a[i].y);
		a[i].x = log(a[i].x);
		a[i].y = log(a[i].y);
		X[i] = a[i].x;
	}
	sort(X+1, X+n+1);
	for (int i=1; i<=m; ++i) {
		scanf("%lf %lf", &L[i].b, &L[i].k);
		L[i].b = log(L[i].b);
		L[i].k = -L[i].k;
	}
	
	loc = 1;
	root[0] = 1;
	ls[1] = rs[1] = 0;
	T[1].b = INF, T[1].k = -(1e-10);
	for (int i=1; i<=m; ++i) {
		add(root[i-1], root[i], 1, n, L[i]);
	}

	for (int i=1; i<=n; ++i) {
		if (find(root[m], 1, n, a[i].x) >= a[i].y) {
			puts("-1");
		} else {
			int l=1, r=m;
			while (l < r) {
				int mid = (l+r)>>1;
				if (find(root[mid], 1, n, a[i].x) >= a[i].y)
					l = mid+1;
				else r = mid;
			}
			printf("%d\n", l);
		}
	}

	return 0;
}
