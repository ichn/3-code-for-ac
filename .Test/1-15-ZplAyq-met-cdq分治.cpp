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
 
const int maxh = 22;
const int maxn = 600000 + 100;
const int maxq = 600000 + 100;

struct Querys {
	int l, r, t, val;
} Q[maxq];


int n, m, q, c, l, r, v;
int to[maxn], rec[maxn], cap[maxn], f[maxh][maxn], ans[maxn], tmp[maxn];
LL sum[maxn];

void solve(int l, int r, int h) {
	//printf("%d %d %d %d\n", l, r, h, f[h][0]);
	int *now=f[h], *next=f[h+1];
	if (l==r) {
		rep(i, 1, now[0])
			if (!ans[now[i]])
				ans[now[i]] = Q[l].t;
		return ;
	}
	int mid = (l+r)>>1;
	memset(sum, 0, sizeof(sum[0])*(now[0]+1));
	rep(i, l, mid) {
		sum[Q[i].l] += Q[i].val;
		sum[Q[i].r+1] -= Q[i].val;
	}
	rep(i, 1, now[0])
		rec[now[i]] = cap[now[i]];
	rep(i, 1, now[0]) {
		sum[i] += sum[i-1];
		if (cap[now[i]] > 0)
			cap[now[i]] -= sum[i];
	}
	next[0] = 0;
	memset(tmp, 0, sizeof(tmp[0])*(now[0]+1));
	rep(i, 1, now[0]) {
		if (cap[now[i]] > 0) {
			tmp[i] = tmp[i-1]+1;
			next[++next[0]] = now[i];
		} else tmp[i] = tmp[i-1];
	}
	rep(i, mid+1, r) {
		Q[i].l = tmp[Q[i].l-1]+1;
		Q[i].r = tmp[Q[i].r];
	}
	solve(mid+1, r, h+1);
	next[0] = 0;
	memset(tmp, 0, sizeof(int)*(now[0]+1));
	rep(i, 1, now[0]) {
		if (cap[now[i]]<=0) {
			tmp[i] = tmp[i-1]+1;
			next[++next[0]] = now[i];
		} else tmp[i] = tmp[i-1];
	}
	rep(i, 1, now[0]) {
		if (cap[now[i]]<=0)
			cap[now[i]] = rec[now[i]];
	}
	rep(i, l, mid) {
		Q[i].l = tmp[Q[i].l-1]+1;
		Q[i].r = tmp[Q[i].r];
	}
	solve(l, mid, h+1);
}

int main() {
	freopen("met.in", "r", stdin), freopen("met.out", "w", stdout);
	fr(n, m);
	f[0][0] = m;
	rep(i, 1, f[0][0])
		fr(f[0][i]);
	rep(i, 1, n)
		fr(cap[i]);
	fr(q);
	rep(i, 1, q) {
		fr(l, r, v);
		if (r < l) {
			Q[++c] = (Querys){1, r, i, v};
			Q[++c] = (Querys){l, m, i, v};
		} else Q[++c] = (Querys){l, r, i, v};
	}
	solve(1, c+1, 0);
	rep(i, 1, n)
		if (ans[i]) {
			printf("%d\n", ans[i]);
		} else puts("NIE");

	return 0;
}



