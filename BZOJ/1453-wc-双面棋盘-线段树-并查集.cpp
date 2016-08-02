#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 10;
struct dsu {
	vector<int> fa;
	void init(int _n) {
		fa.resize(_n+1);
		while (_n--) fa[_n]=_n;
	}
	int find(int x) {
		return fa[x]==x ? x : fa[x]=find(fa[x]);
	}
	void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
};

int n, m, a[maxn][maxn];
int n2, n3, n4;
int vis[maxn<<2];

struct seg_node {
	dsu s;
	int w, b;
	int&at(int x) { return s.fa[x]; }
	seg_node() { w = b = 0; }
} t[maxn<<2];

#define lson l, mid, rt<<1
#define rson mid+1, r, rt<<1|1

void upd(int rt, int l, int r) {
	int L=rt<<1, R=rt<<1|1, mid=(l+r)>>1;
	t[rt].b = t[L].b+t[R].b;
	t[rt].w = t[L].w+t[R].w;
	t[rt].s.init(n4);
	for (int j=1; j<=n2; ++j) {
		t[rt].s.merge(j, t[L].s.find(j));
		t[rt].s.merge(j+n2, t[R].s.find(j)+n2);
	}
	for (int j=1; j<=n; ++j) {
		if (a[mid][j] == a[mid+1][j]) {
			if (t[rt].s.same(j+n, j+n2))
				continue;
			t[rt].s.merge(j+n, j+n2);
			t[rt].w -= a[mid][j]==0;
			t[rt].b -= a[mid][j]==1;
		}
	}
	for (int j=1; j<=n4; ++j)
		t[rt].s.find(j);
	memset(vis, 0, sizeof vis);
	for (int j=1; j<=n; ++j) {
		if (!vis[t[rt].at(j)]) {
			vis[t[rt].at(j)] = j;
			t[rt].at(j) = j;
		} else t[rt].at(j) = vis[t[rt].at(j)];
	}
	for (int j=n3+1; j<=n4; ++j) {
		if (!vis[t[rt].at(j)]) {
			vis[t[rt].at(j)] = j-n2;
			t[rt].at(j) = j-n2;
		} else t[rt].at(j) = vis[t[rt].at(j)];
	}
	for (int j=1; j<=n; ++j)
		t[rt].at(j+n) = t[rt].at(j+n3);
	for (int j=n2+1; j<=n4; ++j)
		t[rt].at(j) = j;
}

void build(int l, int r, int rt) {
	if (l == r) {
		t[rt].s.init(n4);
		t[rt].w = a[l][1]==0;
		t[rt].b = a[l][1]==1;
		t[rt].s.merge(1+n, 1);
		for (int j=2; j<=n; ++j) {
			t[rt].s.merge(j+n, j);
			if (a[l][j] == a[l][j-1])
				t[rt].s.merge(j, j-1);
			else t[rt].w += a[l][j]==0, t[rt].b += a[l][j]==1;
		}
		return ;
	}
	int mid = (l+r)>>1;
	build(lson), build(rson);
	upd(rt, l, r);
}

void modify(int l, int r, int rt, int p) {
	if (l == r) {
		t[rt].s.init(n4);
		t[rt].w = a[l][1]==0;
		t[rt].b = a[l][1]==1;
		t[rt].s.merge(1+n, 1);
		for (int j=2; j<=n; ++j) {
			t[rt].s.merge(j+n, j);
			if (a[l][j] == a[l][j-1])
				t[rt].s.merge(j, j-1);
			else t[rt].w += a[l][j]==0, t[rt].b += a[l][j]==1;
		}
		return ;	
	}
	int mid = (l+r)>>1;
	if (p <= mid) modify(lson, p);
	else modify(rson, p);
	upd(rt, l, r);
}

int main() {
	scanf("%d", &n);
	n2 = n*2, n3 = n*3, n4 = n*4;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			scanf("%d", &a[i][j]);
	build(1, n, 1);
	scanf("%d", &m);
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		a[x][y] ^= 1;
		modify(1, n, 1, x);
		printf("%d %d\n", t[1].b, t[1].w);
	}
	return 0;
}

