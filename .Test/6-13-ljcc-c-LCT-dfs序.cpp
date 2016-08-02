#define _Debug
#include <bits/stdc++.h>
using namespace std;

const int maxVer = 1e5 + 100;
const int maxArc = 2e5 + 100;

const int maxLvL = 21;

int n, m;

namespace Edge {
	int h[maxVer], e, to[maxArc], nxt[maxArc];

	void iniEdge() {
		memset(h, -1, sizeof h);
		e = 0;
	}
	void addArc(int u, int v) {
		nxt[e] = h[u], to[e] = v, h[u] = e++;
	}
	void addEdge(int u, int v) {
		addArc(u, v);
		addArc(v, u);
	}
};
using namespace Edge;

namespace dfsSeq {
	int rt, _rt;
	int pa[maxVer][maxLvL], dep[maxVer], dfi[maxVer], dfo[maxVer], dfn[maxVer];
	int dfs_clk;

	long long tr[maxVer<<2], tg[maxVer<<2];

	void dfs(int u) {
		dfi[u] = ++dfs_clk;
		dfn[dfs_clk] = u;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (v != pa[u][0]) {
				pa[v][0] = u;
				dep[v] = dep[u]+1;
				dfs(v);
			}
		}
		dfo[u] = dfs_clk;
	}

	void bldSegTree(int l, int r, int rt) {
		if (l == r) {
			tr[rt] = dep[dfn[l]];
			return ;
		}
		int mid = (l+r)>>1;
		tg[rt] = 0;
		bldSegTree(l, mid, rt<<1);
		bldSegTree(mid+1, r, rt<<1|1);
		tr[rt] = tr[rt<<1] + tr[rt<<1|1];
	}


	void mdf(int ql, int qr, int v, int l, int r, int rt) {
		if (qr < ql) return ;
		if (ql <= l && r <= qr) {
			tg[rt] += v;
			tr[rt] += v * (r-l+1);
			return ;
		}
		int mid = (l + r) >> 1;
		tg[rt<<1] += tg[rt], tg[rt<<1|1] += tg[rt];
		tr[rt<<1] += tg[rt]*(mid-l+1), tr[rt<<1|1] += tg[rt]*(r-mid);
		tg[rt] = 0;

		if (ql <= mid) mdf(ql, qr, v, l, mid, rt<<1);
		if (mid < qr) mdf(ql, qr, v, mid+1, r, rt<<1|1);
		tr[rt] = tr[rt<<1] + tr[rt<<1|1];
	}

	long long qry(int ql, int qr, int l, int r, int rt) {
		if (ql <= l && r <= qr) {
			return tr[rt];
		}
		int mid = (l+r)>>1;
		tg[rt<<1] += tg[rt], tg[rt<<1|1] += tg[rt];
		tr[rt<<1] += tg[rt]*(mid-l+1), tr[rt<<1|1] += tg[rt]*(r-mid);
		tg[rt] = 0;

		long long ret = 0;
		if (ql <= mid) ret += qry(ql, qr, l, mid, rt<<1);
		if (mid < qr) ret += qry(ql, qr, mid+1, r, rt<<1|1);
		return ret;
	}

	void mdfSubTree(int x, int f, int v) {
		if (f == pa[x][0]) mdf(dfi[x], dfo[x], v, 1, n, 1);
		else {
			mdf(1, dfi[f]-1, v, 1, n, 1);
			mdf(dfo[f]+1, n, v, 1, n, 1);
		}
	}

	double qrySubTree(int x) {
		long long siz = 0, sum = 0;
		if (x == _rt) {
			siz = n;
			sum = qry(1, n, 1, n, 1);
		} else if (dfi[_rt] < dfi[x] || dfi[_rt] > dfo[x]) {
			sum = qry(dfi[x], dfo[x], 1, n, 1);
			siz = dfo[x] - dfi[x] + 1;
		} else {
			int y = _rt;
			for (int i = maxLvL-1; 0 <= i; --i)
				if (dep[pa[y][i]] >= dep[x]+1)
					y = pa[y][i];
			if (1 <= dfi[y]-1) {
				sum += qry(1, dfi[y]-1, 1, n, 1);
				siz += dfi[y]-1;
			}
			if (dfo[y]+1 <= n) {
				sum += qry(dfo[y]+1, n, 1, n, 1);
				siz += n-dfo[y];
			}
		}
		return (double)sum/siz;
	}

	void iniTree() {
		rt = 1;
		_rt = 1;
		pa[rt][0] = 0;
		dep[0] = 0;
		dep[rt] = 1;
		dfs_clk = 0;

		dfs(rt);

		for (int i = 1; i < maxLvL; ++i)
			for (int v = 1; v <= n; ++v)
				pa[v][i] = pa[pa[v][i-1]][i-1];

		memset(tr, 0, sizeof tr);
		memset(tg, 0, sizeof tg);

		bldSegTree(1, n, 1);
	}
};
using namespace dfsSeq;

namespace LinkCutTree {
#define ln lct_node
#define lc ch[0]
#define rc ch[1]
	struct lct_node {
		ln*fa, *ch[2], *ep[2];
		int rev;
		bool is_r() {
			return !fa || (this != fa->lc && this != fa->rc);
		}
		int d() {
			return this == fa->ch[0];
		}
		void down() {
			if (rev) {
				rev = 0;
				if (lc) {
					lc->rev ^= 1;
					swap(lc->lc, lc->rc);
					swap(lc->ep[0], lc->ep[1]);
				}
				if (rc) {
					rc->rev ^= 1;
					swap(rc->lc, rc->rc);
					swap(rc->ep[0], rc->ep[1]);
				}
			}
		}
		void up() {
			ep[0] = ep[1] = this;
			if (lc) ep[0] = lc->ep[0];
			if (rc) ep[1] = rc->ep[1];
		}
		void set_c(ln*s, int r) {
			ch[r] = s;
			if (s) s->fa = this;
		}
		void ini() {
			fa = lc = rc = NULL;
			ep[0] = ep[1] = NULL;
			rev = 0;
		}
	} pl[maxVer], *loc;

	void rot(ln*x) {
		ln*y = x->fa;
		int d = x->d();
		y->set_c(x->ch[d], d^1);
		x->fa = y->fa;
		if (!y->is_r())
			y->fa->set_c(x, y->fa->rc==y);
		x->set_c(y, d);
		y->up();
	}

	ln*stk[maxVer];
	int tp;
	void splay(ln*x) {
		for (stk[tp=1]=x; !stk[tp]->is_r(); ++tp, stk[tp]=stk[tp-1]->fa);
		for (; tp; stk[tp]->down(), --tp);
		for (ln*y=x->fa ; !x->is_r(); rot(x), y=x->fa)
			if (!y->is_r()) {
				if (y->d() == x->d())
					rot(y);
				else rot(x);
			}
		x->up();
	}

	ln*access(ln*x) {
		ln*y = NULL;
		for (; x; y=x, x=x->fa) {
			splay(x);
			if (x->rc) {
				mdfSubTree(x->rc->ep[0]-pl, x-pl, 1);
			}
			if (y) {
				mdfSubTree(y->ep[0]-pl, x-pl, -1);
			}
			x->set_c(y, 1);
			x->up();
		}
		return y;
	}
	
	void mkRoot(ln*x) {
		access(x);
		splay(x);
		swap(x->lc, x->rc);
		swap(x->ep[0], x->ep[1]);
		x->rev ^= 1;
	}

	void iniLCT() {
		loc = pl;
		for (int i = 1; i <= n; ++i) {
			(loc + i)->ini();
		}
		for (int i = 1; i <= n; ++i) {
			if (i == rt) continue;
			(loc + i)->fa = (loc + pa[i][0]);
		}
	}

};
using namespace LinkCutTree;

struct Debug {
	void chkSegTree() {
	// 1 加 2 查
		int a, b;
		scanf("%d %d", &a, &b);
		int l, r, x, t;
		for (int i = 1; i <= b; ++i) {
			scanf("%d %d %d %d", &t, &l, &r, &x);
			if (t == 0)
				mdf(l, r, x, 1, a, 1);
			else printf("%d\n", qry(l, r, 1, a, 1));
		}
	}
};

int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);

	iniEdge();

	scanf("%d %d", &n, &m);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}

	iniTree();
	iniLCT();

	for (int i = 1, t, x; i <= m; ++i) {
		scanf("%d %d", &t, &x);
		if (t == 1) {
			access(loc + x);
		} else if (t == 2) {
			mkRoot(loc + x);
			_rt = x;
		} else {
			double ans = qrySubTree(x);
			printf("%.10lf\n", ans);
		}
	}

	return 0;
}


