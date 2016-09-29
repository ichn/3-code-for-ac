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


const int maxN = 100000 + 100;
int n;
int a[maxN], b[maxN], d[maxN];

int solve() {
	int cnt1 = 0, cnt2 = 0;
	for (int i = 1; i <= n; ++i)
		if (a[i] != b[i]) {
			if (a[i] == 1)
				++cnt1;
			else ++cnt2;
		}
	return max(cnt1, cnt2);
}

int main() {

#ifdef love_yxl
	file(B);
#endif

	fr(n);
	for (int i = 1; i <= n; ++i) {
		char c = gchar();
		a[i] = c == 'b';
	}
	for (int i = 1; i <= n; i += 2)
		b[i] = 1;
	memcpy(d, a, sizeof a);
	int ans = solve();
	memcpy(d, a, sizeof a);
	memset(b, 0, sizeof b);
	for (int i = 2; i <= n; i += 2)
		b[i] = 1;
	cout << min(ans, solve()) << endl;

	return 0;
}

