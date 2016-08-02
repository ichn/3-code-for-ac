#include <bits/stdc++.h>
#define rep(_i, _j) for(int _i = 1; _i <= _j; ++_i)
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef double DB;
using namespace std;


int f, n;
const int maxn = 100000 + 20;
bool calced[maxn];
int sg[maxn];

int work(int p) {
	if(calced[p]) {
		return sg[p];
	}
	calced[p] = true;
	if(p < f) {
		return sg[p] = 0;
	}
	bool hash[maxn];
	memset(hash, false, sizeof hash);
	for(int i = 2; i <= p; i = p / (p / i) + 1) {
		for(int j = i; j <= i + 1 && j <= p; ++j) {
			int status = 0;
			int time = p - (p / j) * j;
			if(time & 1) {
				status ^= work(p / j + 1);
			}
			if((j - time) & 1) {
				status ^= work(p / j);
			}
			hash[status] = true;
		}
	}
	for(int i = 0; ; ++i) {
		if(!hash[i]) {
			return sg[p] = i;
		}
	}
}

int main() {
	int t, m;
	scanf("%d%d", &t, &f);
	while(t--) {
		scanf("%d", &n);
		int res = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &m);
			res ^= work(m);
		}
		printf("%d", res > 0);
		if(t == 0) {
			puts("");
		} else {
			putchar(' ');
		}
	}

	return 0;
}

