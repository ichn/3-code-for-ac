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

const int maxn = 5e6 + 100;
const int maxq = 2e5 + 100;

char str[maxn];

int n, m;

_pir y[maxn];
int cy, pos[maxn];
//对询问离线处理
struct Query {
	int id, l, r, k;
	bool operator < (const Query&rhs) const {
		return k < rhs.k;
	}
	Query() {}
	Query(int id):id(id) {
		fr(l, r, k);
		//scanf("%d %d %d", &l, &r, &k);
	}
} q[maxq];

struct MdfInfo {
	int pos, val;
	MdfInfo() {}
	MdfInfo(int pos, int val):pos(pos), val(val) {}
	bool operator < (const MdfInfo&rhs) const {
		return val < rhs.val;
	}
};

MdfInfo mi[maxn];
int cmi;

int tr[maxn<<2];

void mdf(int p, int v, int l, int r, int rt) {
	if (l == r) {
		tr[rt] = v;
		return ;
	}
	int mid = (l+r)>>1;
	if (p <= mid)
		mdf(p, v, l, mid, rt<<1);
	else mdf(p, v, mid+1, r, rt<<1|1);
	tr[rt] = tr[rt<<1] + tr[rt<<1|1];
}

int qry(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr)
		return tr[rt];
	int mid = (l+r)>>1;
	int ret = 0;
	if (ql <= mid)
		ret += qry(ql, qr, l, mid, rt<<1);
	if (mid < qr)
		ret += qry(ql, qr, mid+1, r, rt<<1|1);
	return ret;
}

int qSum(int ql, int qr) {
	if (qr < ql) return 0;
	return qry(ql, qr, 1, cy, 1);
}

void doMdf(MdfInfo x) {
	//printf("mdf %d %d\n", x.pos, y[x.pos].second / x.val);
	mdf(x.pos, y[x.pos].second / x.val, 1, cy, 1);
}

LL ans[maxq];

int main() {
	freopen("tabs.in", "r", stdin);
	freopen("tabs.out", "w", stdout);

	gets(str + 1);
	n = strlen(str + 1);
	(str + 1)[n] = 'T';
	n = strlen(str + 1);
	scanf("%d", &m);
	
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		pos[i] = cy + 1;
		if (str[i] != 'T')
			++cnt;
		else {
			y[++cy] = make_pair(i, cnt);
			if (cnt == 0) continue;
			int j = 1;
			for (j = 1; j <= cnt; j = cnt / (cnt / j) + 1)
				mi[cmi++] = (MdfInfo(cy, j));
			mi[cmi++] = (MdfInfo(cy, j));
			cnt = 0;
		}
	}

	for (int c = 1; c <= m; ++c)
		q[c] = Query(c);

	sort(q + 1, q + m + 1);
	sort(mi, mi + cmi);

	int ps = 0, mx_ps = cmi;

	for (int i = 1; i <= m; ++i) {
		while (ps < mx_ps && mi[ps].val <= q[i].k) {
			doMdf(mi[ps]);
			++ps;
		}
		ans[q[i].id] = 0;
		int k = q[i].k;
		if (pos[q[i].l] == pos[q[i].r]) {
			ans[q[i].id] = q[i].r - q[i].l;
			if (q[i].r == y[pos[q[i].r]].first)
				ans[q[i].id] += k - (ans[q[i].id] % k);
			else ++ans[q[i].id];
		} else {
			ans[q[i].id] += (y[pos[q[i].l]].first - q[i].l) / k;

			LL num = 1;
			num += (pos[q[i].r] - 1) - (pos[q[i].l] + 1) + 1;
			ans[q[i].id] += qSum(pos[q[i].l]+1, pos[q[i].r]-1);
		//	printf("%lld\n", ans[q[i].id]);
			ans[q[i].id] *= k;
			ans[q[i].id] += num * k;
			if (q[i].r == y[pos[q[i].r]].first) {
				int tmp = y[pos[q[i].r]].second;
				ans[q[i].id] += tmp + (k - tmp % k);
			} else ans[q[i].id] += y[pos[q[i].r]].second + 1 - (y[pos[q[i].r]].first - q[i].r);
		//	printf("%d\n", q[i].id);
		}
	}

	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);

	return 0;
}
