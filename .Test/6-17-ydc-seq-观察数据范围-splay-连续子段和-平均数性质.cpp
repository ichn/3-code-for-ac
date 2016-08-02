#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
	template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
	template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
	template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
		return ret;
	}
};
using namespace my_useful_tools;

const int maxn = 1e5 + 100;

int a[maxn], n, m, K;

#define sn splay_node
#define lc ch[0]
#define rc ch[1]
const int maxNode = 1e5 + 100;
const int MinInt = -111111111;
typedef LL myInt;
struct splay_node {
	sn*fa, *ch[2];
	myInt id, val, ls[20], rs[20], sz;
	myInt pl[20], pr[20], ms[20];
	LL sum;
	void upd(); 
	int d() {
		return this == fa->lc;
	}
	void set_c(sn*c, int d) {
		ch[d] = c;
		if (c) c->fa = this;
	}
} pl[maxNode], *loc = pl, *rt;

void splay_node::upd() {
	sz = 1;
	if (lc) sz += lc->sz;
	if (rc) sz += rc->sz;
	sum = val;
	if (lc) sum += lc->sum;
	if (rc) sum += rc->sum;

	reu(i, 1, 20) {
		ms[i] = 0;
		pl[i] = 0;
		pr[i] = 0;
		if (lc && lc->ms[i] > ms[i])
			ms[i] = lc->ms[i], 
				pl[i] = lc->pl[i]-((lc->rc?lc->rc->sz:0)+1),
				pr[i] = lc->pr[i]-((lc->rc?lc->rc->sz:0)+1);
		if (rc && rc->ms[i] > ms[i])
			ms[i] = rc->ms[i], 
				pl[i] = rc->pl[i]+((rc->lc?rc->lc->sz:0)+1), 
				pr[i] = rc->pr[i]+((rc->lc?rc->lc->sz:0)+1);

		if (lc && rc)
			red(j, i-1, 0) {
				myInt s = lc->rs[j] + val + rc->ls[i-j-1];
				if (s > ms[i])
					ms[i] = s, pl[i] = -j, pr[i] = -j+i-1;
			}
		if (lc && !rc) {
			myInt s = val + lc->rs[i-1];
			if (s > ms[i])
				ms[i] = s, pl[i] = -i+1, pr[i] = 0;
		}
		if (rc && !lc) {
			myInt s = val + rc->ls[i-1];
			if (s > ms[i])
				ms[i] = s, pl[i] = 0, pr[i] = i-1;
		}
		if (!lc && !rc && i==1)
			ms[i] = val, pl[i] = 0, pr[i] = 0;

		if (lc && i <= lc->sz)
			ls[i] = lc->ls[i];
		else if ((lc?lc->sz:0)+1 == i)
			ls[i] = (lc?lc->sum:0)+val;
		else if (rc && i <= sz)
			ls[i] = (lc?lc->sum:0) + val + rc->ls[i-(lc?lc->sz:0)-1];
		else ls[i] = MinInt;

		if (rc && i <= rc->sz)
			rs[i] = rc->rs[i];
		else if ((rc?rc->sz:0)+1 == i)
			rs[i] = (rc?rc->sum:0)+val;
		else if (lc && i <= sz)
			rs[i] = (rc?rc->sum:0) + val + lc->rs[i-(rc?rc->sz:0)-1];
		else rs[i] = MinInt;
	}
}


sn*newNode(int p) {
	loc->id = p;
	loc->val = a[p];
	loc->fa = NULL, loc->lc = NULL, loc->rc = NULL;
	loc->ls[0] = loc->rs[0] = loc->ms[0] = 0;
	return loc++;
}

void build(sn*&x, int l, int r) {
	if (r < l) {
		x = NULL;
		return ;
	}
	int mid = (l+r)>>1;
	x = newNode(mid);
	build(x->lc, l, mid-1);
	if (x->lc) x->lc->fa = x;
	build(x->rc, mid+1, r);
	if (x->rc) x->rc->fa = x;
	x->upd();
}

void rot(sn*x) {
	sn*y = x->fa;
	int d = x->d();
	y->set_c(x->ch[d], d^1);
	x->fa = y->fa;
	if (y->fa) y->fa->set_c(x, y->fa->rc==y);
	x->set_c(y, d);
	y->upd();
}

sn*lb, *rb;

void splay(sn*x, sn*g) {
	if (x == g) return ;
	for (sn*y = x->fa; x->fa != g; rot(x), y = x->fa)
		if (y->fa != g) {
			if (x->d() == y->d())
				rot(y);
			else rot(x);
		}
	x->upd();
	if (g == NULL) rt = x;
}

sn*select(int k) {
	sn*u = rt;
	for (;;) {
		if (u->lc && k <= u->lc->sz)
			u = u->lc;
		else if (u->rc && (u->lc?u->lc->sz:0)+1<k)
			k -= (u->lc?u->lc->sz:0)+1, u = u->rc;
		else break;
	}
	return u;
}

void remove(int l, int r) {
	sn *ln = select(l);
	sn *rn = select(r+2);
	splay(ln, NULL);
	splay(rn, ln);
	rn->lc->fa = NULL;
	rn->lc = NULL;
	rn->upd();
	ln->upd();
}

void qry(int l, int r) {
	sn *ln = select(l);
	sn *rn = select(r+2);
	splay(ln, NULL);
	splay(rn, ln);
	sn*p = rn->lc;
	static myInt ms[20], pl[20], pr[20];
	reu(i, 1, 20) ms[i] = p->ms[i];
	reu(i, 1, 20) pl[i] = p->pl[i];
	reu(i, 1, 20) pr[i] = p->pr[i];
	splay(p, NULL);
	int pp = (p->lc?p->lc->sz:0);
	int pL = 0, pR = 0;
	double avg = 0.0;
	for (int i = K; i < (K<<1); ++i)
		if ((double)ms[i] / i > avg) {
			avg = (double)ms[i] / i;
			pL = pl[i], pR = pr[i];
		}
	printf("%d %d\n", pL+pp, pR+pp);
	remove(pL+pp, pR+pp);
}

int main() {

	file(seq);

	fr(n, m, K);
	lb = newNode(0);
	rb = newNode(n+1);
	lb->rc = rb, rb->fa = lb, rt = lb;
	rep(i, 1, n) fr(a[i]);
	build(rb->lc, 1, n);
	rb->lc->fa = rb;
	rb->upd(), lb->upd();
	int L, R;
	while (m--) {
		fr(L, R);
		qry(L, R);
	}
 
	return 0;
}


