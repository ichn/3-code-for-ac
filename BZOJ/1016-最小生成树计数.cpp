#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
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

const int maxn = 100 + 10;
struct DisjoinSet {
	int fa[maxn];
	void clear() {
		rep(i, 0, maxn - 1) {
			fa[i] = i;
		}
	}
	int find(int x) {
		if(fa[x] == x) {
			return x;
		} else {
			return find(fa[x]);
		}
	}
	void Union(int x, int y) {
		fa[find(y)] = find(x);
	}
} A, B;
struct edges {
	int f, t, w;
	edges() {
	}
	edges(int f, int t, int w):f(f), t(t), w(w) {
	}
	bool operator < (const edges &rhs) const {
		return w < rhs.w;
	}
} e[maxn * 10];
const int mod = 31011;
int n, m;

int dfs(int k, int limit, int remain) {
	if(remain == 0) {
		return 1;
	} else {
		int ret = 0;
		rep(i, k + 1, limit) {
			if(B.find(e[i].f) != B.find(e[i].t)) {
				int rec = B.find(e[i].f);
				B.Union(e[i].t, e[i].f);
				ret += dfs(i, limit, remain - 1);
				B.fa[rec] = rec;
			}
		}
		return ret;
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1016.in", "r", stdin); freopen("1016.out", "w", stdout);
#endif
	R(n), R(m);
	rep(i, 0, m - 1) {
		int f, t, w;
		R(f), R(t), R(w);
		e[i] = edges(f, t, w);
	}
	sort(e, e + m);
	A.clear(), B.clear();
	int cnt = 0;
	rep(i, 0, m - 1) {
		if(A.find(e[i].f) != A.find(e[i].t)) {
			A.Union(e[i].f, e[i].t);
			++cnt;
		}
	}
	if(cnt != n - 1) {
		W(0);
	} else {
		int ans = 1, left = 0;
		A.clear();
		e[m].w = -1;
		rep(i, 0, m - 1) {
			if(e[i].w != e[i + 1].w) {
				int calc = 0;
				rep(j, left, i) {
					if(A.find(e[j].f) != A.find(e[j].t)) {
						A.Union(e[j].f, e[j].t);
						++calc;
					}
				}
				(ans *= dfs(left - 1, i, calc)) %= mod;
	//			W(ans);
				rep(j, left, i) {
					if(B.find(e[j].f) != B.find(e[j].t)) {
						B.Union(e[j].f, e[j].t);
						++calc;
					}
				}
				left = i + 1;
			}
		}
		W(ans);
	}

    return 0;
}
