#include <bits/stdc++.h>
using namespace std;

typedef double DB;

struct fs {
	DB r, i;
	fs() {}
	fs(DB r, DB i=0.0):r(r), i(i) {}
	fs operator * (fs rhs) {
		return fs(r*rhs.r-i*rhs.i, r*rhs.i+i*rhs.r);
	}
	fs operator + (fs rhs) {
		return fs(r+rhs.r, i+rhs.i);
	}
	fs operator - (fs rhs) {
		return fs(r-rhs.r, i-rhs.i);
	}
};

const int maxn = 4e6;

namespace FFT_Recursive {
	fs tmp[maxn];
	void dft(fs*a, int n, int r) {
		if (n==1) return ;
		int h = n>>1;
		memcpy(tmp, a, sizeof(fs)*n);
		for (int i = 0; i < h; ++i)
			a[i] = tmp[i<<1], a[i+h] = tmp[i<<1|1];
		fs *b = a+h, c = fs(1), s = fs(cos(2.0*M_PI*r/n), sin(2.0*M_PI*r/n));
		dft(a, h, r), dft(b, h, r);
		for (int i = 0; i < h; ++i, c=c*s)
			tmp[i] = a[i]+c*b[i], tmp[i+h] = a[i]-c*b[i];
		memcpy(a, tmp, sizeof(fs)*n);
	}

	int a[maxn], b[maxn];
	void mult(int n, int m) {
		static fs A[maxn], B[maxn];
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			A[i] = fs(a[i]);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d", &b[i]);
			B[i] = fs(b[i]);
		}
		n = n+m-1;
		for (m=1; m <= n; m<<=1);
		dft(A, m, 1);
		dft(B, m, 1);
		for (int i = 0; i < m; ++i)
			A[i] = A[i] * B[i];
		dft(A, m, -1);
		for (int i = 0; i < n; ++i) {
			printf("%lld ", (long long)((A[i].r/m+.5)));
		}
	}
};
namespace FFT_NonRecursive {
	int rev[maxn];
	void dft(fs*a, int n, int r) {
		for (int i = 0; i < n; ++i)
			if (i < rev[i])
				swap(a[i], a[rev[i]]);
		for (int i = 2; i <= n; i <<= 1) {
			fs s = fs(cos(2*M_PI*r/i), sin(2*M_PI*r/i));
			for (int j = 0; j < n; j += i) {
				fs c = fs(1), u, v;
				for (int k = j; k < j+(i>>1); ++k, c = c*s) {
					u = a[k], v = c*a[k+(i>>1)];
					a[k] = u+v;
					a[k+(i>>1)] = u-v;
				}
			}
		}
		if (r==-1)
			for (int i = 0; i < n; ++i)
				a[i].r /= n;
	}

	int a[maxn], b[maxn];
	void mult(int n, int m) {
		static fs A[maxn], B[maxn];
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			A[i] = fs(a[i]);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d", &b[i]);
			B[i] = fs(b[i]);
		}
		n = n+m-1;
		for (m=1; m <= n; m<<=1);
		int l = 0;
		while ((1<<l) < m) ++l;
		for (int i = 0; i < m; ++i)
			rev[i] = (rev[i>>1]>>1)|((i&1)<<(l-1));
		dft(A, m, 1);
		dft(B, m, 1);
		for (int i = 0; i < m; ++i)
			A[i] = A[i] * B[i];
		dft(A, m, -1);
		for (int i = 0; i < n; ++i) {
			printf("%lld ", (long long)(A[i].r+.5));
		}
	}

};
namespace NTT_Recursive {
	typedef long long LL;
	const int mod = 998244353;
	const int G = 3;
	LL rG[maxn], fac[maxn], inv[maxn];

	LL fast_pow(LL b, LL i, LL m) {
		LL r = 1;
		for (; i; i>>=1, b=b*b%m)
			if (i&1) r = r*b %m;
		return r;
	}

	LL tmp[maxn], A[maxn], B[maxn];
	void dft(LL*a, int n, int r) {
		if (n==1) return ;
		int h = n>>1;
		memcpy(tmp, a, sizeof(LL)*n);
		for (int i = 0; i < h; ++i)
			a[i] = tmp[i<<1], a[i+h] = tmp[i<<1|1];
		LL *b = a+h, c = 1, s = rG[n];
		dft(a, h, r), dft(b, h, r);
		for (int i = 0; i < h; ++i, c=c*s%mod) {
			tmp[i] = (a[i]+c*b[i]%mod)%mod;
			tmp[i+h] = (a[i]-c*b[i]%mod+mod)%mod;
		}
		memcpy(a, tmp, sizeof(LL)*n);
	}
	int a[maxn], b[maxn];
	void mult(int n, int m) {
		for (int i = 0; i < n; ++i)
			scanf("%lld", &A[i]);
		for (int i = 0; i < m; ++i)
			scanf("%lld", &B[i]);

		n = n+m-1;
		for (m=1; m <= n; m<<=1);
		for (int t = m; t; t>>=1)
			rG[t] = fast_pow(G, (mod-1)/t, mod);

		dft(A, m, 1);
		dft(B, m, 1);
		for (int i = 0; i < m; ++i)
			A[i] = A[i] * B[i];
		for (int t = m; t; t>>=1)
			rG[t] = fast_pow(rG[t], mod-2, mod);
		dft(A, m, -1);
		LL revM = fast_pow(m, mod-2, mod);
		for (int i = 0; i < n; ++i) {
			printf("%lld ", (long long)((A[i]*revM)%mod));
		}
	}
};
namespace NTT_NonRecursive {
	typedef long long LL;
	const int mod = 998244353;
	const int g = 3;
	int rev[maxn];
	LL A[maxn], B[maxn], rG[maxn];
	LL fast_pow(LL b, LL i, LL m) {
		LL r = 1;
		for (; i; i>>=1, b=b*b%m)
			if (i&1) r = r*b %m;
		return r;
	}

	void dft(LL*a, int n, int r) {
		for (int i=0; i < n; ++i)
			if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i=2; i <= n; i<<=1) {
			LL s = rG[i], u, v, c;
			for (int j=0, k; j < n; j+=i)
				for (k=j, c=1; k<j+(i>>1); c=c*s%mod, ++k) {
					u = a[k], v = c*a[k+(i>>1)]%mod;
					a[k] = (u+v)%mod;
					a[k+(i>>1)] = (u-v+mod)%mod;
				}
		}
		if (r == -1) {
			LL rv = fast_pow(n, mod-2, mod);
			for (int i=0; i < n; ++i)
				a[i] = a[i]*rv%mod;
		}
	}

	void mult(int n, int m) {
		for (int i = 0; i < n; ++i)
			scanf("%lld", &A[i]);
		for (int i = 0; i < m; ++i)
			scanf("%lld", &B[i]);
		int l, N=n+m-1, M;
		for (M=1; M <= N; M<<=1);
		for (l=0; (1<<l) < M; ++l);
		for (int i = 0; i < M; ++i)
			rev[i] = (rev[i>>1]>>1)|((i&1)<<(l-1));
		for (int i=1; i <= M; i<<=1)
			rG[i] = fast_pow(g, (mod-1)/i, mod);

		dft(A, M, 1);
		dft(B, M, 1);
		for (int i = 0; i < M; ++i)
			A[i] = A[i]*B[i]%mod;
		for (int i=1; i <= M; i<<=1)
			rG[i] = fast_pow(rG[i], mod-2, mod);
		dft(A, M, -1);

		for (int i = 0; i < N; ++i)
			printf("%lld ", A[i]);
	}
};



int main() {

	freopen("FFT.in", "r", stdin);
	freopen("FFT.out", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
	++n, ++m;
	//FFT_Recursive::mult(n, m);
	//FFT_NonRecursive::mult(n, m);
	//NTT_Recursive::mult(n, m);
	NTT_NonRecursive::mult(n, m);

	return 0;
}
