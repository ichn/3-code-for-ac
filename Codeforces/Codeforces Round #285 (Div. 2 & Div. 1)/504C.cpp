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

const int maxn = 1e5+100;

int n, m, a[maxn], cnt[maxn], sum, recl, recr;
int tim[maxn];

bool chk(int r) {
	rep(i, 1, n) tim[i] = 0;
	if (r <= n/2) {
		for (int i=r+1; i<=n/2; ++i)
			if (a[i] != a[n-i+1])
				return 0;
		for (int i=n-r+1; i<=n-m; ++i)
			++tim[a[i]];
		for (int i=m+1; i<=r; ++i)
			--tim[a[i]];
		for (int i=1; i<=n; ++i)
			if (tim[i] != 0)
				return 0;
		return 1;
	} else {
		rep(i, m+1, r) {
			++tim[a[i]];
		}
		rep(i, r+1, n-m) {
			--tim[a[i]];
			if (tim[a[i]]<0)
				return 0;
		}
		return 1;
	}
}

int main() {
#ifdef love_sbit
	file(504C);
#endif
	fr(n);
	rep(i, 1, n) fr(a[i]), ++cnt[a[i]];
	rep(i, 1, n) sum += cnt[i]&1;
	if (sum >= 2) {
		puts("0");
		return 0;
	}
	m=-1;
	for (int i=1, j=n; i<=j; ++i, --j)
		if (a[i] != a[j]) {
			m = i-1;
			break;
		}
	if (m==-1) {
		Wn((LL)n*(n+1)/2);
		return 0;
	}
	int l=m+1, r=n-m, mid;
	while (l < r) {
		mid = (l+r)>>1;
		if (chk(mid)) r = mid;
		else l = mid+1;
	}
	recl = l;
	reverse(a+1, a+n+1);
	l=m+1, r=n-m;
	while (l < r) {
		mid = (l+r)>>1;
		if (chk(mid)) r = mid;
		else l = mid+1;
	}
	recr = n-l+1;
	LL ans = (LL)(n-m-recl)*(m+1)+(LL)(recr-m-1)*(m+1)+(LL)(m+1)*(m+1);
	Wn(ans);

	return 0;
}
