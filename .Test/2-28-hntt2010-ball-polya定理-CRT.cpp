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
	const int maxv = 100, maxe = 100;
	struct Edge {
		int edge, head[maxv], to[maxe], next[maxe];
		Edge() { edge = 0; memset(head, -1, sizeof head); }
		void addedge(int u, int v) {
			to[edge] = v, next[edge] = head[u];
			head[u] = edge++;
		}
	};
};
using namespace my_useful_tools;

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的使命，铭记你的罪恶
//
// 出题人啊出题人

// ans = \frac{1}{|G|}\sum_{f\in G}^{}C(f)=
// \frac{1}{|G|}\sum_{f\in G}^{}k^{m(f)}

const int maxn = 100 * 100 * 2 + 1000;
const int maxg = 100 * 2 + 20;

int n, m, k;
int d[maxn], pw[maxn];
int g[maxg][maxg];

int hash[maxn], FALSE;


void print() {
	rep(i, 0, n<<1) {
		reu(j, 0, m)
			printf("%d ", g[i][j]);
		puts("");
	}
}

// vector<int> tmp;

int get() {
	int t = 0;
	rep(i, 0, n<<1) {
		reu(j, 0, m)
			d[++t] = g[i][j];
	}
	int ret = 0;
	++FALSE;
	rep(i, 1, t)
		if (hash[i] != FALSE) {
			++ret;
			for (int j = i; hash[j] != FALSE; hash[j] = FALSE, j = d[j]);
		}
	//tmp.pb(ret);
	//puts("");
	//print();
	//printf("%d with %d\n", t, ret);
	return ret;
}

void shift() {
	red(i, m-1, 0)
		rep(j, 0, n<<1)
			g[j][i+1] = g[j][i];
	rep(j, 0, n<<1)
		g[j][0] = g[j][m];
}

void rot() {
	int u=0, b=n<<1;
	while (u < b) {
		reu(j, 0, m)
			swap(g[u][j], g[b][j]);
		++u, --b;
	}
	rep(i, 0, n<<1)
		reverse(g[i], g[i]+m);
}

int ext_gcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	} else {
		int d = ext_gcd(b, a % b, x, y);
		int t = x;
		x = y;
		y = t - a / b * y;
		return d;
	}
}

int get_inv(int p, int mod) {
	int x, y;
	ext_gcd(p, mod, x, y);
	x = (x + mod) % mod;
	return x;
}

int solve(int mod) {
	int s = 0;
	reu(i, 0, n) {
		reu(j, 0, m)
			g[i<<1][j] = ++s;
		reu(j, 0, m)
			g[i<<1|1][j] = ++s;
	}
	reu(j, 0, m)
		g[n<<1][j] = ++s;
	++s;
	pw[0] = 1;
	rep(i, 1, s) {
		pw[i] = 1LL* pw[i-1] * k % mod;
	}
	LL ans = 0;
	reu(i, 0, m) {
		shift();
		ans = ans + pw[get()];
		ans %= mod;
		rot();
		ans = ans + pw[get()];
		ans %= mod;
		rot();
	}
	//sort(tmp.begin(), tmp.end());
	//foreach(i, tmp) {
	//	printf("%d ", *i);
	//} puts("");
	//tmp.clear();
	//printf("%lld\n", ans);
	int a = 2*m%mod;
	int inv = get_inv(a, mod);
	//printf("is that %d == 1 true ? \n", inv * a % mod);
	return 1LL * ans * inv % mod;
}

int main() {
#ifdef love_lhy
	file(ball);
#endif

	fr(n, m, k);
	int ans_2999 = solve(2999);
	int ans_3001 = solve(3001);
	//for (int i = 0; i < 2999*3001; ++i) {
	//	if (i % 2999 == ans_2999 && i % 3001 == ans_3001) {
	//		printf("%d\n", i);
	//		break;
	//	}
	//}
	//printf("%d %d\n", ans_2999, ans_3001);
	int M1 = 3001, M2 = 2999;
	int y1 = get_inv(M1, 2999);
	int y2 = get_inv(M2, 3001);
	//printf("%d %d\n", y1 * M1 % 2999, y2 * M2 % 3001);
	LL ans = 1LL*y1*M1*ans_2999 + 1LL*y2*M2*ans_3001;
	//Wn(ans);
	Wn((ans % (3001*2999) + (3001*2999)) % (3001*2999));
 
	return 0;
}

