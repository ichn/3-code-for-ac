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
 
const int maxmu = 50000 + 100;
int mu[maxmu + 100], prime[maxmu], tot, sum[maxmu + 100];
bool vis[maxmu + 100];
int a, b, k;
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("1101.in", "r", stdin); freopen("1101.out", "w", stdout);
#endif
	mu[1] = 1;
	for(int i = 2; i <= maxmu; ++i) {
		if(!vis[i]) mu[i] = -1, prime[++tot] = i;
		for(int j = 1; j <= tot; ++j) {
			if(i * prime[j] > maxmu) break;
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= maxmu; ++i) sum[i] = sum[i - 1] + mu[i];
	int nCase;
	scanf("%d", &nCase);
	while(nCase--) {
		scanf("%d%d%d", &a, &b, &k);
		a /= k, b /= k;
		if(b < a) swap(a, b);
		int last;
		int ans = 0;
		for(int i = 1; i <= a; i = last + 1) {
			last = min(a / (a / i), b / (b / i));
			ans += (sum[last] - sum[i - 1]) * (a / i) * (b / i);
		}
		printf("%d\n", ans);
	}
 
    return 0;
}
