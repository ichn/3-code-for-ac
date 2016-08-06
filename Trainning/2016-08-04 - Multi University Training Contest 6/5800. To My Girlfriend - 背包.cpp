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

const int maxN = 1120;
const int mod = 1e9 + 7;

int f[2][maxN][3][3];
int n, s, a[maxN];

void add(int&x, int y) {
	x += y;
	if (x > mod) x-= mod;
}

int main() {
#ifdef lol
	freopen("5800.in", "r", stdin);
	freopen("5800.out", "w", stdout);
#endif
	int T = fr();
	while (T--) {
		scanf("%d %d", &n, &s);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		memset(f, 0, sizeof f);
		int c = 0, l = 1;
		f[c][0][0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			swap(c, l);
			memcpy(f[c], f[l], sizeof f[c]);
			for (int j = 0; j <= s; ++j) {
				add(f[c][j][0][1], f[l][j][0][0]);
				add(f[c][j][0][2], f[l][j][0][1]);

				add(f[c][j][1][1], f[l][j][1][0]);
				add(f[c][j][1][2], f[l][j][1][1]);

				add(f[c][j][2][1], f[l][j][2][0]);
				add(f[c][j][2][2], f[l][j][2][1]);
			}
			for (int j = 0; j <= s - a[i]; ++j) {
				add(f[c][j+a[i]][0][0], f[l][j][0][0]);
				add(f[c][j+a[i]][0][1], f[l][j][0][1]);
				add(f[c][j+a[i]][0][2], f[l][j][0][2]);
				add(f[c][j+a[i]][1][0], f[l][j][1][0]);
				add(f[c][j+a[i]][1][1], f[l][j][1][1]);
				add(f[c][j+a[i]][1][2], f[l][j][1][2]);
				add(f[c][j+a[i]][2][0], f[l][j][2][0]);
				add(f[c][j+a[i]][2][1], f[l][j][2][1]);
				add(f[c][j+a[i]][2][2], f[l][j][2][2]);


				add(f[c][j+a[i]][1][0], f[l][j][0][0]);
				add(f[c][j+a[i]][2][0], f[l][j][1][0]);

				add(f[c][j+a[i]][1][1], f[l][j][0][1]);
				add(f[c][j+a[i]][2][1], f[l][j][1][1]);

				add(f[c][j+a[i]][1][2], f[l][j][0][2]);
				add(f[c][j+a[i]][2][2], f[l][j][1][2]);
			}
		}
		int ans = 0;
		for (int i = 0; i <= s; ++i) {
			add(ans, f[c][i][2][2]);
		}
		add(ans, ans);
		add(ans, ans);
		cout << ans << endl;
	}
 
	return 0;
}

