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


const int maxn = 1e5 + 100;
char str[maxn];
int n, m;
int sum[maxn], rank[maxn], sa[maxn], height[maxn];

void sort(int *a, int *b, int *c, int n, int m) {
	rep(i, 0, m) sum[i] = 0;
	rep(i, 1, n) ++sum[c[i]];
	rep(i, 1, m) sum[i] += sum[i - 1];
	red(i, n, 1) b[sum[c[a[i]]]--] = a[i];
}

void get_sa() {
	static int x[maxn], y[maxn];
	rep(i, 1, n) rank[i] = i, x[i] = str[i];
	sort(rank, sa, x, n, 256);
	rank[sa[1]] = 1;
	rep(i, 2, n)
		rank[sa[i]] = rank[sa[i - 1]] + (x[sa[i - 1]] != x[sa[i]]);
	for(int i = 1; i <= n; i <<= 1) {
		rep(j, 1, n)
			sa[j] = j, x[j] = rank[j], y[j] = j + i <= n ? rank[i + j] : 0;
		sort(sa, rank, y, n, n), sort(rank, sa, x, n, n);
		rank[sa[1]] = 1;
		rep(j, 2, n)
			rank[sa[j]] = rank[sa[j - 1]] + (x[sa[j]] != x[sa[j - 1]] || y[sa[j]] != y[sa[j - 1]]);
		if(rank[sa[n]] == n) break;
	}
}

void get_height() {
	for(int i = 1, j = 0; i <= n; ++i) {
		if(j > 0) --j;
		if(rank[i] != 1)
			while(str[i + j] == str[sa[rank[i] - 1] + j])
				++j;
		height[rank[i]] = j;
	}
}

int main() {
	freopen("504E.in", "r", stdin);
	scanf("%s", str+1);
	n = strlen(str+1);
	get_sa();

	for (int i=1; i<=n; ++i) {
		printf("%d ", sa[i]);
	} puts("");
	return 0;
}


