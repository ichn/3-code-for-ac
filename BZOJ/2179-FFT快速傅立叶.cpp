#include <bits/stdc++.h>
using namespace std;
typedef double DB;

namespace FFT_recursive {

	struct Complex {
		DB Real, Imag;
		Complex() {}
		Complex(DB theta) { // Euler's e^{\theta i}=cos(\theta)+isin(\theta)
			Real = cos(theta), Imag = sin(theta);
		}
		Complex(DB Real, DB Imag):Real(Real), Imag(Imag) {
		}
		friend Complex operator * (Complex a, Complex b) {
			return Complex(a.Real * b.Real - a.Imag * b.Imag,
					a.Real * b.Imag + a.Imag * b.Real);
		}
		friend Complex operator - (Complex a, Complex b) {
			return Complex(a.Real - b.Real, a.Imag - b.Imag);
		}
		friend Complex operator + (Complex a, Complex b) {
			return Complex(a.Real + b.Real, a.Imag + b.Imag);
		}
	} ;

	const int maxn = 100000 * 4;
	Complex tmp[maxn], W, Wn;

	void DFT(Complex *a, int N, int rev) {
		if(N == 1) return ;
		memcpy(tmp, a, sizeof(a[0])*N);
		N>>=1;
		Complex *a1 = a + N;
		for(int i = 0; i < N; ++i)
			a[i] = tmp[i<<1], a1[i] = tmp[i<<1|1];
		DFT(a, N, rev), DFT(a1, N, rev);
		Wn = Complex(rev*M_PI/N), W = Complex(1.0, 0.0);
		for(int i = 0; i < N; W = W * Wn, ++i)
			tmp[i] = a[i] + W * a1[i],
			tmp[i+N] = a[i] - W * a1[i];
		memcpy(a, tmp, sizeof(a[0])*(N<<1));
	}

};

using namespace FFT_recursive;

bool tester() {
	static char str[maxn];
	static int ans[maxn];
	static Complex a[maxn], b[maxn], c[maxn];
	int n;
	scanf("%d", &n);
	scanf("%s", str);
	for(int i = 0; i < n; ++i)
		a[n - i - 1] = Complex(str[i] - '0', 0);
	scanf("%s", str);
	for(int i = 0; i < n; ++i)
		b[n - i - 1] = Complex(str[i] - '0', 0);
	int N = 1;
	while(N < n) N <<= 1;
	N <<= 1;
	DFT(a, N, 1), DFT(b, N, 1);
	for(int i = 0; i < N; ++i)
		c[i] = a[i] * b[i];
	DFT(c, N, -1);
	for(int i = 0; i < N; ++i) {
		ans[i] += int((DB)c[i].Real/N+.5);
		ans[i+1]+=ans[i]/10, ans[i]%=10;
	}
	for(; N && ans[N] == 0; --N);
	for(; -1 < N; --N) {
		printf("%d", ans[N]);
	}
	exit(0);
	return true;
}


int main() {
	//freopen("FFT.in", "r", stdin), freopen("FFT.out", "w", stdout);
	printf("\n%d\n", tester());
	return 0;
}

