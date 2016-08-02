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

const int maxn = (1<<16) + 100;

struct Info {
	int deg, sum;
	int id;
	bool operator < (const Info&rhs) const {
		return deg < rhs.deg;
	}
} a[maxn];

int m, n;

vector<int> g[maxn];
int f[maxn];

bool vis[maxn];
vector<pair<int, int> > e;

void dfs(int u) {
	vis[u] = true;
	foreach(i, g[u]) {
		int v = (*i);
		if (!vis[v]) {
			e.pb(mp(u, v));
			dfs(v);
		}
	}
}


int main() {
#ifdef love_sbit
	file(504A);
#endif
	fr(n);
	int cnt = 0;
	reu(i, 0, n) {
		fr(a[i].deg, a[i].sum);
		a[i].id = i;
		cnt += a[i].deg;
	}
	sort(a, a+n);
	reu(i, 0, n) {
		f[a[i].id] = i;
	}
	int tp = 0;
	static int que[maxn];
	reu(i, 0, n) {
		if (a[i].deg == 0)
			continue;
		if (a[i].deg != 1)
			break;
		que[++tp] = i;
	}

	while (0 < tp) {
		int i = que[tp--];
		if (a[i].deg == 0) {
			continue;
		}
		//printf("%d %d\n", a[i].id, a[i].sum);
		g[a[i].id].pb(a[i].sum);
		g[a[i].sum].pb(a[i].id);
		a[f[a[i].sum]].sum ^= a[i].id;
		--a[f[a[i].sum]].deg;
		if (a[f[a[i].sum]].deg == 1) {
			que[++tp] = f[a[i].sum];
		}
	}

	reu(i, 0, n) {
		if (!vis[i]) {
			dfs(i);
		}
	}

	printf("%d\n", (int)e.size());
	foreach(i, e) {
		printf("%d %d\n", i->first, i->second);
	}

	return 0;
}

