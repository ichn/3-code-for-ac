#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

const int maxN = 1e5 + 1000;
int a[maxN], n;


bool ss[maxN], mr[maxN];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		memset(mr, 0, sizeof mr);
		memset(ss, 0, sizeof ss);
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			int t = i;
			while (!mr[t] && !ss[t]) {
				mr[t] = true;
				t = a[t];
			}
			if (t != i) {
				int k = i;
				while (mr[k]) {
					mr[k] = false;
					k = a[k];
				}
			} else {
				int k = i;
				while (mr[k]) {
					mr[k] = false;
					ss[k] = true;
					k = a[k];
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			if (!ss[i]) ++cnt;
		cout << cnt << endl;
	}

	return 0;
}
