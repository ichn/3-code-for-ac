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
//#define generator_sbit
 
const int maxn = 500000+100;

#define kn kdt_node
#define ls ch[0]
#define rs ch[1]
const double ratio = 0.05;
struct kdt_node {
	kn*ch[2];
	int sz;
	int x, y;
	int mn[2], mx[2];
	kn() {
		sz = 0;
		ls = rs = NULL;
	}
} pool[maxn], *root, *bu[maxn], *loc;

void init_kdt() {
	root = NULL;
	loc = pool;
}

int dep;

bool cmp(const kn* lhs, const kn* rhs) {
	return dep&1? lhs->x<rhs->x : lhs->y<rhs->y;
}

void build(int l, int r, kn*&at) {
	if (r < l) return ;
	dep ^= 1;
	int mid = (l+r)>>1;
	nth_element(bu+l, bu+mid, bu+r+1, cmp);
	at = bu[mid];
	int rec = dep;
	build(l, mid-1, at->ls);
	build(mid+1, r, at->rs);
	dep = rec;

	at->sz = (at->ls? at->ls->sz : 0) + (at->rs? at->rs->sz : 0) + 1;
	if (at->ls) {
		at->mn[0] = min(at->mn[0], at->ls->mn[0]);
		at->mx[0] = max(at->mx[0], at->ls->mx[0]);
		at->mn[1] = min(at->mn[1], at->ls->mn[1]);
		at->mx[1] = max(at->mx[1], at->ls->mx[1]);
	}
	if (at->rs) {
		at->mn[0] = min(at->mn[0], at->rs->mn[0]);
		at->mx[0] = max(at->mx[0], at->rs->mx[0]);
		at->mn[1] = min(at->mn[1], at->rs->mn[1]);
		at->mx[1] = max(at->mx[1], at->rs->mx[1]);
	}
	//at->push_up();
}

int l, r;

void get(kn*at) {
	if (at == NULL) return ;
	get(at->ls);
	bu[++r] = at;
	get(at->rs);
}

int cnt_reb;
void rebuild(kn*&at) {
	++cnt_reb;
	l=1, r=0;
	get(at);
	for (int i=1; i<=r; ++i) {
		bu[i]->mn[0] = bu[i]->x;
		bu[i]->mx[0] = bu[i]->x;
		bu[i]->mn[1] = bu[i]->y;
		bu[i]->mx[1] = bu[i]->y;
		bu[i]->ls = bu[i]->rs = NULL;
	}
	build(l, r, at);
	//exit(0);
}

bool fucked;

void insert(kn*item, kn*&at) {
	bool fuckthis = false;
	dep ^= 1;
	if (at == NULL) {
		at = item;
		dep = 0;
		return ;
	}
	if (cmp(item, at)) {
		if (!fucked) {
			int sz = at->ls? at->ls->sz+1 : 1;
			if (sz < at->sz * ratio)
				fuckthis = true, fucked = true;
		}
		insert(item, at->ls);
	} else {
		if (!fucked) {
			int sz = at->rs? at->rs->sz+1 : 1;
			if (sz < at->sz * ratio)
				fuckthis = true, fucked = true;
		}
		insert(item, at->rs);
	}
	++at->sz;
	at->mn[0] = min(at->mn[0], item->x);
	at->mx[0] = max(at->mx[0], item->x);
	at->mn[1] = min(at->mn[1], item->y);
	at->mx[1] = max(at->mx[1], item->y);
	if (fuckthis)
		rebuild(at);
}

void insert(int x, int y) {
	loc->mn[0] = loc->mx[0] = x;
	loc->mn[1] = loc->mx[1] = y;
	loc->x = x, loc->y = y;
	loc->sz = 1;
	fucked = false;
	dep = 0;
	insert(loc, root);
	++loc;
}

#define sqr(x) ((LL)(x)*(x))

LL func(int x, int y, kn*at) {
	if (at == NULL) return LLONG_MAX;
	LL ret = 0;
	if (x < at->mn[0]) ret += sqr(x-(at->mn[0]));
	if (at->mx[0] < x) ret += sqr(x-(at->mx[0]));
	if (y < at->mn[1]) ret += sqr(y-(at->mn[1]));
	if (at->mx[1] < y) ret += sqr(y-(at->mx[1]));
	return ret;
}

LL dist(int x, int y, kn*at) {
	return sqr(x-(at->x)) + sqr(y-(at->y));
}

LL res;
void query(int x, int y, kn*at) {
	dep ^= 1;
	int rec = dep;
	if (at == NULL)
		return ;
	res = min(res, dist(x, y, at));
	LL func_ls = func(x, y, at->ls);
	LL func_rs = func(x, y, at->rs);
	if (func_ls < func_rs) {
		if (func_ls < res)
			query(x, y, at->ls);
		if (func_rs < res)
			query(x, y, at->rs);
	} else {
		if (func_rs < res)
			query(x, y, at->rs);
		if (func_ls < res)
			query(x, y, at->ls);
	}
	dep = rec;
};
		
void query(int x, int y) {
	dep = 0;
	res = LLONG_MAX;
	query(x, y, root);
};

const int mod = 998244353;
int n;
int x, y, last_ans;

int main() {
	freopen("gays.in", "r", stdin);
	freopen("gays.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif


	fr(n);
	fr(x, y);
	init_kdt();
	insert(x, y);
	--n;
	last_ans = 0;
	while (n--) {
		fr(x, y);
		x ^= last_ans, y ^= last_ans;
		query(x, y);
		LL ans = res;
		insert(x, y);
		printf("%lld\n", ans);
		last_ans = ans % mod;
	}

	//printf("%d\n", cnt_reb);
	return 0;
}
