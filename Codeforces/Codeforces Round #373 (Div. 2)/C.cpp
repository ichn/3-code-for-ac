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

const int maxN = 200000 + 100;
int n, w, p;
int a[maxN];

int main() {

#ifdef love_yxl
	file(C);
#endif

	fr(n, w);
	for (int i = 1; i <= n; ++i) {
		char c = gchar();
		a[i] = c == '.' ? -1 : c - '0';
		if (c == '.')
			p = i;
	}
	int t = n+1;
	for (int j = p+1; j <= n; ++j)
		if (a[j] >= 5) {
			t = j;
			break;
		}
	if (t > n) {
		for (int i = 1; i <= n; ++i)
			putchar(a[i] < 0 ? '.' : '0' + a[i]);
		puts("");
	} else {
		while (a[t] > 4 && w > 0) {
			a[t-1] += 1;
			--w;
			--t;
		}
		if (a[p] == 0) {
			++a[p-1];
			int e = p-1;
			while (a[e] == 10) {
				++a[e-1];
				a[e] = 0;
				--e;
			}
			if (e == 0) {
				for (int i = 0; i < p; ++i)
					putchar('0' + a[i]);
				puts("");
				return 0;
			}
			for (int i = 1; i < p; ++i)
				putchar('0' + a[i]);
			puts("");
			return 0;
		}
		for (int i = 1; i <= t; ++i)
			putchar(a[i] < 0 ? '.' : '0' + a[i]);
		puts("");
	}


	return 0;
}

