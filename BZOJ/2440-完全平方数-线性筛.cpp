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
 
const int maxn = 50000;
int mu[maxn + 100], prime[maxn], tot;
bitset<maxn + 100> vis;
 
void get_mu() {
	mu[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!vis[i]) { prime[tot++] = i, mu[i] = -1; }
		for(int j = 0; j < tot; ++j) {
			int t = i * prime[j];
			if(t > maxn) break;
			vis[t] = 1;
			mu[t] = -mu[i];
			if(i % prime[j] == 0) {
				mu[t] = 0;
				break;
			}
		}
	}
}
 
int calc(int n) {
	int ret = 0;
	for(int i = 1; ; ++i) {
		if((LL)i * i > n) { break; }
		if(mu[i] != 0)
			ret = ret + mu[i] * (n / i / i);
	}
	return ret;
}
 
int main() {
	int nCase, n;
	scanf("%d", &nCase);
	get_mu();
	while(nCase--) {
		scanf("%d", &n);
		LL l = 0, r = n * 2;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(calc(mid) < n) {
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		printf("%lld\n", l);
	}
 
    return 0;
}
