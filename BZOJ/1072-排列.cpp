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
    inline void R(int &t1, int &t2) { scanf("%d%d", &t1, &t2); }
    inline void R(int &t1, int &t2, int &t3) { scanf("%d%d%d", &t1, &t2, &t3); }
    inline void R(LL &t) { scanf("%lld", &t); }
    inline void R(LL &t1, LL &t2) { scanf("%lld%lld", &t1, &t2); }
    inline void W(int t) { printf("%d\n", t); }
    inline void WB(int t) { printf("%d ", t); }
    inline void W(int t1, int t2) { printf("%d %d\n", t1, t2); }
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

const int maxn = (1 << 10);
int f[maxn][maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1072.in", "r", stdin); freopen("1072.out", "w", stdout);
#endif
	int d, T;
	char s[12];
	int cnt[12];
	scanf("%d", &T);
	while(T--) {
		scanf("%s %d", s, &d);
		int S = strlen(s);
		memset(cnt, 0, sizeof cnt);
		memset(f, 0, sizeof f);
		for(int i = 0; i < S; ++i) {
			++cnt[s[i] - '0'];
		}
		f[0][0] = 1;
		for(int i = 0; i < (1 << S); ++i) {
			for(int j = 0; j < d; ++j) {
				for(int k = 0; k < S; ++k) {
					if(!(i & (1 << k))) {
						f[i | (1 << k)][(j * 10 + s[k] - '0') % d] += f[i][j];
					}
				}
			}
		}
		int ans = f[(1 << S) - 1][0];
		for(int i = 0; i < 10; ++i) {
			for(int j = 1; j <= cnt[i]; ++j) {
				ans /= j;
			}
		}
		printf("%d\n", ans);
	}
    return 0;
}

