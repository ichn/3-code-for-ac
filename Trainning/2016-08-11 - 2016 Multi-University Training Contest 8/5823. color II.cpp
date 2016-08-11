#include <bits/stdc++.h>
using namespace std;
namespace my_zone {
#define rep(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define rgo(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define clr(t) memset(t, 0, sizeof t);
#define clo(t, v) memcpy(t, v, sizeof t);
#define cls(t, v) memset(t,v,sizeof t);
#define pc(c) putchar(c)
#define gc() getchar()
	typedef pair<int, int> ipir;
	typedef vector<int> ivec;
	typedef set<int> iset;
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline char gchar(char r=gc()) {
		for(;r==' '||r=='\n'||r=='\r';
				r=gc());return r;}
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }

};
using namespace my_zone;


typedef unsigned int uint;
const int maxN = 18;
int n, N;
int g[maxN];
int f[1<<maxN];
bool o[1<<maxN];
uint pd(uint a, uint b) {
	uint r = 1;
	for (; b; b >>= 1, a*=a)
		if (b&1) r *= a;
	return r;
}

inline bool ok(int s) {
	for (int t = s; t; t -= t&-t) {
		if (g[__builtin_ffs(t)-1] & s) return false;
	}
	return true;
}
int dfs(int s) {
	if (f[s] != -1) return f[s];
	f[s] = INF;
	for (int t = s; t; t = (t-1)&s) {
		if (o[t])
			f[s] = min(f[s], dfs(s^t)+1);
	}
	return f[s];
}

int main() {
#ifdef lol
	freopen("5823.in", "r", stdin);
	freopen("5823.out", "w", stdout);
#endif

	int T = fr();
	while (T--) {
		fr(n);
		N = 1<<n;
		memset(g, 0, sizeof g);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (gchar() == '1')
					g[i] |= 1<<j;
		memset(f, -1, sizeof f);
		for (int i = 0; i < N; ++i)
			o[i] = ok(i);
		f[0] = 0;
		for (int i = 0; i < n-1; ++i)
			f[1<<i] = 1;
		dfs(N-1);
		uint ans = 0;
		for (int i = 0; i < N; ++i)
			ans += (uint)f[i] * pd(233u, i);
		cout << ans << endl;
	}
 
	return 0;
}

