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
const int maxn = 300+10;
const int maxm = maxn*maxn;
int n, m, n2;
int sum[maxn][maxn];
int f[maxn][maxn];
int get(int a, int b, int c, int d) {
	return sum[c][d]+sum[a-1][b-1]-sum[c][b-1]-sum[a-1][d];
}
void add(int&a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}


int dfs(int l, int r) {
	if (f[l][r] != -1)
		return f[l][r];
	int &ans = f[l][r];
	ans = 0;
	if (l == r) {
		ans = 1;
		return ans;
	}
	if (!get(l, l+1, l, r))
		add(ans, dfs(l+1, r));
	if (!get(l+1, l, r, l))
		add(ans, dfs(l+1, r));
	for (int i = l+1; i < r; ++i) {
		if (!get(i+1, l+1, r, i) && !get(i+1, l, r, l) && !get(l, l+1, l, i))
			add(ans, (LL)dfs(l+1, i)*dfs(i+1, r)%mod);
	}
	return ans;
}

int ans;


int main() {
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);
	int T = fr();
	while (T--) {
		fr(n, m);
		memset(f, -1, sizeof f);
		memset(sum, 0, sizeof sum);
		bool flg = false;
		rep(i, 1, m) {
			int a, b;
			fr(a, b);
			sum[a][b] = 1;
			if (a == b) {
				flg = true;
			}
		}
		if (flg) {
			puts("0");
			continue;
		}
		rep(i, 1, n)
			rep(j, 1, n)
				sum[i][j] += sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		ans = dfs(1, n);
		printf("%d\n", ans);
	}
 
	return 0;
}
