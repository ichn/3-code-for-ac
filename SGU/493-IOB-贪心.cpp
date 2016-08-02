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

const int maxn = 1e3 + 100;
const double eps = 1e-10;
int sgn(DB x) {
	return x < -eps ? -1 : eps < x;
}

int n, n2, ans;
int l[maxn<<1], h[maxn<<1];
int que[maxn], qh, qt;
bitset<2010> fa[maxn<<1];
void init() {
	n2 = n<<1;
	reu(i, 0, n2)
		fa[i].reset();
	qh = 1, qt = 0;
	for (int i = n2-2; 0 <= i; i -= 2) {
		while (qh <= qt && h[i] > h[que[qt]])
			--qt;
		que[++qt] = i;
		fa[i][i] = 1;
		if (i == 0) break;
		rep(j, qh, qt) {
			int p = que[j];
			if (sgn(fabs((DB)h[i] / (l[i] - l[i-1])) - fabs((DB)h[p] / (l[p] - l[i-1]))) <= 0)
				fa[i - 1][p] = 1;
		}
	}
	qh = 1, qt = 0;
	for (int i = 1; i < n2; i += 2) {
		while (qh <= qt && h[i] > h[que[qt]])
			--qt;
		que[++qt] = i;
		fa[i][i] = 1;
		if (i == n2 - 1) break;
		rep(j, qh, qt) {
			int p = que[j];
			if (sgn(fabs((DB)h[i] / (l[i] - l[i+1])) - fabs((DB)h[p] / (l[p] - l[i+1]))) <= 0)
				fa[i + 1][p] = 1;
		}
	}
}

namespace bf {
	void solve() {
		int s = 1<<n2;
		ans = n2;
		reu(t, 0, s) {
			int w = 0;
			reu(j, 0, n2)
				if ((fa[j] & bitset<2010>(t)) != 0)
					w |= (1<<j);
			if (w == s-1)
				ans = min(ans, __builtin_popcount(t));
		}
	}
}

namespace N2 {
	void solve() {
		ans = 1 + n;
	//	reu(i, 0, n2) {
	//		string s = fa[i].to_string();
	//		cout << s.substr(s.length() - 12, s.length()) << endl;
	//	}
		for (int i = 1; i < n2; i += 2) {
			fa[i][i] = 0, fa[i][i+1] = 0;
			fa[i+1][i] = 0, fa[i+1][i+1] = 0;
			if (fa[i].count() != 0 && fa[i+1].count() != 0)
				ans -= 1;
		}
	}
};

int main() {
	freopen("493.in", "r", stdin);
	freopen("493.out", "w", stdout);

	int T = fr();
	static pair<pair<int, int>, int> s[maxn];
	while (T--) {
		fr(n);
		reu(i, 0, n)
			fr(s[i].first.first, s[i].first.second, s[i].second);
		sort(s, s + n);
		reu(i, 0, n) {
			l[i<<1] = s[i].first.first;
			l[i<<1|1] = s[i].first.second;
			h[i<<1] = h[i<<1|1] = s[i].second;
		}
		ans = 0;
		init();
		N2::solve();
		printf("%d\n", ans);
	}
 
	return 0;
}

