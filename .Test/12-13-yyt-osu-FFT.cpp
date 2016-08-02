#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
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
 

struct Complex {
	double Real, Imag;
	Complex(double Real = 0.0, double Imag = 0.0):Real(Real), Imag(Imag) {
	}
	Complex operator + (const Complex&rhs) {
		return Complex(Real + rhs.Real, Imag + rhs.Imag);
	}
	Complex operator - (const Complex&rhs) {
		return Complex(Real - rhs.Real, Imag - rhs.Imag);
	}
	Complex operator * (const Complex&rhs) {
		return Complex(Real * rhs.Real - Imag * rhs.Imag, Real * rhs.Imag + rhs.Real * Imag);
	}	
};

void DFT(Complex*a, int N, int flag) {
	for(int i = (N >> 1), j = 1, k; j < N; i ^= k, ++j) {
		if(i < j) swap(a[i], a[j]);
		for(k = (N >> 1); i & k; i ^= k, k >>= 1);
	}
	for(int n = 2; n <= N; n <<= 1) {
		Complex Wn = Complex(cos(flag * 2 * M_PI / n), sin(flag * 2 * M_PI / n));
		for(int i = 0; i < N; i += n) {
			Complex W = Complex(1, 0);
			for(int j = i; j < i + (n >> 1); ++j, W = W * Wn) {
				Complex u = a[j], v = W * a[j + (n >> 1)];
				a[j] = u + v;
				a[j + (n >> 1)] = u - v;
			}
		}
	}
	if(flag == -1) {
		for(int i = 0; i < N; ++i) a[i].Real /= N;
	}
}

const int maxn = (500000 + 100) * 2;

Complex C[maxn], G[maxn], F[maxn];

void mult(DB *a, DB *b, DB *c, int n, bool print = true) {
	reverse(b, b + n + 1);
	for(int i = n + 1; 0 < i; --i) b[i] = b[i - 1];
	b[0] = 0.0;
	++n;
	rep(i, 0, n - 1) G[i] = Complex(a[i]);
	rep(i, 0, n - 1) F[i] = Complex(b[i]);
	int l = 1;
	while(l < n) l <<= 1;
	l <<= 1;
	DFT(G, l, 1);
	DFT(F, l, 1);
	rep(i, 0, l - 1) C[i] = G[i] * F[i];
	DFT(C, l, -1);
	rep(i, 0, l) {
		c[i] = C[i].Real;
	}
	--n;
	reverse(c + 1, c + n + 1);
	if(print)
	rep(i, 0, n) {
		printf("%.12lf\n", fabs(c[i]));
	}
}

/*
void bf_mult(DB *a, DB *b, DB *c, int n, bool print = true) {
	reverse(b, b + n + 1);
	rep(k, 1, n) {
		for(int j = 0; j + k <= n; ++j) {
			c[k] += a[j] * b[(n - k) - j];
		}
	}
	if(print)
	rep(i, 0, n) {
		printf("%.12lf\n", c[i]);
	}
	reverse(b, b + n + 1);
}

void bf_mult2(DB *a, DB *b, DB *c, int n, bool print = true) {
	for(int i = 0; i <= n; ++i) c[i] = 0.0;
	rep(k, 1, n) {
		for(int j = 0; j <= n - k; ++j) {
			c[k] += a[j] * b[j + k];
		}
	}
	if(print)
		rep(i, 0, n) {
			printf("%.12lf\n", c[i]);
		}
}

void bf_mult3(DB *a, DB *b, DB *c, int n, bool print = true) {
	for(int i = 0; i <= n; ++i) {
		printf("%lf ", b[i]);
	}
	puts("");
	reverse(b, b + n + 1);
	for(int i = 0; i <= n; ++i) {
		printf("%lf ", b[i]);
	}
	puts("");

	for(int i = n + 1; 0 < i; --i) b[i] = b[i - 1];
	b[0] = 0.0;
	for(int i = 0; i <= n; ++i) c[i] = 0.0;
	rep(k, 1, n) {
		for(int j = 0; j <= k; ++j) {
			c[n - k] += a[j] * b[k - j];
		}
	}
	if(print)
		rep(i, 0, n) {
			printf("%.12lf\n", c[i]);
		}
}
*/
 
int n;
DB a[maxn], b[maxn], c[maxn], d[maxn];
DB g[maxn], f[maxn];
int main() {
	file(osu);
	fr(n);
	d[0] = 1.0;
	g[0] = 1.0;
	rep(i, 1, n) {
		scanf("%lf", &a[i]), c[i] = 1.0 - a[i];
		d[i] = d[i - 1] * a[i];
		g[i] = c[i] / d[i];
	}
	c[n + 1] = 1.0;
	rep(i, 1, n) {
		f[i] = d[i] * c[i + 1];
	}
	//bf_mult3(g, f, b, n);
	//puts("");
	mult(g, f, b, n);

	return 0;
}
