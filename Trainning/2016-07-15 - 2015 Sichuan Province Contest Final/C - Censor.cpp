#include <bits/stdc++.h>
using namespace std;

const int maxN = 5e6 + 100;

struct ch {
	ch *pre, *nxt;
	char val;
	void init() {
		pre = NULL;
		nxt = NULL;
	}
	ch() {
		pre = NULL;
		nxt = NULL;
	}
} pool[maxN], *lcl = pool, *hd, *tl, *lst, *mark;

char w[maxN], p[maxN], t[maxN];
int f[maxN];
int lw, lp;


bool solve() {

	int j = 0;
	mark = NULL;
	for (ch*i = lst->nxt; i != NULL; i = i->nxt) {
		while (j && w[j] != i->val) j = f[j];
		if (w[j] == i->val) ++j;
		if (j == lw) {
			mark = i;
			break;
		}
	}
	if (mark == NULL) return false;
	for (int i = 0; i < lw; ++i) {
		mark->nxt->pre = mark->pre;
		mark->pre->nxt = mark->nxt;
		mark = mark->pre;
	}
	lst = mark;
	j = lw;
	while (lst != hd && j != 0) {
		--j;
		lst = lst->pre;
	}
	return true;
}

void print(ch*x) {
	if (x == NULL) return ;
	if (x == hd) return ;
	if (x == tl) return ;
	putchar(x->val);
	print(x->nxt);
}


int main() {
#ifdef lol
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif

	while (scanf("%s\n%s\n", w, p) != EOF) {

		lp = strlen(p), lw = strlen(w);
		int m = strlen(w);
		f[0] = 0, f[1] = 0;
		for (int i = 1; i < m; ++i) {
			int j = f[i];
			while (j && w[i] != w[j]) j = f[j];
			f[i+1] = w[i] == w[j] ? j+1 : 0;
		}
		for (int i = 0; i < maxN; ++i)
			pool[i].init();
		lcl = pool;
		hd = lcl++, tl = lcl++;
		hd->nxt = tl;
		tl->pre = hd;
		for (int i = 0; i < lp; ++i) {
			lcl->nxt = tl;
			lcl->pre = tl->pre;
			tl->pre->nxt = lcl;
			tl->pre = lcl;
			lcl->val = p[i];
			lcl++;
		}

		lst = hd;
		while (solve());
		print(hd->nxt);
		puts("");
	}

	return 0;
}
