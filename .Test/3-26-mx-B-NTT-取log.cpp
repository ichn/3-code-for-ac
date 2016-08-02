#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for (int i=j; i<=k; ++i)
#define reu(i, j, k) for (int i=j; i<k; ++i)
#define red(i, j, k) for (int i=j; k<=i; --i)
#define clr(x) memset(x, 0, sizeof x)
#define l(i) i[0]

typedef long long LL;

const int mod = 998244353;
const int _g = 3;
const int maxn = 40000;
const int maxm = 200;
int p, p_g;
int n[maxm], l[maxm], r[maxm], ans[maxn], b, inv[maxn], ind[maxn], pw[maxn];

int fpm(LL b, int i, int m) {
	LL ret = 1;
	for (; i; i>>=1, (b*=b)%=m)
		if (i&1) (ret*=b)%=m;
	return ret;
}

void trans(char *s, int *t) {
	int &l = t[0], sl = strlen(s), rem, j;
	reu(i, 0, sl) s[i] = s[i]-'0';
	while (sl) {
		rem = j = 0;
		reu(i, 0, sl) {
			rem = rem*10+s[i];
			if (rem >= p) {
				s[j++] = rem / p;
				rem %= p;
			} else if (j) s[j++] = 0;
		}
		sl = j;
		t[++l] = rem;
	}
}

const int maxN = maxn*10;
int f[maxN], g[maxN], c[maxN];
int t1[maxN], t2[maxN], t3[maxN], pos;
int N, L, rev[maxN], rG[2][maxN], invN;

void dft(int *a, int n, int d) {
	reu(i, 0, n) 
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int i=2; i <= n; i<<=1) {
		int s = rG[d][i], u, v, c;
		for (int k, j=0; j < n; j+=i) {
			for (k=j, c=1; k<j+(i>>1); ++k, c=(LL)c*s%mod) {
				u = a[k]%mod;
				v = (LL)c*a[k+(i>>1)]%mod;
				a[k] = (u+v)%mod, a[k+(i>>1)] = (u-v+mod)%mod;
			}
		}
	}
	if (d == 1)
		reu(i, 0, n) a[i] = (LL)a[i]*invN%mod;
}

void solve(int *d, int v) {
	if (d[b] == -1) return ;
	clr(f), clr(g);
	f[0] = g[0] = 1;
	rep(i, 1, b) {
		reu(j, 0, N)
			c[j] = 0, t1[j] = 0, t2[j] = 0;
		c[n[i]]=1;
		rep(j, n[i]+1, p) {
			++t1[ind[c[j-1]]];
			if (j-1 < d[i]) ++t2[ind[c[j-1]]];
			if (j-1 == d[i]) pos = ind[c[j-1]];
			c[j] = (LL)c[j-1]*j%p*inv[j-n[i]]%p;
		}
		if (d[i] < n[i]) reu(i, 0, N) f[i] = 0;
		else {
			reu(i, 0, p-1) t3[i] = 0;
			reu(i, 0, p-1) (t3[(i+pos)%(p-1)] += f[i]) %= mod;
			reu(i, 0, p-1) f[i] = t3[i];
		}
		dft(t1, N, 0);
		dft(t2, N, 0);
		dft(g, N, 0);
		reu(i, 0, N) {
			t1[i] = (LL)t1[i]*g[i]%mod;
			t2[i] = (LL)t2[i]*g[i]%mod;
		}
		dft(t1, N, 1);
		dft(t2, N, 1);
		reu(i, 0, N) g[i] = 0;
		reu(i, 0, N) (g[i%(p-1)] += t1[i]) %= mod;
		reu(i, 0, N) (f[i%(p-1)] += t2[i]) %= mod;
	}
	reu(i, 0, p-1)
		(ans[pw[i]] += v*f[i]) %= mod;
}


int main() {
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	static char s[100];
	int tmp;
	scanf("%d", &p);
	for (N=1; N<=p*2; N<<=1);
	for (L=0; (1<<L)<N; ++L);
	for (int i=1; i <= N; i<<=1) {
		rG[0][i] = fpm(_g, (mod-1)/(i), mod);
		rG[1][i] = fpm(rG[0][i], mod-2, mod);
	}
	reu(i, 0, N) rev[i] = (rev[i>>1]>>1)|((i&1)<<(L-1));
	rep(i, 1, p) inv[i] = fpm(i, p-2, p);
	invN = fpm(N, mod-2, mod);
	reu(i, 1, p) {
		int t = 1;
		reu(j, 1, p-1) {
			t = (LL)t*i%p;
			if (t == 1)
				goto hq;
		}
		p_g = i;
		t = 1;
		reu(j, 0, p-1) {
			pw[j] = t;
			ind[t] = j;
			t = (LL)t*p_g%p;
		}
		break;
hq:;
	}

	scanf("%s", s);
	trans(s, n);
	scanf("%s", s);
	trans(s, l);
	tmp = 0;
	red(i, l(l), 1)
		tmp = ((LL)tmp*p+l[i])%mod;
	ans[0] = -tmp;
	scanf("%s", s);
	trans(s, r);
	tmp = 0;
	red(i, l(r), 1)
		tmp = ((LL)tmp*p+r[i])%mod;
	ans[0] = (ans[0]+tmp+1+mod)%mod;
	b = max(l(n), max(l(l), l(r)));
	--l[1];
	reu(i, 1, b) {
		if (l[i] >= 0) break;
		--l[i+1], l[i]+=p;
	}
	solve(r, 1);
	solve(l, -1);
	reu(i, 1, p)
		(ans[0] -= ans[i]%mod) %= mod;
	(ans[0] += mod) %= mod;
	reu(i, 0, p) {
		printf("%d\n", (ans[i]%mod+mod)%mod);
	}

	return 0;
}

