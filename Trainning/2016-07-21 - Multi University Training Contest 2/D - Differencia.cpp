#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 1000;
const int mod = 1e9 + 7;
int tr[maxN<<2], tg[maxN<<2], a[maxN], b[maxN];
int val[20][maxN], rnk[20][maxN][2];
int n, m, A, B;

int aa, bb, C = ~(1<<31), M = (1<<16)-1;
int rnd(int last) {
	aa = (36969 + (last >> 3)) * (aa & M) + (aa >> 16);
	bb = (18000 + (last >> 3)) * (bb & M) + (bb >> 16);
	return (C & ((aa << 16) + bb)) % 1000000000;
}

void build(int l, int r, int rt, int d) {
	tg[rt] = -1;
	if (l == r) {
		tr[rt] = (a[l] >= b[l]);
		val[d][l] = b[l];
		return ;
	}
	int mid = (l + r) >> 1;

	build(l, mid, rt<<1, d+1);
	build(mid+1, r, rt<<1|1, d+1);

	tr[rt] = tr[rt<<1] + tr[rt<<1|1];
	int lp = l, rp = mid+1, t = l;
	for (; t <= r; ) {
		while (lp <= mid && (rp > r || val[d+1][lp] <= val[d+1][rp]))
			val[d][t++] = val[d+1][lp++];
		while (rp <= r && (lp > mid || val[d+1][rp] <= val[d+1][lp]))
			val[d][t++] = val[d+1][rp++];
	}
	lp = l, rp = mid+1, t = l;
	for (; t <= r; ++t) {
		while (lp <= mid && val[d+1][lp] <= val[d][t])
			++lp;
		while (rp <= r && val[d+1][rp] <= val[d][t])
			++rp;
		rnk[d][t][0] = lp-1 < l ? 0 : lp-1;
		rnk[d][t][1] = rp-1 < mid + 1 ? 0 : rp-1;
	}
}

int ql, qr, qv;

int count(int d, int l, int r, int v) {
	int *t = upper_bound(val[d] + l, val[d] + r + 1, v);
	if (t == val[d] + l) return 0;
	--t;
	return t - (val[d] + l) + 1;
}

void paint(int l, int r, int rt, int d, int pos) {
	if (ql <= l && r <= qr) {
		tg[rt] = pos;
		tr[rt] = pos == 0 ? 0 : pos - l + 1;
		return ;
	}
	int mid=(l+r)>>1;
	if (tg[rt] != -1) {
		tg[rt<<1] = tr[rt] == 0 ? 0 : rnk[d][l + tr[rt] - 1][0];
		tg[rt<<1|1] = tr[rt] == 0 ? 0 : rnk[d][l + tr[rt] - 1][1];
		tr[rt<<1] = tg[rt<<1] == 0 ? 0 : tg[rt<<1] - l + 1;
		tr[rt<<1|1] = tg[rt<<1|1] == 0 ? 0 : tg[rt<<1|1] - mid;
		tg[rt] = -1;
	}
	if (ql <= mid) paint(l, mid, rt<<1, d+1, rnk[d][pos][0]);
	if (mid < qr) paint(mid+1, r, rt<<1|1, d+1, rnk[d][pos][1]);

	tr[rt] = tr[rt<<1] + tr[rt<<1|1];
}

void paint() {
	int rk = count(0, 1, n, qv);
	paint(1, n ,1, 0, rk);
}


int query(int l, int r, int rt, int d) {
	if (ql <= l && r <= qr)
		return tr[rt];
	int mid=(l+r)>>1;
	if (tg[rt] != -1) {
		tg[rt<<1] = tr[rt] == 0 ? 0 : rnk[d][l + tr[rt] - 1][0];
		tg[rt<<1|1] = tr[rt] == 0 ? 0 : rnk[d][l + tr[rt] - 1][1];
		tr[rt<<1] = tg[rt<<1] == 0 ? 0 : tg[rt<<1] - l + 1;
		tr[rt<<1|1] = tg[rt<<1|1] == 0 ? 0 : tg[rt<<1|1] - mid;
		tg[rt] = -1;
	}
	int ret = 0;
	if (ql <= mid) ret += query(l, mid, rt<<1, d+1);
	if (mid < qr) ret += query(mid+1, r, rt<<1|1, d+1);
	return ret;
}

int main() {
#ifdef lol
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif

	//clock_t bg = clock();
	int tCase;
	scanf("%d", &tCase);
	while (tCase--) {
		scanf("%d %d %d %d", &n, &m, &A, &B);
		aa = A, bb = B;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &b[i]);
		build(1, n, 1, 0);

		int sum = 0;
		int lst = 0;
		for (int i = 1; i <= m; ++i) {
			ql = rnd(lst) % n + 1;
			qr = rnd(lst) % n + 1;
			qv = rnd(lst) + 1;
			if (qr < ql) swap(ql, qr);
			if ((ql + qr + qv) & 1) {
				paint();
			} else {
				lst = query(1, n, 1, 0);
				sum += 1LL * lst * i % mod;
				if (sum >= mod) sum -= mod;
			}
		}
		printf("%d\n", sum);
	}

	//cout << 1.0 * (clock() - bg) / CLOCKS_PER_SEC << endl;

	return 0;
}
