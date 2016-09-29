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
const int mod = 1e9 + 7;

struct Mat {
	int d[2][2];
	void init() {
		memset(d, 0, sizeof d);
		d[0][0] = d[1][1] = 1;
	}
	void clear() {
		memset(d, 0, sizeof d);
	}
	Mat() {
		clear();
	}
	void set() {
		clear();
		d[0][1] = d[1][0] = d[1][1] = 1;
	}
	bool chk() {
		if (d[0][0] == 1 && d[0][1] == 0 && d[1][0] == 0 && d[1][1] == 1)
			return true;
		return false;
	}
};

int Mod(int a) {
	if (a >= mod) a-= mod;
	return a;
}
void add(int&a, int c) {
	a += c;
	if (a >= mod) a-= mod;
}
Mat operator + (Mat a, Mat b) {
	Mat r;
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			r.d[i][j] = Mod(a.d[i][j] + b.d[i][j]);
	return r;
}
Mat operator * (Mat a, Mat b) {
	Mat r;
	r.clear();
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				add(r.d[i][k], (1LL * a.d[i][j] * b.d[j][k]) % mod);
	return r;
}

Mat pwd(Mat a, int b) {
	Mat r;
	r.init();
	for (; b; b >>= 1, a = a * a)
		if (b & 1)
			r = r * a;
	return r;
}

Mat get(int a) {
	Mat r;
	r.set();
	return pwd(r, a);
}

Mat tr[maxN<<2], mt[maxN<<2];
int a[maxN];

void upd(int rt) {
	tr[rt] = tr[rt<<1] + tr[rt<<1|1];
}

void init(int l, int r, int rt) {
	mt[rt].init();
	tr[rt].clear();
	if (l == r) {
		tr[rt] = get(a[l]);
	//	printf("%d ", Mod(tr[rt].d[0][0] + tr[rt].d[1][0]));
		return ;
	}
	int mid = (l + r) >> 1;
	init(l, mid, rt<<1);
	init(mid+1, r, rt<<1|1);
	upd(rt);
}

Mat c;
void mult(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		tr[rt] = tr[rt] * c;
		mt[rt] = mt[rt] * c;
		return ;
	}
	int mid = (l + r) >> 1;
	if (!mt[rt].chk()) {
		tr[rt<<1] = tr[rt<<1] * mt[rt];
		tr[rt<<1|1] = tr[rt<<1|1] * mt[rt];
		mt[rt<<1] = mt[rt<<1] * mt[rt];
		mt[rt<<1|1] = mt[rt<<1|1] * mt[rt];
		mt[rt].init();
	}
	if (ql <= mid)
		mult(ql, qr, l, mid, rt<<1);
	if (mid < qr)
		mult(ql, qr, mid+1, r, rt<<1|1);
	upd(rt);
}

Mat calc(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		return tr[rt];
	}
	int mid = (l + r) >> 1;
	if (!mt[rt].chk()) {
		tr[rt<<1] = tr[rt<<1] * mt[rt];
		tr[rt<<1|1] = tr[rt<<1|1] * mt[rt];
		mt[rt<<1] = mt[rt<<1] * mt[rt];
		mt[rt<<1|1] = mt[rt<<1|1] * mt[rt];
		mt[rt].init();
	}
	Mat ret;
	ret.clear();
	if (ql <= mid)
		ret = ret + calc(ql, qr, l, mid, rt<<1);
	if (mid < qr)
		ret = ret + calc(ql, qr, mid+1, r, rt<<1|1);
	return ret;
}

int main() {

#ifdef love_yxl
	file(E);
#endif

	int n, m;
	fr(n, m);
	for (int i = 1; i <= n; ++i)
		fr(a[i]), --a[i];
	init(1, n, 1);
	//puts("");
	for (int i = 1; i <= m; ++i) {
		int l, r, v;
		if (fr() == 1) {
			fr(l, r, v);
			c = get(v);
			mult(l, r, 1, n, 1);
		} else {
			fr(l, r);
			Mat w = calc(l, r, 1, n, 1);
			printf("%d\n", Mod(w.d[1][0] + w.d[0][0]));
		}
	}

	return 0;
}

