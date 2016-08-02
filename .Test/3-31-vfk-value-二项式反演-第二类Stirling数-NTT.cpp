#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
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

const int mod = 998244353;
const int _g = 3;
const int maxn = 2e5 + 100;

int iFac[maxn], fac[maxn], pow2[maxn];

int fpm(int b, LL i, int m) {
	if (i < 0) return 0;
	int r = 1;
	for (; i; i>>=1, b=(LL)b*b%m)
		if (i&1) r = (LL)r*b%m;
	return r;
}

int S[maxn];

int Binom(int n, int k) {
	return (LL)fac[n]*iFac[k]%mod*iFac[n-k]%mod;
}

int a[maxn*4], b[maxn*4];
int rev[maxn*4];
int rG[2][maxn*4];

void dft(int *a, int N, int d) {
	reu(i, 0, N)
		if (i<rev[i]) swap(a[i], a[rev[i]]);
	for (int i=2; i<=N; i<<=1) {
		int s=rG[d][i], u, v, c;
		for (int k, j=0; j < N; j+=i)
			for (k=j, c=1; k<j+(i>>1); ++k, c=(LL)c*s%mod) {
				u = a[k], v = (LL)c*a[k+(i>>1)]%mod;
				a[k] = (u+v)%mod;
				a[k+(i>>1)] = (u-v+mod)%mod;
			}
	}
	if (d) {
		int rN = fpm(N, mod-2, mod);
		reu(i, 0, N)
			a[i] = (LL)a[i]*rN%mod;
	}
}

void getStirlingNumber2(int k) {
	rep(i, 0, k) {
		a[i] = (LL)fpm(i, k, mod)*iFac[i]%mod;
		b[i] = (LL)(!(i&1)?1LL:(mod-1LL))*iFac[i]%mod;
	}
	int n = (k+1)*2, N, L;
	for (N=1; N<=n; N<<=1);
	for (L=0; (1<<L)<N; ++L);
	rep(i, 1, N)
		rev[i] = (rev[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=1; i<=N; i<<=1)
		rG[0][i] = fpm(_g, (mod-1)/i, mod);
	for (int i=1; i<=N; i<<=1)
		rG[1][i] = fpm(rG[0][i], mod-2, mod);
	
	dft(a, N, 0);
	dft(b, N, 0);
	reu(i, 0, N)
		a[i] = (LL)a[i]*b[i]%mod;
	dft(a, N, 1);
	rep(i, 0, k)
		S[i] = a[i];
}

int s[1000][1000];

int calc(int k, int l) {
	if (s[k][l] != -1) return s[k][l];
	if (k < l) return 0;
	if (k == l) return 1;
	if (l == 1) return 1;
	return s[k][l] = (calc(k-1, l-1)+(LL)l*calc(k-1, l)%mod)%mod;
}

LL G(int n, int k) {
	getStirlingNumber2(k);
	LL ret = 0;
	LL ps = 1;
	rep(l, 0, k) {
		LL tmp = (LL)S[l]*fpm(2, n-l, mod)%mod*ps%mod;
		ps = ps*(n-l)%mod;
		ret += tmp;
		ret %= mod;
	}
	return ret;
}

int main() {
	freopen("value.in", "r", stdin);
	freopen("value.out", "w", stdout);
	int n, k;
	fr(n, k);
	if (k == 0) {
		Wn((LL)n*fast_pow(2LL, (LL)n*(n-1)/2LL, (LL)mod)%mod);
		return 0;
	}
	iFac[0] = 1;
	fac[0] = 1;
	rep(i, 1, k) {
		fac[i] = (LL)i*fac[i-1]%mod;
		iFac[i] = fpm(fac[i], mod-2, mod);
	}

	int ans1 = (LL)n*fpm(2, (LL)(n-1)*n/2LL-n+1, mod)%mod;
	Wn((LL)ans1*G(n-1, k)%mod);

	return 0;
}
