#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
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
 
const int maxn = 200000 + 100;
vector<ipir> q[maxn];
int n, m, a[maxn], ans[maxn], next[maxn];
map<int, int> E, N;
int tmp[maxn];
 
int main() {
	fr(n, m);
	rep(i, 1, n) {
		fr(a[i]);
		if(N.count(a[i]))
			next[N[a[i]]] = i - 1;
		N[a[i]] = i;
	}
	rep(i, 1, n) {
		if(next[i] == 0) next[i] = n;
	}
	rep(i, 1, m) {
		int l, r; fr(l, r);
		q[l].pb(mp(r, i));
	}
	tmp[1] = (a[1]==0)?1:0;
	E[a[1]] = 1;
	rep(i, 2, n) {
		tmp[i] = tmp[i - 1];
		E[a[i]] = 1;
		while(E.count(tmp[i])) ++tmp[i];
	}
	rep(i, 1, n) {
		foreach(j, q[i])
			ans[j->second] = tmp[j->first];
		tmp[i] = 0;
		for(int j = next[i]; i < j; --j) {
			if(tmp[j] <= a[i]) break;
			tmp[j] = a[i];
		}
	}
	rep(i, 1, m) {
		printf("%d\n", ans[i]);
	}
 
	return 0;
}
