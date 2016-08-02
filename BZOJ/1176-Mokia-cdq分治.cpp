#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _j, _k) for(int _i = _j; _i <= _k; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define upu(_a, _b) if(_a < _b) { _a = _b; }
#define upd(_a, _b) if(_b < _a) { _a = _b; }
#define pb push_back
#define mp make_pair
#define i_pair pair<int, int>
#define i_vec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	inline void R(int &t) { scanf("%d", &t); }
	inline void R(LL &t) { scanf("%lld", &t); }
	inline void W(int t) { printf("%d\n", t); }
	inline void W(LL t) { printf("%lld\n", t); }
	template<class T> inline void FR(T &ret, char c = ' ') {
		for(c = getchar(); c < '0' || '9' < c; c = getchar());
		for(ret = 0; '0' <= c && c <= '9'; c = getchar()) {
		 ret = ret * 10 + c - '0';
		}
	}
	inline char gchar() {
		char ret = getchar();
		for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
		return ret;
	}
	template<class T> inline T gcd(T a, T b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) {
			if(index & 1) ret = ret * base % mod;
		}
		return ret;
	}
	const int maxv = 100;
	const int maxe = 100;
	struct Edge {
		int edge;
		int head[maxv], to[maxe], next[maxe];
		Edge() {
			edge = 0;
			memset(head, -1, sizeof head);
		}
		void addedge(int u, int v) {
			to[edge] = v;
			next[edge] = head[u];
			head[u] = edge++;
		}
	};
};
using namespace my_useful_tools;

const int maxn = 200000 + 100;
const int maxm = 2000000 + 100;
struct infoQuery {
	int type, x, y, v, Order, nQuery;
	infoQuery() {}
	infoQuery(int x, int y, int v, int Order, int nQuery):
		x(x), y(y), v(v), Order(Order), nQuery(nQuery) {
	}
} a[maxn];
int n, m, cntQuery;
LL C[maxm], ans[maxn];
void addQuery(int x, int y, int v, int q) {
	if(x != 0 && y != 0) {
		++m;
		a[m] = infoQuery(x, y, v, m, q);
	}
}
void Modify(int x, int delta) {
	while(x <= n) {
		C[x] += delta;
		x += x & (-x);
	}
}
LL getSum(int x) {
	LL ret = 0;
	while(x) {
		ret += C[x];
		x -= x & (-x);
	}
	return ret;
}
bool cmp(const int &lhs, const int &rhs) {
	return a[lhs].x < a[rhs].x;
}
int f[maxn], tmp[maxn];

void solve(int l, int r) {
	if(l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	for(int i = l, s1 = l, s2 = mid + 1; i <= r; ++i) {
		if(f[i] <= mid) {
			tmp[s1++] = f[i];
		} else {
			tmp[s2++] = f[i];
		}
	}
	memcpy(f + l, tmp + l, sizeof (int) * (r - l + 1));
	int now = l;
	for(int i = mid + 1; i <= r; ++i) {
		int x = f[i];
		if(a[x].nQuery != 0) {
			while(now <= mid && a[f[now]].x <= a[x].x) {
				if(a[f[now]].nQuery == 0) {
					Modify(a[f[now]].y, a[f[now]].v);
				}
				++now;
			}
			ans[a[x].nQuery] += getSum(a[x].y) * a[x].v;
		}
	}
	for(int i = l; i < now; ++i) {
		if(a[f[i]].nQuery == 0) {
			Modify(a[f[i]].y, -a[f[i]].v);
		}
	}
	solve(l, mid), solve(mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1176.in", "r", stdin); freopen("1176.out", "w", stdout);
#endif
	int t, flag = 1, x, y, X1, X2, Y1, Y2, v;
	scanf("%d", &t);
	while(flag) {
		scanf("%d", &n);
		m = 0, cntQuery = 0;
		while(true) {
			scanf("%d", &t);
			if(t == 3 || t == 0) {
				flag = t == 3 ? 0 : flag;
				break;
			} else if(t == 1) {
				scanf("%d%d%d", &x, &y, &v);
				addQuery(x, y, v, 0);
			} else {
				scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
				++cntQuery;
				addQuery(X1 - 1, Y1 - 1, 1, cntQuery), addQuery(X2, Y2, 1, cntQuery);
				addQuery(X1 - 1, Y2, -1, cntQuery), addQuery(X2, Y1 - 1, -1, cntQuery);
			}
		}
		for(int i = 1; i <= m; ++i) {
			f[i] = i;
		}
		sort(f + 1, f + m + 1, cmp);
		/*
		W(m);
		rep(i, 1, m) {
			W(a[f[i]].x);
		}
		*/
		solve(1, m);
		for(int i = 1; i <= cntQuery; ++i) {
			printf("%lld\n", ans[i]);
			ans[i] = 0ll;
		}
	}

	return 0;
}

