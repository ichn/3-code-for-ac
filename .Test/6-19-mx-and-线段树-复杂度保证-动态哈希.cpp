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


const int maxn = 1e6 + 100;

const int mod = 1e9 + 7;
LL hs[maxn<<2];
int sm[maxn<<2];
LL b[maxn];
char str[maxn];

int n, m;

void build(int l, int r, int rt) {
	if (l == r) {
		hs[rt] = str[l-1]=='1';
		sm[rt] = hs[rt];
		return ;
	}
	int mid = (l+r)>>1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	hs[rt] = (hs[rt<<1]*b[r-mid]+hs[rt<<1|1]) % mod;
	sm[rt] = sm[rt<<1] + sm[rt<<1|1];
}

void mdf(int p, int v, int l, int r, int rt) {
	if (l == r) {
		hs[rt] = v;
		sm[rt] = v;
		return ;
	}
	int mid = (l+r)>>1;
	if (p <= mid) mdf(p, v, l, mid, rt<<1);
	else mdf(p, v, mid+1, r, rt<<1|1);
	hs[rt] = (hs[rt<<1]*b[r-mid]%mod+hs[rt<<1|1]) % mod;
	sm[rt] = sm[rt<<1] + sm[rt<<1|1];
}
void rev(int p, int l, int r, int rt) {
	if (l == r) {
		hs[rt] ^= 1;
		sm[rt] = hs[rt];
		return ;
	}
	int mid = (l+r)>>1;
	if (p <= mid) rev(p, l, mid, rt<<1);
	else rev(p, mid+1, r, rt<<1|1);
	hs[rt] = (hs[rt<<1]*b[r-mid]+hs[rt<<1|1]) % mod;
	sm[rt] = sm[rt<<1] + sm[rt<<1|1];
}


LL qry(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		return hs[rt];
	}
	int mid = (l+r)>>1;
	int ret = 0;
	if (ql <= mid) ret = qry(ql, qr, l, mid, rt<<1);
	if (mid < qr) ret = (ret * b[min(r-mid, qr - mid)] % mod + qry(ql, qr, mid+1, r, rt<<1|1)) % mod;
	return ret;
}


int qSum(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		return sm[rt];
	}
	int mid = (l+r)>>1;
	int ret = 0;
	if (ql <= mid) ret += qSum(ql, qr, l, mid, rt<<1);
	if (mid < qr) ret += qSum(ql, qr, mid+1, r, rt<<1|1);
	return ret;
}

void solve(int a, int b, int l, int r) {
	if (r < l) return ;
	if (l == r) {
		if (qry(a+l-1, a+l-1, 1, n, 1) != qry(b+l-1, b+l-1, 1, n, 1))
			mdf(a+l-1, 0, 1, n, 1), mdf(b+l-1, 0, 1, n, 1);
		return ;
	}
	int mid = (l+r)>>1;
	if (qry(a+l-1, a+mid-1, 1, n, 1) != qry(b+l-1, b+mid-1, 1, n, 1))
		solve(a, b, l, mid);
	if (qry(a+mid, a+r-1, 1, n, 1) != qry(b+mid, b+r-1, 1, n, 1))
		solve(a, b, mid+1, r);
}

int val[maxn];

int main() {

	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);

	b[0] = 1;
	int s = 71;
	fr(n, m);
	for (int i = 1; i <= n; ++i)
		b[i] = b[i-1]*s % mod;

	scanf("%s", str);
	build(1, n, 1);

	for (int mm = 1; mm <= m; ++mm) {
	//	for (int i = 1; i <= n; ++i) {
	//		printf("%lld", qry(i, i, 1, n, 1));
	//		val[i] = qry(i, i, 1, n, 1);
	//	}
	//	puts("");
		int t = fr();
		if (t == 1) {
			int l = fr(), r = fr(), w = fr();
			solve(l, r, 1, w);
		} else if (t == 2) {
			rev(fr(), 1, n, 1);
		} else {
			int l = fr(), r = fr(), w = fr();
			int c = qSum(l, r, 1, n, 1);
			if (w == 1) printf("%d\n", c);
			else printf("%d\n", r-l+1-c);
		}
	}
 
	return 0;
}


