#include <bits/stdc++.h>
using namespace std;
namespace my_zone {
#define rep(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define rgo(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define clr(t) memset(t, 0, sizeof t);
#define clo(t, v) memcpy(t, v, sizeof t);
#define cls(t, v) memset(t,v,sizeof t);
#define pc(c) putchar(c)
#define gc() getchar()
    typedef pair<int, int> ipir;
    typedef vector<int> ivec;
    typedef set<int> iset;
    typedef long long LL;
    typedef double DB;
    inline char gchar(char r=gc()) {
        for(;r==' '||r=='\n'||r=='\r';
                r=gc());return r;}
    template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
        if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
        ret = ret * flag;
    }
    inline int fr() { int x; fr(x); return x; }
    template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }

};
using namespace my_zone;

const int INF = 0x7f7f7f7f;

const int maxN = 1e5 + 100;

char ans[maxN], s[maxN];
int sa[maxN], t[maxN], t2[maxN], c[maxN], n;
int rnk[maxN], h[maxN];
void get_sa(int m) {
    int i, *x = t, *y = t2;
    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) c[x[i] = s[i]]++;
    for (i = 1; i < m; ++i) c[i] += c[i-1];
    for (i = n-1; 0 <= i; --i) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k<<=1) {
        int p = 0;
        for (i = n-k; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= k) y[p++] = sa[i] - k;
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[y[i]]]++;
        for (i = 1; i < m; ++i) c[i] += c[i-1];
        for (i = n-1; 0<=i; --i) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (i = 1; i < n; ++i)
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]) ? p-1 : p++;
        if (p >= n) break;
        m = p;
    }
    int j, k = 0;
    for (i = 0; i < n; ++i) rnk[sa[i]] = i;
    for (i = 0; i < n; ++i) {
        if (k) k--;
        if (rnk[i] != 0) {
            j = sa[rnk[i]-1];
            while (s[i+k] == s[j+k]) ++k;
            h[rnk[i]] = k;
        }
    }
}


int stk[maxN], tp;
int ch[maxN][2];

int sum[maxN];

int al, ar;

int get(int l, int r, int sub) {
	if (r < l) return 0;
	return sum[r] - (l == 0 ? 0 : sum[l-1]) - (r - l + 1) * sub;
}

void solve(int u, int l, int r, int k, int sub = 0) {
	if (r < l) {
		assert(false);
		return ;
	}
	if (l == r) {
		al = sa[l], ar = sa[l] + sub + k;
		return ;
	}
	h[u] -= sub;
	if (h[u] != 0) {
		if ((r - l + 1) * h[u] >= k) {
			al = sa[l];
			ar = al + sub;
			while (k > 0) {
				k -= r - l + 1;
				++ar;
			}
			return ;
		} else {
			k -= (r - l + 1) * h[u];
			sub += h[u];
			h[u] = 0;
		}
	}

	int t = get(l, u-1, sub);
	printf("%d %d %d\n", l, u, t);
	if (k <= t) {
		solve(ch[u][0], l, u-1, k, sub);
	} else {
		k -= t;
		if (sa[u] + sub + k < n) {
			al = sa[u], ar = sa[u] + sub + k;
			return ;
		}
		solve(ch[u][1], u+1, r, k - get(u, u, sub), sub);
	}
}

int main() {
#ifdef lol
    freopen("3553.in", "r", stdin);
    freopen("3553.out", "w", stdout);
#endif
    int T = fr();
    for (int tt = 1; tt <= T; ++tt) {
		int k;
		scanf("%s %d\n", s, &k);

		n = strlen(s);
		s[n] = '|';
		++n;
		s[n] = '\0';
		get_sa(200);
		--n;
		s[n] = '\0';
		tp = 0;
		memset(ch, 0, sizeof ch);
		puts("sa :");
		for (int i = 0; i < n; ++i)
			printf("%d ", sa[i]);
		puts("");
		sum[0] = n - sa[0];
		for (int i = 1; i < n; ++i)
			sum[i] = sum[i - 1] + n - sa[i];
		for (int i = 1; i < n; ++i) {
			while (tp > 0 && h[i] < h[stk[tp]]) {
				ch[stk[tp]][1] = 0;
				ch[i][0] = stk[tp];
				--tp;
			}
			ch[stk[tp]][1] = i;
			stk[++tp] = i;
		}
		solve(ch[0][1], 0, n - 1, k);

        printf("Case %d: ", tt);
		for (int j = al; j < ar; ++j)
			putchar(s[j]);
		puts("");
    }

    return 0;
}
