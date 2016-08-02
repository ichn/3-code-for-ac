#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define _pir pair<int, int>
#define _vec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define pfile(x) freopen(#x".in", "r", stdin), freopen("_"#x".out", "w", stdout)
#define hfile freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define gfile(x) freopen(#x".in", "w", stdout);
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
};
using namespace my_useful_tools;

const int mod = 998244353;
const int maxn = (65536<<1) + 100;
const int G = 3;

int n, l, m, k;
int N, L, g[2][maxn], rev[maxn], rN;

map<int, _vec> bad;

int fpm(LL b, int i, int m) {
	int r = 1;
	for (; i; i >>= 1, b = b * b % m)
		if (i & 1) r = 1LL * r * b % m;
	return r;
}

void addIt(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

void dft(int *a, int r, int N) {
	reu(i, 0, N)
		if (rev[i] < i)
			swap(a[i], a[rev[i]]);

	for (int i = 2; i <= N; i <<= 1) {
		int s = g[r][i], u, v;
		for (int j = 0, c = 1; j < N; j += i, c = 1)
			for (int k = 0; k < (i>>1); ++k, c = 1LL * c * s % mod) {
				u = a[j+k], v = 1LL * a[j+(i>>1)+k] * c % mod;
				a[j+k] = (u + v) % mod;
				a[j+k+(i>>1)] = (u - v + mod) % mod;
			}
	}
	if (r == 1)
		reu(i, 0, N)
			a[i] = 1LL * a[i] * rN % mod;
}

int tmp[maxn];

void mult(int *a, int *b) {
	reu(i, 0, N)
		tmp[i] = b[i];
	dft(a, 0, N);
	dft(tmp, 0, N);
	reu(i, 0, N)
		a[i] = 1LL * a[i] * tmp[i] % mod;
	dft(a, 1, N);
	for (int i = n; i < N; ++i)
		addIt(a[i % n], a[i]), a[i] = 0;
}

void fpm(int*b, int i) {
	dft(b, 0, N);

	reu(j, 0, N)
		b[j] = fpm(b[j], i, mod);

	dft(b, 1, N);
}

int ct[maxn], ca[maxn], cb[maxn];


int main() {
	file(move);

	fr(n, l);
	N = n<<1;
	for (L = 0; (1<<L) != N; ++L);
	reu(i, 0, N)
		rev[i] = (rev[i>>1]>>1) | ((i&1)<<(L-1));

	for (int i = 1; i <= N; i<<=1)
		g[0][i] = fpm(3, (mod-1)/i, mod);
	for (int i = 1; i <= N; i<<=1)
		g[1][i] = fpm(g[0][i], mod-2, mod);
	rN = fpm(N, mod-2, mod);

	fr(m);
	reu(i, 0, m) {
		int x = fr(), y = fr();
		bad[x].pb(y);
	}
	bad[l].pb(n+1);

	fr(k);
	reu(i, 0, k) {
		++ct[fr() % n];
	}

	ca[0] = 1;
	
	int last = 0;
	foreach(i, bad) {
		int ind = i->first - last;
		memcpy(cb, ct, sizeof ct);
		fpm(cb, ind);

		mult(ca, cb);
		foreach(j, i->second)
			ca[*j] = 0;
		last = i->first;
	}

	printf("%d\n", ca[0]);
 
	return 0;
}


