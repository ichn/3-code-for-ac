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
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你所深爱着的
//
// 永远不要相信自己的意志力

#define sn splay_node
#define lc ch[0]
#define rc ch[1]

const int maxn = 1e5 + 1000;
// (=1, )=-1
struct splay_node {
	sn *ch[2], *fa;
	int fm, fn, bm, bn; // 最大/最小前缀和，最大/最小后缀和
	int c, s, z; // 当前节点的权值，子树和，子树大小
	bool rpl, swp, inv; // replace，swap，invert
	sn() {
		ch[0] = ch[1] = fa = NULL;
		rpl = swp = inv = false;
	}
	// -1 1 -1 1 1 -1 1 1 -1
	void upd() {
		s = (lc?lc->s:0) + (rc?rc->s:0) + c;
		z = (lc?lc->z:0) + (rc?rc->z:0) + 1;
		fm = max(lc?lc->fm:0, (lc?lc->s:0)+c+(rc?rc->fm:0));
		fn = min(lc?lc->fn:0, (lc?lc->s:0)+c+(rc?rc->fn:0));
		bm = max(rc?rc->bm:0, (rc?rc->s:0)+c+(lc?lc->bm:0));
		bn = min(rc?rc->bn:0, (rc?rc->s:0)+c+(lc?lc->bn:0));
	}
	// rank(replace) > rank(swap) = rank(invert)
	void tag() {
		if (inv) {
			if (lc) {
				swap(lc->fn, lc->fm);
				swap(lc->bn, lc->bm);
				lc->fn = -lc->fn;
				lc->fm = -lc->fm;
				lc->bn = -lc->bn;
				lc->bm = -lc->bm;
				lc->c = -lc->c;
				lc->s = -lc->s;
				lc->inv ^= 1;
			}
			if (rc) {
				swap(rc->fn, rc->fm);
				swap(rc->bn, rc->bm);
				rc->fn = -rc->fn;
				rc->fm = -rc->fm;
				rc->bn = -rc->bn;
				rc->bm = -rc->bm;
				rc->c = -rc->c;
				rc->s = -rc->s;
				rc->inv ^= 1;
			}
			inv = false;
		}
		if (rpl) {
			if (lc) {
				lc->swp = lc->inv = 0;
				lc->rpl = true;
				lc->c = c;
				lc->s = c*lc->z;
				if (c > 0)
					lc->fm = lc->bm = c*lc->z, lc->fn = lc->bn = 0;
				else lc->fn = lc->bn = c*lc->z, lc->fm = lc->bm = 0;
			}
			if (rc) {
				rc->swp = rc->inv = 0;
				rc->rpl = true;
				rc->c = c;
				rc->s = c*rc->z;
				if (c > 0)
					rc->fm = rc->bm = c*rc->z, rc->fn = rc->bn = 0;
				else rc->fn = rc->bn = c*rc->z, rc->fm = rc->bm = 0;
			}
			rpl = false;
		}
		if (swp) {
			if (lc) {
				swap(lc->lc, lc->rc);
				swap(lc->fn, lc->bn);
				swap(lc->fm, lc->bm);
				lc->swp ^= 1;
			}
			if (rc) {
				swap(rc->lc, rc->rc);
				swap(rc->fn, rc->bn);
				swap(rc->fm, rc->bm);
				rc->swp ^= 1;
			}
			swp = false;
		}
	}
} pool[maxn], *root, *lft, *rht, *loc;


void init() {
	loc = pool;
	lft = loc++, rht = loc++;
	lft->c = 1, rht->c = -1;
	root = lft;
	lft->ch[1] = rht;
	rht->fa = lft;
	rht->upd();
	lft->upd();
}

void rot(sn *x, int d) {
	sn *y = x->fa, *z = y->fa;
	y->ch[d^1] = x->ch[d];
	if (x->ch[d]) x->ch[d]->fa = y;
	x->ch[d] = y;
	y->fa = x;
	x->fa = z;
	if (z) z->ch[z->ch[1] == y] = x;
	y->upd();
}

sn *stk[maxn];
int top;

void splay(sn *x, sn *goal) {
	if (x == goal) return ;
	top = 0;
	stk[++top] = x;
	while (stk[top] != goal)
		++top, stk[top] = stk[top-1]->fa;
	if (goal == NULL) --top;
	while (top)
		stk[top]->tag(), --top;
	while (x->fa != goal) {
		sn *y = x->fa, *z = y->fa;
		int rx = x == y->ch[0];
		if (z == goal) rot(x, rx);
		else {
			int ry = y == z->ch[0];
			if (rx == ry) rot(y, ry);
			else rot(x, rx);
			rot(x, ry);
		}
	}
	x->upd();
	if (goal == NULL)
		root = x;
}

void print(sn *x, int d=0) {
	if (!x) return ;
	print(x->lc, d+1);
	rep(i, 1, d) {
		printf("	");
	}
	printf("%d %d %d %d %d %d %d\n", x-pool, x->fa-pool, x->ch[0]-pool, x->ch[1]-pool, x->c, x->s, x->z);
	print(x->rc, d+1);
}

void out(sn *p) {
	if (!p) return ;
	p->tag();

	out(p->lc);
	//printf("%c", p->c == -1 ? ')' : '(');
	out(p->rc);
}

char a[maxn];
void build(sn *&x, int l, int r) {
	if (r < l) return ;
	x = loc++;
	int mid = (l+r)>>1;
	build(x->ch[0], l, mid-1);
	if (x->ch[0]) x->ch[0]->fa = x;
	build(x->ch[1], mid+1, r);
	if (x->ch[1]) x->ch[1]->fa = x;
	x->c = a[mid] == '(' ? 1 : -1;
	x->upd();
}

int n, m;
char ope[20];

sn*select(int rk) {
	sn *u = root;
	while (true) {
		u->tag();
		if (u->lc && rk <= u->lc->z)
			u = u->lc;
		else if ((u->lc?u->lc->z:0)+1 < rk)
			rk -= (u->lc?u->lc->z:0)+1, u = u->rc;
		else return u;
	}
}

sn* make_range(int l, int r) {
	splay(select(l-1), NULL);
	splay(select(r+1), root);
	return root->ch[1]->ch[0];
}
 
int main() {
	file(2329);
 
	init();
	fr(n, m);
	scanf("%s", a + 1);
	build(rht->ch[0], 1, n);
	if (rht->ch[0]) rht->ch[0]->fa = rht;
	rht->upd(), lft->upd();
	//print(root);

	//out(root);
	//puts("");
	while (m--) {
		int l, r;
		scanf("%s %d %d", ope, &l, &r);
		++l, ++r;
		sn *rt = make_range(l, r);
	//	printf("si %d\n", rt->z);
	//	print(rt);
	//	exit(0);
		if (ope[0] == 'R') {
			char c = gchar();
			rt->rpl = true;
			rt->swp = rt->inv = false;
			rt->c = (c == '(') ? 1 : -1;
			rt->s = rt->c*rt->z;
			if (rt->c > 0)
				rt->fm = rt->bm = rt->s, rt->bn = rt->fn = 0;
			else rt->fm = rt->bm = 0, rt->bn = rt->fn = rt->s;
		} else if (ope[0] == 'Q') {
			//out(root);
			printf("%d\n", (1-rt->fn)/2 + (1+rt->bm)/2);
			continue;
		} else if (ope[0] == 'I') {
			rt->inv ^= 1;
			swap(rt->fm, rt->fn);
			swap(rt->bm, rt->bn);
			rt->fn = -rt->fn;
			rt->fm = -rt->fm;
			rt->bn = -rt->bn;
			rt->bm = -rt->bm;
			rt->c = -rt->c;
			rt->s = -rt->s;
		} else {
			rt->swp ^= 1;
			swap(rt->fn, rt->bn);
			swap(rt->fm, rt->bm);
			swap(rt->lc, rt->rc);
		}
	//	rt->tag();

		//	out(root);
	}
 
	return 0;
}

