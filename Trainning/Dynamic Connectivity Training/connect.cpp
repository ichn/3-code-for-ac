#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

#define ln lct_node
#define lc ch[0]
#define rc ch[1]

struct lct_node {
	ln *fa, *ch[2], *mn;
	int rev, val;
	void up() {
		mn = this;
		if (lc) {
			if (lc->mn->val < mn->val)
				mn = lc->mn;
		}
		if (rc) {
			if (rc->mn->val < mn->val)
				mn = rc->mn;
		}
	}
	void down() {
		if (rev) {
			rev = 0;
			if (lc) {
				lc->rev ^= 1;
			}
			if (rc) {
				rc->rev ^= 1;
			}
			swap(lc, rc);
		}
	}
	bool is_r() {
		return !fa || (fa->lc != this && fa->rc != this);
	}
	int d() {
		return this == fa->ch[0];
	}
	void set_c(ln*son, int _d) {
		ch[_d] = son;
		if (son) son->fa = this;
	}
};

const int maxNode = 3e5 + 100;

ln pool[maxNode * 2], *loc = pool;

void rot(ln*x) {
	ln*y = x->fa;
	int d = x->d();
	y->set_c(x->ch[d], d^1);
	x->fa = y->fa;
	if (!y->is_r())
		y->fa->set_c(x, y->fa->rc == y);
	x->set_c(y, d);
	y->up();
}

void init(ln*x) {
	x->fa = x->lc = x->rc = NULL;
	x->val = INF;
	x->rev = 0;
}

ln*stk[maxNode * 2];
int tp;

void splay(ln*x) {
	for (stk[tp = 1] = x; !stk[tp]->is_r(); ++tp, stk[tp] = stk[tp - 1]->fa);
	for (; tp; stk[tp]->down(), --tp);
	for (ln*y = x->fa; !x->is_r(); rot(x), y = x->fa)
		if (!y->is_r()) {
			if (x->d() == y->d())
				rot(y);
			else rot(x);
		}
	x->up();
}

ln*access(ln*x) {
	ln*y = NULL;
	for (; x; y = x, x = x->fa) {
		splay(x);
		x->set_c(y, 1);
		x->up();
	}
	return y;
}

void make_root(ln*x) {
	access(x);
	splay(x);
	x->rev ^= 1;
}

void link(ln*u, ln*v) {
	make_root(u);
	u->fa = v;
}
inline char gchar() {
	char ret = getchar();
	for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
	return ret;
}

struct Edge {
	int st, ed;
	int u, v;
	Edge() {}
	Edge(int _st, int _ed, int _u, int _v) {
		st = _st, ed = _ed, u = _u, v = _v;
	}
} E[maxNode];
int cE;

struct Query {
	int type, u, v;
	int opr;
	Query() {}
	Query(int _type, int _u, int _v) {
		type = _type, u = _u, v = _v;
		opr = -1;
	}
} Q[maxNode];

map<pair<int, int>, int> Map;
typedef map<pair<int, int>, int>::iterator MI;

ln*qMinEdge(int _u, int _v) {
	ln*u = pool + _u, *v = pool + _v;
	make_root(u);
	access(v);
	splay(v);
	ln*x = v->lc, *ret = NULL;
	while (x) {
		if (x == u) {
			splay(u);
			ret = u->mn;
			break;
		}
		x = x->lc;
	}
	return ret;
}

int cnt_comp;

void addEdge(int e) {
	ln*w = loc + e, *u = pool + E[e].u, *v = pool + E[e].v;
	w->val = E[e].ed;
	link(w, u);
	link(w, v);
	--cnt_comp;
}

void disconnect(ln*u, ln*v) {
	make_root(u);
	access(v);
	splay(u);
	u->rc = v->fa = NULL;
	u->up();
}

void disconnect(ln*x) {
	++cnt_comp;
	ln*u = pool + E[x - loc].u, *v = pool + E[x - loc].v;
	disconnect(u, x);
	disconnect(x, v);
}

int n, m;

int main() {
	freopen("connect.in", "r", stdin);
	freopen("connect.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; ++i) {
		char s = gchar();
		if (s == '?') {
			Q[i].type = -1;
			continue;
		}
		int u, v;
		scanf("%d %d", &u, &v);
		if (v < u) swap(u, v);
		Q[i] = Query(s == '+', u, v);
		if (s == '-') {
			E[++cE] = Edge(Map[make_pair(u, v)], i, u, v);;
			Q[Map[make_pair(u, v)]].opr = cE;
			Q[i].opr = cE;
			Map[make_pair(u, v)] = INF;
		} else {
			Map[make_pair(u, v)] = i;
		}
	}
	for (MI i = Map.begin(); i != Map.end(); ++i) {
		if (i->second != INF) {
			E[++cE] = Edge(i->second, m + 1, i->first.first, i->first.second);
			Q[i->second].opr = cE;
		}
	}

	//for (int i = 1; i <= cE; ++i) {
	//	printf("%d %d %d %d\n", E[i].u, E[i].v, E[i].st, E[i].ed);
	//}
    //
	//for (int i = 1; i <= m; ++i) {
	//	printf("%d\n", Q[i].opr);
	//}

	cnt_comp = n;
	for (int i = 1; i <= n + cE; ++i) {
		init(pool + i);
	}
	loc = pool + n;
	for (int i = 1; i <= m; ++i) {
		if (Q[i].type == -1) {
			printf("%d\n", cnt_comp);
			continue;
		}
		if (Q[i].type == 1) {
			ln *x = qMinEdge(Q[i].u, Q[i].v);
			if (x == NULL) {
				addEdge(Q[i].opr);
			} else if (x->val < E[Q[i].opr].ed) {
	//			printf("%d %d\n", x->val, E[Q[i].opr].ed);
				disconnect(x);
				addEdge(Q[i].opr);
			}
		}
		if (Q[i].type == 0) {
			ln *x = qMinEdge(Q[i].u, Q[i].v);
	//		printf("%d\n", x->val);
			if (x - loc == Q[i].opr)
				disconnect(x);
		}
	}

	return 0;
}

