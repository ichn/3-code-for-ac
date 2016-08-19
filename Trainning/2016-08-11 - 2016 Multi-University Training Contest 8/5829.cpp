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

const int maxN = 1e5 + 100;
const int Rng = 1e5 + 10;
const int mod = 998244353;
const int G = 3;
int n, a[maxN], b[maxN], f[maxN], p2[maxN], rf[maxN];
int pd(int a, int b, int c=mod) {
	int r = 1;
	for (; b; b>>=1, a=1LL*a*a%mod)
		if (b&1) r=1LL*r*a%mod;
	return r;
}

int main() {
#ifdef lol
	freopen("5829.in", "r", stdin);
	freopen("5829.out", "w", stdout);
#endif

	f[0] = 1;
	p2[0] = 1;
	for (int i = 1; i <= Rng; ++i) {
		f[i] = 1LL * f[i-1] * i % mod;
		p2[i] = p2[i-1] * 2LL % mod;
		rf[i] = pd(f[i], mod-2);
	}

	int T = fr();
	while (T--) {
		fr(n);
		for (int i = 1; i <= n; ++i)
			fr(a[i]);
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; ++i)
			a[i] = 1LL * a[i] * p2[n-i] % mod * f[i-1] % mod;
		reverse(a + 1, a + n + 1);
		int N = 1, l = 0;
		while (N<=n) N<<=1, ++l;
		dft(a, N, 1);
		dft(f, N, 1);
		for (int i = 0; i < N; ++i)
			a[i] = 1LL * a[i] * f[i] % mod;
		dfs(a, N, -1);
		for (int i = 1; i <= n; ++i)
			b[i] = a[n+1-i];
		for (int i = 1; i <= n; ++i) {
		}


 
	return 0;
}

