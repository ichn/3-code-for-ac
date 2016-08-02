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
 
const int maxv = 50000+100, maxe = (100000<<1) + 100;
struct Edge {
	int edge, head[maxv], from[maxe], to[maxe], next[maxe];
	LL wei[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v, LL w) {
		to[edge] = v, next[edge] = head[u];
		from[edge] = u;
		wei[edge] = w;
		head[u] = edge++;
	}
	void addEdge(int u, int v, LL w) {
		addedge(u, v, w);
		addedge(v, u, w);
	}
} e;

int n, m, cnt;
const int maxn = maxv;
LL val[maxn], cir[maxe];
bool vis[maxn];

void dfs(int u) {
	vis[u] = true;
	for (int i=e.head[u]; i!=-1; i=e.next[i]) {
		int v = e.to[i];
		if (!vis[v]) {
			val[v] = val[u]^e.wei[i];
			dfs(v);
		} else cir[++cnt] = val[u]^val[v]^e.wei[i]; 
	}
}

const int len = 62;

LL g[len], h[len];
int p;

void Elimination() {
	for (int i=1; i<=cnt; ++i) {
		LL d = cir[i];
		for (int j=1; j<=p && d; ++j)
			if (d&h[j])
				d ^= g[j];
		if (!d) continue;
		h[++p]=1, g[p]=d;
		for (h[p]=1; (h[p]<<1)<=d; h[p]<<=1);
		for (int j=p; 1<j; --j)
			if (h[j] > h[j-1]) {
				swap(h[j], h[j-1]);
				swap(g[j], g[j-1]);
			}
	}
}
 
int main() {
#ifdef love_sbit
	file(xor);
#endif
 
	fr(n, m);
	rep(i, 1, m) {
		int u, v;
		LL w;
		fr(u, v), fr(w);
		e.addEdge(u, v, w);
	}
	dfs(1);
	Elimination();
	LL ans = val[n];
	for (int i=1; i<=p; ++i)
		if (!(ans&h[i]))
			ans ^= g[i];
	Wn(ans);
 
	return 0;
}
