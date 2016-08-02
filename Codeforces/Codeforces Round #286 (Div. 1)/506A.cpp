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

const int maxn = 30000 + 100;
int n, d, p[maxn];

int road[maxn];
map<int, int> info[maxn];
int m;

bool inq[maxn];
int re_sum[maxn];
int acv

int main() {
#ifdef love_sbit
	file(506A);
#endif
	m = 30000;
	fr(n, d);
	rep(i, 1, n)
		fr(p[i]), road[p[i]]=1;
	info[d][d] = road[d];
	for (int i=m; 0<i; --i)
		re_sum[i] = re_sum[i+1]+road[i];
	static int que[maxn];
	int h=0, t=0;
	que[h] = d;
	int ans = 0;
	while (h <= t) {
		int u = que[h++];
		foreach(i, info[u]) {
			int x=i->first, y=i->second;
			for (int j=-1; j<=1; ++j) {
				int v=u+x+j;
				if (v>m) {
					ans = max(ans, y);
					break;
				}
				if (!inq[v]) {
					que[++t] = v;
					inq[v] = true;
				}
				if (x+j <= 0) {
					ans = max(ans, re_sum[v]);
					continue;
				}
				info[v][x+j] = max(info[v][x+j], y+(road[v]==1));
			}
		}
	}
	printf("%d\n", ans);

	return 0;
}
