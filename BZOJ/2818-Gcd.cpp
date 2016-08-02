#include <bits/stdc++.h>
#define rep(_i, _j) for(int _i = 1; _i <= _j; ++_i)
const int INF = 0x3f3f3f3f;
typedef double DB;
using namespace std;
const int maxn = 1e7 + 100;
typedef unsigned long long LL;
LL f[maxn];
int phi[maxn], vis[maxn], prime[maxn], tot = 0;
 
 
int main() {
	int N = maxn - 2;
	for(int i = 2; i <= N; ++i) {
		if(!vis[i]) {
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0; j < tot; ++j) {
			if(i * prime[j] > N) break;
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		f[i] = (((f[i - 1] >> 1) + phi[i]) << 1) + 1;
	}
	LL ans = 0;
	for(int i = 0; prime[i] <= n; ++i) {
		ans += f[n / prime[i]];
	}
	printf("%llu\n", ans);
	return 0;
}
