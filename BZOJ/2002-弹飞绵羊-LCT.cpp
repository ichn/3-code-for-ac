#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))
const int maxn = 200000 + 10;
 
struct splay_node {
	splay_node *fa, *ch[2];
	int size;
	void maintain() {
		size = ch[0]->size + ch[1]->size + 1;
	}
	int d() {
		return this == fa->ch[1];
	}
	void set_ch(splay_node *t, int d) {
		(ch[d] = t)->fa = this;
		maintain();
	}
	bool root() {
		return this != fa->ch[0] && this != fa->ch[1];
	}
} null[maxn];
void rot(splay_node *x) {
	int d = x->d();
	splay_node *y = x->fa;
	y->set_ch(x->ch[d ^ 1], d);
	if(y->root()) {
		x->fa = y->fa;
	} else {
		y->fa->set_ch(x, y->d());
	}
	x->set_ch(y, d ^ 1);
}
void splay(splay_node *x) {
	while(!x->root()) {
		if(x->fa->root()) {
			rot(x);
		} else if(x->d() == x->fa->d()) {
			rot(x->fa), rot(x);
		} else {
			rot(x), rot(x);
		}
	}
}
void access(splay_node *x) {
	for(splay_node *y = null; x != null; y = x, x = x->fa) {
		splay(x);
		x->set_ch(y, 1);
	}
}
 
int n, m;
#define nd(i) (null + i)
int main() {
	scanf("%d", &n);
	splay_node *x;
	int ope, a, b;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a);
		(x = nd(i))->ch[0] = x->ch[1] = null;
		x->fa = nd(min(i + a, n + 1));
	}
	(x = nd(n + 1))->ch[0] = x->ch[1] = x->fa = null->ch[0] = null->ch[1] = null->fa = null;
	scanf("%d", &m);
	while(m--) {
		scanf("%d%d", &ope, &a);
		x = nd(++a);
		if(ope == 1) {
			access(x);
			splay(x);
			printf("%d\n", x->ch[0]->size);
		} else {
			scanf("%d", &b);
			splay(x);
			x->ch[0]->fa = x->fa;
			x->ch[0] = null;
			x->fa = nd(min(a + b, n + 1));
		}
	}
	return 0;
}
