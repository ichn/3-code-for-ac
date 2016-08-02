#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
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

struct Querys {
	int	t, a, b, c;
	int id;
} Q[maxn];
int col[maxn], n, m, a, b, p;
int nxt[maxn], val[maxn], pos[maxn];

int tr[maxn<<2], tg[maxn<<2];
void upd(int &a, int b) {
	if (a < b) a = b;
}

/*
 * 区间取max
 * 单点询问
 * */

void up(int rt) {
	tr[rt] = max(tr[rt<<1], tr[rt<<1|1]);
}

void down(int rt) {
	upd(tr[rt<<1], tg[rt]);
	upd(tg[rt<<1], tg[rt]);
	upd(tr[rt<<1|1], tg[rt]);
	upd(tg[rt<<1|1], tg[rt]);
}

int query(int p, int l, int r, int rt) {
	if (l == r) {
		return tr[rt];
	}
	int mid = (l+r)>>1;
	down(rt);
	if (p <= mid) return query(p, l, mid, rt<<1);
	return query(p, mid+1, r, rt<<1|1);
}

void modify(int ql, int qr, int v, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		upd(tr[rt], v);
		upd(tg[rt], v);
		return ;
	}
	int mid = (l+r)>>1;
	down(rt);
	if (ql <= mid) modify(ql, qr, v, l, mid, rt<<1);
	if (mid < qr) modify(ql, qr, v, mid+1, r, rt<<1|1);
	up(rt);
}

void build(int l, int r, int rt) {
	tg[rt] = 0;
	if (l == r) {
		tr[rt] = -1;
		return ;
	}
	int mid = (l+r)>>1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	up(rt);
}

int main() {
	freopen("line.in", "r", stdin);
	freopen("line.out", "w", stdout);
	fr(n, m);
	int c = 0;
	pse(nxt, -1);
	rep(i, 1, m) {
		fr(Q[i].t);
		if (Q[i].t == 1) {
			++c;
			fr(Q[i].a, Q[i].b, Q[i].c);
			Q[i].id = c;
			nxt[c] = nxt[Q[i].c];
			nxt[Q[i].c] = c;
		} else {
			fr(Q[i].a);
		}
	}
	int id = 0;
	for (int i=0; i!=-1; i=nxt[i]) {
	//	printf("%d ", i);
		val[i] = id++;
		pos[val[i]] = i;
	}
	//puts("");
	build(0, n, 1);
	rep(i, 1, m) {
		if (Q[i].t == 1) {
			modify(Q[i].a, Q[i].b, val[Q[i].id], 1, n, 1);
		} else {
			printf("%d\n", pos[query(Q[i].a, 1, n, 1)]);
		}
	}

	return 0;
}

