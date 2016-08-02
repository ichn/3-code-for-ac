#include <bits/stdc++.h>
using namespace std;
const int maxn = 30000 + 200;
const int INF = 0x3f3f3f3f;
struct splay_node {
	splay_node *fa, *ch[2];
	int val, sum, max_v;
	splay_node() {
		sum = 0, max_v = -INF;
		fa = ch[0] = ch[1] = NULL;
	}
	splay_node(int val):val(val) {
		sum = max_v = val;
		fa = ch[0] = ch[1] = NULL;
	}
	void setc(splay_node *t, int d) {
		ch[d] = t;
		if(t != NULL) {
			t->fa = this;
		}
	}
	int d() {
		return this == fa->ch[1];
	}
	bool is_root() {
		return fa == NULL || (this != fa->ch[0] && this != fa->ch[1]);
	}
} *T[maxn];
void push_up(splay_node *x) {
	x->max_v = max(x->val, max((x->ch[0] ? x->ch[0]->max_v : -INF), (x->ch[1] ? x->ch[1]->max_v : -INF)));
	x->sum = (x->ch[0] ? x->ch[0]->sum : 0) + (x->ch[1] ? x->ch[1]->sum : 0) + x->val;
}
void rot(splay_node *&x) {
	splay_node *y = x->fa;
	int d = x->d();
	if(y->is_root()) {
		x->fa = y->fa;
	} else {
		y->fa->setc(x, y->d());
	}
	y->setc(x->ch[d ^ 1], d);
	x->setc(y, d ^ 1);
	push_up(y);
}
void splay(splay_node *x) {
	for(; !x->is_root(); ) {
		if(x->fa->is_root()) {
			rot(x);
		} else {
			if(x->d() == x->fa->d()) {
				rot(x->fa);
			} else {
				rot(x);
			}
			rot(x);
		}
	}
	push_up(x);
}
splay_node* access(splay_node *x) {
	splay_node *c;
	for(c = NULL; x; c = x, x = x->fa) {
		splay(x);
		x->setc(c, 1);
		push_up(x);
	}
	return c;
}

int n, q;
vector<int> g[maxn];
int read() {
	int a;
	scanf("%d", &a);
	return a;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i) {
		T[i] = new splay_node(read());
	}
	queue<int> que;
	bitset<maxn> vis = 0;
	que.push(1);
	vis[1] = 1;
	while(!que.empty()) {
		int t = que.front(); que.pop();
		for(size_t i = 0; i < g[t].size(); ++i) {
			int v = g[t][i];
			if(vis[v] == 0) {
				vis[v] = 1;
				T[v]->fa = T[t];
				que.push(v);
			}
		}
	}
	char ope[10];
	scanf("%d", &q);
	while(q--) {
		scanf("%s", ope);
		if(ope[0] == 'C') {
			int p, v;
			scanf("%d%d", &p, &v);
			splay(T[p]);
			T[p]->val = v;
			push_up(T[p]);
		} else {
			int u, v, ans;
			scanf("%d%d", &u, &v);
			access(T[u]);
			splay_node *lca = access(T[v]);
			splay(T[u]);
			if(lca == T[u]) {
				if(ope[1] == 'M') {
					ans = max((T[u]->ch[1] ? T[u]->ch[1]->max_v : -INF), T[u]->val);
				} else {
					ans = (T[u]->ch[1] ? T[u]->ch[1]->sum : 0) + T[u]->val;
				}
			} else {
				if(ope[1] == 'M') {
					ans = max(max(T[u]->max_v, lca->ch[1] ? lca->ch[1]->max_v : -INF), lca->val);
				} else {
					ans = T[u]->sum + lca->val + (lca->ch[1] ? lca->ch[1]->sum : 0);
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
