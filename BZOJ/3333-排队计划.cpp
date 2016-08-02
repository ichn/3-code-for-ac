#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define Edges(_i, _u, _e) for(int _i = _e.head[_u]; _i != -1; _i = _e.next[_i])
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
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
	const int maxv = 100, maxe = 100;
	struct Edge {
		int edge, head[maxv], to[maxe], next[maxe];
		Edge() { edge = 0; memset(head, -1, sizeof head); }
		void addedge(int u, int v) {
			to[edge] = v, next[edge] = head[u];
			head[u] = edge++;
		}
	};
};
using namespace my_useful_tools;


const int MaxN = 5e5 + 100;
int n, m, r;
int a[MaxN];

vector<int> val;
map<int, int> hs;

int f[MaxN], c[MaxN];

void modify(int p, int d) {
	for(; p <= r; c[p] += d, p += p&-p);
}
int get_sum(int p) {
	int ret = 0;
	for(; p; ret += c[p], p -= p&-p);
	return ret;
}


ipir T[MaxN << 2];

void push_up(int p) {
	T[p] = min(T[p<<1], T[p<<1|1]);
}
void build(int l, int r, int rt) {
	if(l == r) {
		T[rt] = mp(a[l], l);
		return ;
	}
	int mid = (l+r) >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	push_up(rt);
}
int ql, qr, p;
ipir query(int l, int r, int rt) {
	if(ql <= l && r <= qr)
		return T[rt];
	int mid = (l+r) >> 1;
	ipir ret = mp(INF, INF);
	if(ql <= mid) ret = min(ret, query(l, mid, rt << 1));
	if(mid < qr) ret = min(ret, query(mid+1, r, rt<<1|1));
	return ret;
}
void change(int l, int r, int rt) {
	if(l == r) {
		T[rt].first = INF;
		return ;
	}
	int mid = (l+r) >> 1;
	if(p <= mid) change(l, mid, rt<<1);
	else change(mid + 1, r, rt<<1|1);
	push_up(rt);
}

int main() {
#ifdef love_sbit
	file(3333);
#endif
	fr(n, m);

	rep(i, 1, n) fr(a[i]), val.pb(a[i]);
	sort(val.begin(), val.end());
	val.erase(unique(val.begin(), val.end()), val.end());
	r = val.size();
	reu(i, 0, r)
		hs[val[i]] = i + 1;
	rep(i, 1, n) a[i] = hs[a[i]];
	LL ans = 0;
	red(i, n, 1) {
		ans += (f[i] = get_sum(a[i] - 1));
		modify(a[i], 1);
	}
	printf("%lld\n", ans);
	build(1, n, 1);
	while(m--) {
		fr(ql), qr = n;
		ipir tmp = query(1, n, 1);
		while(tmp.first <= a[ql]) {
			ans -= f[p = tmp.second];
			f[p] = 0;
			change(1, n, 1);
			tmp = query(1, n, 1);
		}
		printf("%lld\n", ans);
	}

	return 0;
}
