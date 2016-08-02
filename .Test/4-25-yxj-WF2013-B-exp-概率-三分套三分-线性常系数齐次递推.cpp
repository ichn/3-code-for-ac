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

typedef long double ld;

ld x, p, r, a;

ld f(ld l, ld w) {
	ld gl = (1.0 - pow(r, l)) / (pow(r, w) - pow(r, l));
	ld ret = w * gl + l * (1 - x) * (1 - gl);
	a = max(a, ret);
	return ret;
}

ld calc(int w) {
	int l = -30000, r = 0;
	ld ret = 0.0;
	for (int i = 1; i <= 100; ++i) {
		if (r - l < 10) {
			for (int j = l; j <= r; ++j)
				ret = max(ret, f(j, w));
			break;
		}
		int m = (l + r) / 2;
		if (f(m, w) < f(m+1, w))
			l = m+1;
		else r = m;
	}
	return ret;
}

int main() {
	/*
	freopen("exp.in", "r", stdin);
	freopen("exp.out", "w", stdout);
	*/

	cin >> x >> p;
	x /= 100, p /= 100;
	r = (1 - p) / p;

	a = 0.0;

	int l = 0, r = 30000;
	for (int i = 1; i <= 100; ++i) {
		if (r - l < 10) {
			for (int j = l; j <= r; ++j)
				calc(j);
			break;
		}
		int m = (l + r) >> 1;
		if (calc(m) < calc(m+1)) {
			l = m+1;
		} else r = m;
	}

	double ans = a;

	printf("%.10lf\n", ans);

	return 0;
}

