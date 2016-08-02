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

const int maxNode = 1e7;
const int maxQueryNode = 4e5 + 100;
const int maxSegNode = (maxQueryNode<<2);
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y):x(x), y(y) {}
	bool operator < (const Point&rhs) const {
		return x < rhs.x || (x==rhs.x && y < rhs.y);
	}
	Point operator - (const Point&rhs) {
		return Point(x-rhs.x, y-rhs.y);
	}
} pool[maxNode], *loc = pool, P[maxQueryNode];
LL Dot(Point a, Point b) {
	return (LL)a.x*b.x+(LL)a.y*b.y;
}
LL Cross(Point a, Point b) {
	return (LL)a.x*b.y-(LL)a.y*b.x;
}

struct ConvexHull {
	Point *up, *dw;
	int un, dn;
	void buildConvexHull(Point*p, int sz) {
		sort(p, p+sz);
		up = loc;
		int cnt = -1;
		reu(i, 0, sz) {
			while (cnt > 0 && Cross(p[i]-up[cnt-1], up[cnt]-up[cnt-1]) <= 0)
				--cnt;
			++cnt, up[cnt] = p[i];
		}
		loc += cnt+1;
		un = cnt+1;
		dw = loc;
		cnt = -1;
		reu(i, 0, sz) {
			while (cnt > 0 && Cross(p[i]-dw[cnt-1], dw[cnt]-dw[cnt-1]) >= 0)
				--cnt;
			++cnt, dw[cnt] = p[i];
		}
		loc += cnt+1;
		dn = cnt+1;
	}
	LL qMaxDot(Point p) {
		LL ret = LLONG_MIN;
		int l = 0, r = un-1;
		while (l <= r) {
			if (r - l + 1 <= 2) {
				for (register int i = l; i <= r; ++i) {
					ret = max(ret, Dot(up[i], p));
				}
				break;
			}
			int mid = (l+r)>>1;
			if (Dot(up[mid], p) < Dot(up[mid+1], p)) {
				l = mid+1;
			} else {
				r = mid;
			}
		}
		l = 0, r = dn-1;
		while (l <= r) {
			if (r - l + 1 <= 2) {
				for (register int i = l; i <= r; ++i) {
					ret = max(ret, Dot(dw[i], p));
				}
				break;
			}
			int mid = (l+r)>>1;
			if (Dot(dw[mid], p) < Dot(dw[mid+1], p)) {
				l = mid+1;
			} else {
				r = mid;
			}
		}
	//	return ret;
	//	LL tmp = LLONG_MIN;
	//	for (int i = 0; i < un; ++i)
	//		tmp = max(tmp, Dot(up[i], p));
	//	for (int i = 0; i < dn; ++i)
	//		tmp = max(tmp, Dot(dw[i], p));
		return ret;
	}
} ch_pool[maxSegNode], *ch_loc = ch_pool;

struct SegNode {
	SegNode*lc, *rc;
	ConvexHull*ch;
	int l, r, sz;
	SegNode() {
		lc = rc = NULL;
		ch = ch_loc++;
		sz = 0;
	}
} sn_pool[maxSegNode], *sn_loc = sn_pool, *root;

void buildSegTree(int l, int r, SegNode*&rt) {
	if (rt == NULL) {
		rt = sn_loc++;
		rt->l = l, rt->r = r;
	}
	if (l == r) return ;
	int mid = (l+r)>>1;
	buildSegTree(l, mid, rt->lc), buildSegTree(mid+1, r, rt->rc);
}

void addPoint(int pos, SegNode*rt) {
	if (rt->l == rt->r) {
		++rt->sz;
		if (rt->sz == rt->r-rt->l+1)
			rt->ch->buildConvexHull(P+(rt->l), rt->sz);
		return ;
	}
	int mid = (rt->l+rt->r)>>1;
	if (pos <= mid) addPoint(pos, rt->lc);
	else addPoint(pos, rt->rc);
	rt->sz = rt->lc->sz+rt->rc->sz;
	if (rt->sz == rt->r-rt->l+1)
		rt->ch->buildConvexHull(P+(rt->l), rt->sz);
}

Point qp;
LL Query(int ql, int qr, SegNode*rt) {
	if (ql <= rt->l && rt->r <= qr) {
		return rt->ch->qMaxDot(qp);
	}
	int mid = (rt->l+rt->r)>>1;
	LL ret = LLONG_MIN;
	if (ql <= mid) ret = max(ret, Query(ql, qr, rt->lc));
	if (mid < qr) ret = max(ret, Query(ql, qr, rt->rc));
	return ret;
}

int n;
bool e;
LL last_ans = 0LL;

inline int decode(int x) {
	if (e)
		return x ^ (last_ans & 0x7fffffff);
	else return x;
}

void print_tree(SegNode*rt) {
	if (rt == NULL) return ;
	printf("%d %d %d\n", rt->l, rt->r, rt->sz);
	print_tree(rt->lc);
	print_tree(rt->rc);
}

int main() {
#ifdef love_lhy
	freopen("vset.in", "r", stdin);
	freopen("vset.out", "w", stdout);
#endif
	fr(n), e=(gchar()!='E');
	int x, y, ql, qr;
	int cnt = 0;
	buildSegTree(1, n, root);
	while (n--) {
		if (gchar() == 'A') {
			x = decode(fr()), y = decode(fr());
			P[++cnt] = Point(x, y);
			addPoint(cnt, root);
		} else {
			x = decode(fr()), y = decode(fr());
			ql = decode(fr()), qr = decode(fr());
	//		printf("%d %d %d %d\n", x, y, ql, qr);
			qp = Point(x, y);
			last_ans = Query(ql, qr, root);
			printf("%lld\n", last_ans);
		}
	//	print_tree(root);
	}

	return 0;
}
