#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
const int INF = 0x3f3f3f3f;

int n, k;
int p[20], d[20][20];

int main() {
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &p[i]);
		d[i][0] = 1;
		for (int j = 1; j <= p[i]; ++j)
			scanf("%d", &d[i][j]);
	}
	int tot = 0, hd = 0;
	int w = 0;
	while (tot < k) {
		if (d[w][0] <= p[w]) {
			if (d[w][d[w][0]] >= hd) {
				hd += d[w][d[w][0]];
				++tot;
			} 
			++d[w][0];
		} else {
			++tot;
			hd += 50;
		}
		++w;
		w %= n;
	}
	printf("%d\n", hd);

	return 0;
}
