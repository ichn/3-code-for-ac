#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define reo(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
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
 
const int Mod = 998244353;
const int Maxn = 500000;
const int g = 3;

LL fpm(LL base, int index, int mod) {
	LL ret = 1;
	for(; index; base = base*base%mod, index>>=1)
		if(index&1) ret = ret*base%mod;
	return ret;
}

int ans[Maxn], tmp0[Maxn], tmp1[Maxn];
/*

void fft(int*a, int N, int rev=1) {
	if(N==1) return ;
	int h = N>>1, *a0 = a, *a1 = a+h, Tw = 1, Wn = fpm(g, (Mod-1)/N, Mod);
	if(rev==-1) Wn = fpm(Wn, Mod-2, Mod)%Mod;
	memcpy(tmp, a, sizeof(int)*N);
	reo(i, 0, h)
		a0[i] = tmp[i<<1], a1[i] = tmp[i<<1|1];
	fft(a0, h, rev), fft(a1, h, rev);
	for(int i=0; i < h; Tw = (LL)Tw*Wn%Mod, ++i) {
		tmp[i] = (a0[i] + (LL)Tw * a1[i]%Mod)%Mod,
		tmp[i+h] = (a0[i] - (LL)Tw * a1[i]%Mod)%Mod;
	}
	memcpy(a, tmp, sizeof(int)*N);
}
*/

int w[Maxn + 5];

void fft(int *a, const int &n, const int &dep = 0)
{
	static int tmp[Maxn + 5];
	if (n == 1) return;
	int half = n >> 1;
	fft(a, half, dep + 1);
	fft(a + (1 << dep), half, dep + 1);
	reo(i, 0, half)
	{
		int s = a[(i << 1) << dep];
		int t = (LL)a[(i << 1 | 1) << dep] * w[i << dep] % Mod;
		tmp[i] = s + t;
		tmp[i + half] = s - t;
	}
	reo(i, 0, n) a[i << dep] = tmp[i] % Mod;
}

void work(int l, int r) {
	if(r <= l + 1) {
		ans[l] = l;
		return ;
	}
	int m = (l+r)>>1, N = r-l+1;
	while(N & (N-1)) ++N;
	work(l, m), work(m, r);
	int ls = m-l, rs = r-m;
	reo(i, 0, ls) tmp0[i] = ans[l+i]; tmp0[ls] = 1; rep(i, ls+1, N) tmp0[i] = 0;
	reo(i, 0, rs) tmp1[i] = ans[m+i]; tmp1[rs] = 1; rep(i, rs+1, N) tmp1[i] = 0;
	if(N <= 128) {
		reo(i, 0, r-l) {
			int &cnt = ans[l+i];
			cnt = 0;
			rep(j, 0, i)
				(cnt += (LL)tmp0[j]*tmp1[i-j]%Mod) %= Mod;
		}
		return ;
	}
	w[0] = 1;
	int step = fpm(g, (Mod-1)/N, Mod);
	reo(i, 1, N) w[i] = (LL)w[i-1]*step%Mod;
	fft(tmp0, N), fft(tmp1, N);
	reo(i, 0, N) tmp0[i] = (LL)tmp0[i]*tmp1[i]%Mod;
	reverse(w+1, w+N);
	fft(tmp0, N);
	int t = fpm(N, Mod-2, Mod);
	reo(i, 0, r-l) ans[l+i]=(LL)tmp0[i]*t%Mod;
}

 
int main() {
#ifdef love_sbit
	file(count);
#else
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	int n, a, b;
	fr(n, a, b);
	/*
	if(n <= 5000 + 1000) {
		static const int maxn = 5e3 + 100;
		static int S[maxn][maxn], sum[maxn];
		S[1][1] = 1;
		for(int i = 2; i <= n; ++i)
			for(int j = 1; j <= i; ++j)
				S[i][j] = (S[i - 1][j - 1] + (LL)(i - 1) * S[i - 1][j] % Mod) % Mod;
		for(int i = 1; i <= b; ++i)
			sum[i] = (LL)(sum[i - 1] + S[n][i]) % Mod;
		printf("%d\n", (sum[b] + Mod - sum[a - 1]) % Mod);
	} 
	*/
	ans[n] = 1;
	work(0, n);
	int sum = 0;
	rep(i, a, b) (sum += ans[i]) %= Mod;
	printf("%d\n", (sum+Mod)%Mod);
	return 0;
}
